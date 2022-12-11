#include "broadcast.h"

std::optional<Matrix> tryBroadcastTo(const Matrix& matrix, const Shape& shape) {
    if (matrix.shape() == shape) {
        return matrix;
    }
    if (matrix.shape() == Shape{1, shape.cols}) {
        Matrix newMatrix(shape);
        for (size_t i = 0; i < shape.rows; ++i) {
            newMatrix.setRow(i, matrix);
        }
        return newMatrix;
    }
    if (matrix.shape() == Shape{shape.rows, 1}) {
        Matrix newMatrix(shape);
        for (size_t i = 0; i < shape.cols; ++i) {
            newMatrix.setCol(i, matrix);
        }
        return newMatrix;
    }
    if (matrix.shape() == Shape{1, 1}) {
        Matrix newMatrix(shape);
        for (size_t i = 0; i < shape.rows; ++i) {
            for (size_t j = 0; j < shape.cols; ++j) {
                newMatrix.at(i, j) = matrix.at(0, 0);
            }
        }
        return newMatrix;
    }

    return std::nullopt;
}
