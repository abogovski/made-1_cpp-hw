#pragma once

#include <memory>
#include <optional>
#include <cstddef>

using ValueType = double;

struct Shape {
    size_t rows;
    size_t cols;

    bool operator==(const Shape& other) const;
};

class Matrix {
public:
    Matrix(const Shape& shape);
    Matrix(const Shape& shape, const Matrix& defaultValue);
    Matrix(const Matrix& matrix);
    Matrix(Matrix&& matrix);

    Shape shape() const;

    ValueType& at(size_t rowIdx, size_t colIdx);
    const ValueType& at(size_t rowIdx, size_t colIdx) const;

    Matrix getRow(size_t rowIdx) const;
    Matrix getCol(size_t colIdx) const;
    Matrix getDiagAsCol() const;

    void setRow(size_t rowIdx, const Matrix& row);
    void setCol(size_t colIdx, const Matrix& col);

    Matrix T() const; // get transposed

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator%(const Matrix& other) const;

    Matrix& operator=(const Matrix& other) const;

private:
    std::unique_ptr<ValueType> values;
    size_t nRows;
    size_t nCols;
};

Matrix Value(ValueType value);
Matrix Row(size_t nCols, ValueType value);
Matrix Col(size_t nRows, ValueType value);
