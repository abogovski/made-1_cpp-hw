#pragma once

#include "stack_impl.h"

template<class MatrixIt>
Matrix stackRows(MatrixIt matricesBegin, MatrixIt matricesEnd) {
    size_t nRows = getTotalRowPositiveCount(matricesBegin, matricesEnd);
    size_t nCols = getCommonColPositiveCount(matricesBegin, matricesEnd);
    size_t rowOffset = 0;

    Matrix matrix({nRows, nCols});
    for (MatrixIt it = matricesBegin; it != matricesEnd; ++it) {
        for (size_t row = 0; row < it->shape().rows; ++row) {
            for (size_t col = 0; col < it->shape().cols; ++col) {
                matrix.at(rowOffset + row, col) = it->at(row, col);
            }
        }
        rowOffset += it->shape().rows;
    }
    return matrix;
}

template<class MatrixIt>
Matrix stackCols(MatrixIt matricesBegin, MatrixIt matricesEnd) {
    size_t nRows = getCommonRowPositiveCount(matricesBegin, matricesEnd);
    size_t nCols = getTotalColPositiveCount(matricesBegin, matricesEnd);
    size_t colOffset = 0;

    Matrix matrix({nRows, nCols});
    for (MatrixIt it = matricesBegin; it != matricesEnd; ++it) {
        for (size_t row = 0; row < it->shape().rows; ++row) {
            for (size_t col = 0; col < it->shape().cols; ++col) {
                matrix.at(row, colOffset + col) = it->at(row, col);
            }
        }
        colOffset += it->shape().cols;
    }
    return matrix;
}
