#include "count.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <thread>

#include <sys/wait.h>
#include <unistd.h>

namespace {

constexpr size_t approxMinPartSize = 1024;
constexpr size_t UCHAR_MAX = std::numeric_limits<unsigned char>::max();

std::vector<size_t> getHistogram(const unsigned char* bytes, size_t size) {
    std::vector<size_t> histogram(UCHAR_MAX + 1, 0);
    for (size_t i = 0; i < size; ++i) {
        ++histogram[bytes[i]];
    }
    return histogram;
}

bool writeResult(int fd, const std::vector<size_t>& result) {
    int rv;
    size_t size = result.size() * sizeof(size_t);
    size_t offset = 0;

    do {
        rv = write(fd, result.data() + offset, size - offset);
        offset += std::max(0, rv);
    } while (offset < sizeof(result) && rv == EINTR);

    return offset == size;
}

bool readResult(int fd, std::vector<size_t>& result) {
    int rv;

    result.clear();
    result.resize(UCHAR_MAX + 1, 0);

    size_t size = result.size() * sizeof(size_t);
    size_t offset = 0;

    do {
        rv = read(fd, result.data() + offset, size - offset);
        offset += std::max(0, rv);
    } while (offset < sizeof(result) && rv == EINTR);

    return offset == size;
}

bool spawnCountProcess(int* fd, const unsigned char* bytes, size_t size) {
    int pid = fork();
    if (!pid) {
        close(fd[0]);
        writeResult(fd[1], getHistogram(bytes, size));

        close(fd[1]);
        exit(0);
    }
    return !(pid < 0);
}

void waitAllChildren() {
    for (int status; wait(&status) > 0; );
}

size_t getSplitSize(size_t totalSize) {
    double partsMax = std::thread::hardware_concurrency();
    double numPartsEstimate = std::round(double(totalSize) / approxMinPartSize);
    return std::ceil(totalSize / std::clamp(numPartsEstimate, 1., partsMax));
}

} // namespace

bool CharCount::operator==(const CharCount& other) const {
    return value == other.value && count == other.count;
}

std::vector<CharCount> getCharCounts(const std::vector<unsigned char>& bytes, const std::string& charset) {
    int fd[2] = {0, 0};
    std::vector<size_t> totalResult;

    try {
        if (pipe(fd) < 0) {
            throw std::runtime_error("Could not create pipe");
        }

        auto splitSize = getSplitSize(bytes.size());
        int numParallel = 0;

        for (size_t offset = 0; offset < bytes.size(); offset += splitSize, ++numParallel) {
            size_t size = std::min(bytes.size(), offset + splitSize) - offset;

            if (!spawnCountProcess(fd, bytes.data() + offset, size)) {
                throw std::runtime_error("Could not spawn process");
            }
        }
        close(fd[1]);

        int resultsRead = 0;
        if (readResult(fd[0], totalResult)) {
            ++resultsRead;
            std::vector<size_t> chunkResult;
            while (readResult(fd[0], chunkResult)) {
                for (size_t i = 0; i < UCHAR_MAX; ++i) {
                    totalResult[i] += chunkResult[i];
                }
                ++resultsRead;
            }
        }

        if (resultsRead != numParallel) {
            throw std::runtime_error("Could not read all results");
        }

        close(fd[0]);
        waitAllChildren();
    } catch (...) {
        if (fd[0] != 0) {
            close(fd[0]);
        }
        waitAllChildren();
        throw;
    }

    std::vector<CharCount> counts(charset.size());
    for (size_t i = 0; i < charset.size(); ++i) {
        counts[i].value = charset[i];
        counts[i].count = totalResult[static_cast<unsigned char>(charset[i])];
    }
    return counts;
}
