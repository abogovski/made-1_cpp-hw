#include "matrix.h"

bool Shape::operator==(const Shape& other) const {
    return rows == other.rows && cols == other.cols;
}

Matrix::Matrix(const Shape& shape):
    values(new ValueType[shape.rows * shape.cols]),
    nRows(shape.rows),
    nCols(shape.cols)
{
    for (size_t i = 0; i < nRows * nCols; ++i) {
        values.get()[i] = 0.0;
    }
}

Matrix::Matrix(const Shape& shape, const Matrix& defaultValue):
    Matrix(shape) {
    // FIXIT: tidy up this multiple ctrs + broadcast fuckery
    if (shape != defaultValue.shape) {
        auto broadcasted = tryBroadcastTo(defaultValue, shape);
    } else {
        *this = defaultValue;
    }
}

Matrix::Matrix(const Matrix& other):
    Matrix(other.shape()) {
    for (size_t i = 0; i < nRows * nCols; ++i) {
        values.get()[i] = other.values.get()[i];
    }
}

Matrix::Matrix(Matrix&& other):
    values(std::move(other.values)),
    nRows(other.shape().rows),
    nCols(other.shape().cols) {}

Matrix& Matrix::operator=(const Matrix& other) {
    nRows = other.shape().rows;
    nCols = other.shape().cols;
    values = new ValueType[nRows * nCols];
    for (size_t i = 0; i < nRows * nCols; ++i) {
        values.get()[i] = other.values.get()[i];
    }
    return *this;
}

Shape Matrix::shape() const {
    return {nRows, nCols};
}

ValueType& at(size_t rowIdx, size_t colIdx) {
    return values.get()[nCols * rowIdx + colIdx];
}

const ValueType& at(size_t rowIdx, size_t colIdx) const {
    return values.get()[nCols * rowIdx + colIdx];
}

Matrix Matrix::getRow(size_t rowIdx) const {
    Matrix row(1, nCols);
    for (size_t i = 0; i < nCols; ++i) {
        row.at(0, i) = at(rowIdx, i);
    }
    return row;
}

Matrix Matrix::getCol(size_t colIdx) const {
    Matrix col(nRows, 1);
    for (size_t i = 0; i < nRows; ++i) {
        row.at(i, 0) = at(i, colIdx);
    }
    return row;
}

Matrix Matrix::getDiagAsCol() const {
    Matrix col(std::min(nRows, nCols), 1);
    for (size_t i = 0; i < std::min(nRows, nCols); ++i) {
        col.at(i, 0) = at(i, i);
    }
    return col;
}

void Matrix::setRow(size_t rowIdx, const Matrix& row) {
    if (row.shape() != {1, nCols}) {
        throw std::runtime_error("setRow size mismatch");
    }
    for (size_t i = 0; i < nCols; ++i) {
        at(rowIdx, i) = row.at(0, i);
    }
}

void Matrix::setCol(size_t colIdx, const Vector& col) {
    if (row.shape() != {1, nRows}) {
        throw std::runtime_error("setRow size mismatch");
    }
    for (size_t i = 0; i < nRows; ++i) {
        at(colIdx, i) = row.at(0, i);
    }
}

Matrix Matrix::T() const {
    Matrix newMatrix(Shape{shape.cols, shape.rows}); // TODO: Shape.T()
    for (size_t i = 0; i < nRows; ++i) {
        for (size_t j = 0; j < nCols; ++j) {
            newMatrix.at(j, i) = at(i, j);
        }
    }
    return newMatrix;
}

namespace {

Matrix add(const Matrix& lhs, const Matrix& rhs) {
    // assert broadcasted
    Matrix result(lhs.shape());
    for (size_t i = 0; i < lhs.shape().rows; ++i) {
        for (size_t j = 0; j < lhs.shape().cols; ++j) {
            result.at(i, j) = lhs.at(i, j) + lhs.at(i, j);
        }
    }
    return result;
}

Matrix sub(const Matrix& lhs, const Matrix& rhs) {
    // assert broadcasted
    Matrix result(lhs.shape());
    for (size_t i = 0; i < lhs.shape().rows; ++i) {
        for (size_t j = 0; j < lhs.shape().cols; ++j) {
            result.at(i, j) = lhs.at(i, j) - lhs.at(i, j);
        }
    }
    return result;
}

Matrix mul(const Matrix& lhs, const Matrix& rhs) {
    // assert broadcasted
    Matrix result(lhs.shape());
    for (size_t i = 0; i < lhs.shape().rows; ++i) {
        for (size_t j = 0; j < lhs.shape().cols; ++j) {
            result.at(i, j) = lhs.at(i, j) * lhs.at(i, j);
        }
    }
    return result;
}

} // namespace

Matrix Matrix::operator+(const Matrix& other) const {
    auto broadcastedOther = tryBroadcastTo(other, shape());
    if (broadcastedOther) {
        return add(*this, *broadcastedOther);
    }

    auto broadcastedThis = tryBroadcastTo(*this, other.shape());
    if (broadcastedThis) {
        return add(*broadCastedThis, other);
    }

    // TODO: also process [1, n] + [m, 1] case
    throw std::runtime_error("could not broadcast together");
}

Matrix Matrix::operator-(const Matrix& other) const {
    auto broadcastedOther = tryBroadcastTo(other, shape());
    if (broadcastedOther) {
        return sub(*this, *broadcastedOther);
    }

    auto broadcastedThis = tryBroadcastTo(*this, other.shape());
    if (broadcastedThis) {
        return sub(*broadCastedThis, other);
    }

    // TODO: also process [1, n] + [m, 1] case
    throw std::runtime_error("could not broadcast together");
}

Matrix operator*(const Matrix& other) const
{
    auto broadcastedOther = tryBroadcastTo(other, shape());
    if (broadcastedOther) {
        return mul(*this, *broadcastedOther);
    }

    auto broadcastedThis = tryBroadcastTo(*this, other.shape());
    if (broadcastedThis) {
        return mul(*broadCastedThis, other);
    }

    // TODO: also process [1, n] + [m, 1] case
    throw std::runtime_error("could not broadcast together");
}


Matrix Matrix::operator%(const Matrix& other) const {
    if (shape().cols() != other.shape().rows()) {
        throw std::runtime_error("size mismatch");
    }
    Matrix result({shape().rows, other.shape().cols});
    for (size_t i = 0; i < nRows; ++i) {
        for (size_t j = 0; j < other.shape().cols; ++j) {
            ValueType accum = 0;
            for (size_t k = 0; k < nCols; ++k) {
                accum += at(i, k) * other.at(k, j);
            }
            result.at(i, j) = accum;
        }
    }
    return result;
}

Matrix Value(ValueType value) {
    Matrix matrix({1, 1});
    matrix.at(0, 0) = value;
    return matrix;
}

Matrix Row(size_t nCols, ValueType value) {
    Matrix matrix({1, nCols});
    for (size_t i = 0; i < nCols; ++i) {
        matrix.at(0, i) = value;
    }
    return matrix;
}

Matrix Col(size_t nRows, ValueType value) {
    Matrix matrix({nRows, 1});
    for (size_t i = 0; i < nRows; ++i) {
        matrix.at(i, 0)
    }
}
