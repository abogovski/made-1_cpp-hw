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
    Matrix stackedRows = stackOverCols(rows.begin(), rows.end());
}
