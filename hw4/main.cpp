#include "count.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <thread>

constexpr int NUM_TRIALS = 3;

using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;
using FloatDuration = std::chrono::duration<float>;
using Clock = std::chrono::steady_clock;

std::vector<unsigned char> readFile(const char* fileName) {
    std::ifstream file;
    file.exceptions(std::ios::failbit | std::ios::badbit);
    file.open(fileName, std::ios::binary | std::ios::ate);

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<unsigned char> bytes(size);
    file.read((char*)bytes.data(), size);
    return bytes;
}

void expectSameResults(const std::vector<std::vector<CharCount>>& results) {
    for (size_t i = 1; i < results.size(); ++i) {
        if (results[0] != results[i]) {
            throw std::runtime_error("Trial results differ");
        }
    }
}

std::ostream& operator << (std::ostream& os, const std::vector<CharCount>& charCounts) {
    for (const auto& charCount : charCounts) {
        os << charCount.value << " " << charCount.count << std::endl;
    }
    return os;
}

double benchmark(const std::vector<unsigned char>& bytes, const std::string& charset, size_t numTrials) {
    std::vector<double> times(numTrials);
    std::vector<std::vector<CharCount>> results(numTrials);

    for (size_t i = 0; i < numTrials; ++i) {
        auto start = Clock::now();
        results[i] = getCharCounts(bytes, charset);
        times[i] = FloatDuration(Clock::now() - start).count();
    }

    expectSameResults(results);

    std::cout << results[0] << std::endl;

    std::sort(times.begin(), times.end());
    return (times[times.size() / 2] + times[times.size() / 2 - 1]) / 2;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Path to file and charset should be specified in params" << std::endl;
        return 1;
    }

    double elapsedTime = benchmark(readFile(argv[1]), argv[2], NUM_TRIALS);
    std::cerr << "Median time: " << elapsedTime << std::endl;
    if (PARALLEL) {
        std::cerr << "Hardware concurrency: " << std::thread::hardware_concurrency() << std::endl;
    }
    return 0;
}
