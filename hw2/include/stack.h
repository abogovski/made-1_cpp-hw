#pragma once

#include "stack_impl.h"

template<class MatrixIt>
Matrix stackOverRows(MatrixIt matricesBegin, MatrixIt matricesEnd) {
    size_t nRows = getTotalRowPositiveCount(matricesBegin, matricesEnd);
    size_t nCols = getCommonColPositiveCount(matricesBegin, matricesEnd);
}

template<class MatrixIt>
Matrix stackOverCols(MatrixIt matricesBegin, MatrixIt matricesEnd) {
    size_t nRows = getCommonRowPositiveCount(matricesBegin, matricesEnd);
    size_t nCols = getTotalColPositiveCount(matricesBegin, matricesEnd);
}
