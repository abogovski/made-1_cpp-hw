#pragma once

#include <string>
#include <vector>

struct CharCount {
    char value;
    size_t count;

    bool operator==(const CharCount& other) const;
};

std::vector<CharCount> getCharCounts(
    const std::vector<unsigned char>& bytes,
    const std::string& charset);
