#include <gtest/gtest.h>
#include "matrix.h"
#include "stack.h"


TEST(matrix, access_elements_by_index_and_extract_rows_cols_and_diag) {
    Matrix matrix(Shape{3, 2});

    matrix.at(0, 0) = 1; matrix.at(0, 1) = 2;
    matrix.at(1, 0) = 3; matrix.at(1, 1) = 4;
    matrix.at(2, 0) = 5; matrix.at(2, 1) = 6;

    EXPECT_EQ(matrix.at(0, 0), 1); EXPECT_EQ(matrix.at(0, 1), 2);
    EXPECT_EQ(matrix.at(1, 0), 3); EXPECT_EQ(matrix.at(1, 1), 4);
    EXPECT_EQ(matrix.at(2, 0), 5); EXPECT_EQ(matrix.at(2, 1), 6);

    Matrix row = matrix.getRow(0);
    EXPECT_EQ(matrix.at(0, 0), row.at(0, 0));
    EXPECT_EQ(matrix.at(0, 1), row.at(0, 1));

    row = matrix.getRow(1);
    EXPECT_EQ(matrix.at(1, 0), row.at(0, 0));
    EXPECT_EQ(matrix.at(1, 1), row.at(0, 1));

    row = matrix.getRow(2);
    EXPECT_EQ(matrix.at(2, 0), row.at(0, 0));
    EXPECT_EQ(matrix.at(2, 1), row.at(0, 1));

    Matrix col = matrix.getCol(0);
    EXPECT_EQ(matrix.at(0, 0), col.at(0, 0));
    EXPECT_EQ(matrix.at(1, 0), col.at(1, 0));

    col = matrix.getCol(1);
    EXPECT_EQ(matrix.at(0, 1), col.at(0, 0));
    EXPECT_EQ(matrix.at(1, 1), col.at(1, 0));
}

TEST(matrix, create_rows_and_cols_from_values) {
    std::vector<Matrix> rows {Row({1, 2, 3}), Row({4, 5, 6})};

    EXPECT_EQ(rows[0].shape(), (Shape{1, 3}));
    EXPECT_EQ(rows[0].at(0, 0), 1);
    EXPECT_EQ(rows[0].at(0, 1), 2);
    EXPECT_EQ(rows[0].at(0, 2), 3);

    Matrix stackedRows = stackRows(rows.begin(), rows.end());
    EXPECT_EQ(stackedRows.shape(), (Shape{2, 3}));

    EXPECT_EQ(stackedRows.at(0, 0), rows[0].at(0, 0));
    EXPECT_EQ(stackedRows.at(0, 1), rows[0].at(0, 1));
    EXPECT_EQ(stackedRows.at(0, 2), rows[0].at(0, 2));

    EXPECT_EQ(stackedRows.at(1, 0), rows[1].at(0, 0));
    EXPECT_EQ(stackedRows.at(1, 1), rows[1].at(0, 1));
    EXPECT_EQ(stackedRows.at(1, 2), rows[1].at(0, 2));

    std::vector<Matrix> cols {Col({1, 2, 3}), Col({4, 5, 6})};
    Matrix stackedCols = stackCols(cols.begin(), cols.end());

    EXPECT_EQ(stackedCols.shape(), (Shape{3, 2}));

    EXPECT_EQ(stackedCols.at(0, 0), cols[0].at(0, 0));
    EXPECT_EQ(stackedCols.at(1, 0), cols[0].at(1, 0));
    EXPECT_EQ(stackedCols.at(2, 0), cols[0].at(2, 0));

    EXPECT_EQ(stackedCols.at(0, 1), cols[1].at(0, 0));
    EXPECT_EQ(stackedCols.at(1, 1), cols[1].at(1, 0));
    EXPECT_EQ(stackedCols.at(2, 1), cols[1].at(2, 0));

    Matrix value = Value(123);
    EXPECT_EQ(value.shape(), (Shape{1, 1}));
    EXPECT_EQ(value.at(0, 0), 123);
}

TEST(matrix, elementwise_ops) {
    std::vector<Matrix> rowsLeft {Row({1, 2, 3}), Row({4, 5, 6})};
    std::vector<Matrix> rowsRight {Row({3, 7, 1}), Row({1, 4, 2})};
    Matrix left = stackRows(rowsLeft.begin(), rowsLeft.end());
    Matrix right = stackRows(rowsRight.begin(), rowsRight.end());

    Matrix sum = left + right;
    Matrix difference = left - right;
    Matrix product = left * right;

    EXPECT_EQ(sum.shape(), left.shape());
    EXPECT_EQ(difference.shape(), left.shape());
    EXPECT_EQ(product.shape(), left.shape());

    for (size_t row = 0; row < 2; ++row) {
        for (size_t col = 0; col < 3; ++col) {
            EXPECT_EQ(left.at(row, col) + right.at(row, col), sum.at(row, col));
            EXPECT_EQ(left.at(row, col) - right.at(row, col), difference.at(row, col));
            EXPECT_EQ(left.at(row, col) * right.at(row, col), product.at(row, col));
        }
    }
}
