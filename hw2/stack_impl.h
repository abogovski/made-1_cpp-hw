#pragma once

#include "matrix.h"
#include <stdexcept>

template<class MatrixIt>
size_t getTotalRowsPositiveCount(MatrixIt matricesBegin, MatrixIt matricesEnd) {
    size_t nRows = 0;
    for (MatrixIt it = matricesBegin; it != matricesEnd; ++it) {
        nRows += it->shape().rows;
    }
    if (!nRows) {
        throw std::runtime_error("total number of rows is not positive");
    }
    return nRows;
}

template<class MatrixIt>
size_t getTotalColsPositiveCount(MatrixIt matricesBegin, MatrixIt matricesEnd) {
    size_t nCols = 0;
    for (MatrixIt it = matricesBegin; it != matricesEnd; ++it) {
        nCols += it->shape().cols;
    }
    if (!nCols) {
        throw std::runtime_error("total number of cols is not positive");
    }
    return nCols;
}

template<class MatrixIt>
size_t getCommonRowPositiveCount(MatrixIt matricesBegin, MatrixIt matricesEnd) {
    std::optional<size_t> nRows;
    for (MatrixIt it = matricesBegin; it != matricesEnd; ++it) {
        if (!nRows) {
            *nRows = it->shape().rows;
        }
        if (*nRows != it->shape().rows) {
            throw std::runtime_error("rows count mismatch");
        }
    }
    if (!nRows) {
        throw std::runtime_error("can't get common row count for empty list of matrices");
    }
    if (!*nCols) {
        throw std::runtime_error("common number of rows is not positive");
    }
    return *nRows;
}

template<class MatrixIt>
size_t getCommonColPositiveCount(MatrixIt matricesBegin, MatrixIt matricesEnd) {
    std::optional<size_t> nCols;
    for (MatrixIt it = matricesBegin; it != matricesEnd; ++it) {
        if (!nCols) {
            *nCols = it->shape().cols;
        }
        if (*nCols != it->shape().cols) {
            throw std::runtime_error("cols count mismatch");
        }
    }
    if (!nCols) {
        throw std::runtime_error("can't get common col count for empty list of matrices");
    }
    if (!*nCols) {
        throw std::runtime_error("common number of cols is not positive");
    }
    return *nCols;
}
