#pragma once

#include "stack_impl.h"

template<class MatrixIt>
Matrix stackOverRows(MatrixIt matricesBegin, MatrixIt matricesEnd) {
    size_t nRows = getTotalRowsPositiveCount(matricesBegin, matricesEnd);
    size_t nCols = getCommonColsPositiveCount(matricesBegin, matricesEnd);
}

template<class MatrixIt>
Matrix stackOverCols(MatrixIt matricesBegin, MatrixIt matricesEnd) {
    size_t nRows = getCommonRowsPositiveCount(matricesBegin, matricesEnd);
    size_t nCols = getTotalColsPositiveCount(matricesBegin, matricesEnd);
}
