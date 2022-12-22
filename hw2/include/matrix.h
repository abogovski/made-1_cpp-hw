#pragma once

#include <memory>
#include <optional>
#include <cstddef>
#include <vector>

using ValueType = double;

struct Shape {
    size_t rows;
    size_t cols;

    bool operator==(const Shape& other) const;
    bool operator!=(const Shape& other) const;

    Shape T() const;
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

    Matrix& operator=(const Matrix& other);

private:
    std::unique_ptr<ValueType> values;
    size_t nRows;
    size_t nCols;
};

Matrix Value(ValueType value);
Matrix Row(const std::vector<ValueType>& values);
Matrix Col(const std::vector<ValueType>& values);
