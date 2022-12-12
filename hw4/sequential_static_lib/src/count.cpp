#include "count.h"

#include <limits>

namespace {

constexpr size_t UCHAR_MAX = std::numeric_limits<unsigned char>::max();

} // namespace

bool CharCount::operator==(const CharCount& other) const {
    return value == other.value && count == other.count;
}

std::vector<CharCount> getCharCounts(const std::vector<unsigned char>& bytes, const std::string& charset) {
    size_t histogram[UCHAR_MAX + 1] = {};

    for (unsigned char value : bytes) {
        ++histogram[value];
    }

    std::vector<CharCount> counts(charset.size());
    for (size_t i = 0; i < charset.size(); ++i) {
        counts[i].value = charset[i];
        counts[i].count = histogram[static_cast<unsigned char>(charset[i])];
    }
    return counts;
}
