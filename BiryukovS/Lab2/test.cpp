#include "pch.h"
#include <gtest/gtest.h>
#include "TVector.h"

TEST(TVector, create_and_access) {
    TVector<int> v(5, 0);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(v[i], 0);
    }
    v[0] = 10;
    v[3] = 30;
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[3], 30);
    EXPECT_EQ(v.GetSize(), 5);
    EXPECT_EQ(v.GetStartIndex(), 0);
}

TEST(TVector, create_with_start_index) {
    TVector<int> v(4, 3);
    v[3] = 100;
    v[6] = 600;
    EXPECT_EQ(v[3], 100);
    EXPECT_EQ(v[6], 600);
    EXPECT_EQ(v.GetStartIndex(), 3);
    EXPECT_EQ(v.GetSize(), 4);
}

TEST(TVector, copy_constructor_is_deep) {
    TVector<int> a(3, 0);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    TVector<int> b(a);
    a[0] = 999;
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
    EXPECT_EQ(b[2], 3);
}

TEST(TVector, assignment_is_deep_and_self_safe) {
    TVector<int> a(3, 0);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    TVector<int> b(2, 0);
    b = a;
    EXPECT_EQ(b.GetSize(), 3);
    EXPECT_EQ(b[0], 1);
    a[0] = 777;
    EXPECT_EQ(b[0], 1);
    b = b;
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[2], 3);
}

TEST(TVector, equality) {
    TVector<int> a(3, 0);
    a[0] = 1; a[1] = 2; a[2] = 3;
    TVector<int> b(3, 0);
    b[0] = 1; b[1] = 2; b[2] = 3;
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
    b[2] = 5;
    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a == b);
}

TEST(TVector, equality_requires_same_start_index) {
    TVector<int> a(2, 0);
    a[0] = 1; a[1] = 2;
    TVector<int> b(2, 5);
    b[5] = 1; b[6] = 2;
    EXPECT_TRUE(a != b);
}

TEST(TVector, scalar_operations) {
    TVector<int> v(3, 0);
    v[0] = 1; v[1] = 2; v[2] = 3;
    TVector<int> plus = v + 10;
    EXPECT_EQ(plus[0], 11);
    EXPECT_EQ(plus[2], 13);
    EXPECT_EQ(plus.GetStartIndex(), 0);
    TVector<int> minus = v - 1;
    EXPECT_EQ(minus[0], 0);
    EXPECT_EQ(minus[2], 2);
    TVector<int> mult = v * 2;
    EXPECT_EQ(mult[0], 2);
    EXPECT_EQ(mult[2], 6);
}

TEST(TVector, vector_add_sub) {
    TVector<int> a(3, 0);
    a[0] = 1; a[1] = 2; a[2] = 3;
    TVector<int> b(3, 0);
    b[0] = 10; b[1] = 20; b[2] = 30;
    TVector<int> sum = a + b;
    EXPECT_EQ(sum[0], 11);
    EXPECT_EQ(sum[1], 22);
    EXPECT_EQ(sum[2], 33);
    TVector<int> diff = b - a;
    EXPECT_EQ(diff[0], 9);
    EXPECT_EQ(diff[2], 27);
}

TEST(TVector, dot_product) {
    TVector<int> a(3, 0);
    a[0] = 1; a[1] = 2; a[2] = 3;
    TVector<int> b(3, 0);
    b[0] = 4; b[1] = 5; b[2] = 6;
    EXPECT_EQ(a * b, 32);
}

TEST(TVector, empty_vector) {
    TVector<int> v(0, 0);
    EXPECT_EQ(v.GetSize(), 0);
    TVector<int> v2(0, 7);
    EXPECT_EQ(v2.GetSize(), 0);
    EXPECT_EQ(v2.GetStartIndex(), 7);
    EXPECT_THROW(v + v2, std::invalid_argument);
    TVector<int> m = v * 5;
    EXPECT_EQ(m.GetSize(), 0);
    EXPECT_THROW(v * v2, std::invalid_argument);
}

TEST(TVector, boundary_access) {
    TVector<int> v(3, 2);
    v[2] = 1;
    v[4] = 3;
    EXPECT_EQ(v[2], 1);
    EXPECT_EQ(v[4], 3);
}

TEST(TVector, throw_negative_size_or_start_index) {
    EXPECT_THROW(TVector<int>(-1, 0), std::out_of_range);
    EXPECT_THROW(TVector<int>(5, -1), std::out_of_range);
}

TEST(TVector, throw_too_large_size) {
    EXPECT_THROW(TVector<int>(MAX_VECTOR_SIZE + 1, 0), std::out_of_range);
    EXPECT_THROW(TVector<int>(MAX_VECTOR_SIZE, 1), std::out_of_range);
}

TEST(TVector, throw_access_out_of_range) {
    TVector<int> v(3, 0);
    EXPECT_THROW(v[-1], std::out_of_range);
    EXPECT_THROW(v[3], std::out_of_range);
    EXPECT_THROW(v[100], std::out_of_range);
}

TEST(TVector, throw_access_below_start_index) {
    TVector<int> v(3, 5);
    EXPECT_THROW(v[4], std::out_of_range);
    EXPECT_THROW(v[0], std::out_of_range);
}

TEST(TVector, throw_incompatible_sizes) {
    TVector<int> a(3, 0);
    TVector<int> b(4, 0);
    EXPECT_THROW(a + b, std::invalid_argument);
    EXPECT_THROW(a - b, std::invalid_argument);
    EXPECT_THROW(a * b, std::invalid_argument);
}

TEST(TVector, throw_incompatible_start_index) {
    TVector<int> a(3, 0);
    TVector<int> b(3, 5);
    EXPECT_THROW(a + b, std::invalid_argument);
    EXPECT_THROW(a - b, std::invalid_argument);
    EXPECT_THROW(a * b, std::invalid_argument);
}

TEST(TMatrix, create_zero_matrix) {
    TMatrix<int> m(4);
    EXPECT_EQ(m.GetSize(), 4);
    EXPECT_EQ(m.GetStartIndex(), 0);
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(m[i].GetSize(), 4 - i);
        EXPECT_EQ(m[i].GetStartIndex(), i);
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = i; j < 4; ++j) {
            EXPECT_EQ(m[i][j], 0);
        }
    }
}

TEST(TMatrix, access_triangle) {
    TMatrix<int> m(3);
    m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
    m[1][1] = 4; m[1][2] = 5;
    m[2][2] = 6;
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][2], 3);
    EXPECT_EQ(m[1][1], 4);
    EXPECT_EQ(m[1][2], 5);
    EXPECT_EQ(m[2][2], 6);
}

TEST(TMatrix, copy_is_deep) {
    TMatrix<int> a(3);
    a[0][0] = 1; a[1][1] = 2; a[2][2] = 3;
    TMatrix<int> b(a);
    a[0][0] = 999;
    EXPECT_EQ(b[0][0], 1);
    EXPECT_EQ(b[1][1], 2);
    EXPECT_EQ(b[2][2], 3);
}

TEST(TMatrix, assign_is_deep_and_self_safe) {
    TMatrix<int> a(3);
    a[0][0] = 1; a[0][1] = 2; a[1][1] = 3;
    TMatrix<int> b(2);
    b = a;
    EXPECT_EQ(b.GetSize(), 3);
    EXPECT_EQ(b[0][1], 2);
    a[0][0] = 777;
    EXPECT_EQ(b[0][0], 1);
    b = b;
    EXPECT_EQ(b[0][0], 1);
    EXPECT_EQ(b[1][1], 3);
}

TEST(TMatrix, equality) {
    TMatrix<int> a(3);
    a[0][0] = 1; a[1][2] = 5;
    TMatrix<int> b(3);
    b[0][0] = 1; b[1][2] = 5;
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
    b[1][2] = 7;
    EXPECT_TRUE(a != b);
}

TEST(TMatrix, equality_different_sizes) {
    TMatrix<int> a(3);
    TMatrix<int> b(4);
    EXPECT_TRUE(a != b);
}

TEST(TMatrix, add_sub) {
    TMatrix<int> a(3);
    a[0][0] = 1; a[0][1] = 2; a[0][2] = 3;
    a[1][1] = 4; a[1][2] = 5;
    a[2][2] = 6;
    TMatrix<int> b(3);
    b[0][0] = 10; b[0][1] = 20; b[0][2] = 30;
    b[1][1] = 40; b[1][2] = 50;
    b[2][2] = 60;
    TMatrix<int> sum = a + b;
    EXPECT_EQ(sum[0][0], 11);
    EXPECT_EQ(sum[0][2], 33);
    EXPECT_EQ(sum[1][1], 44);
    EXPECT_EQ(sum[2][2], 66);
    TMatrix<int> diff = b - a;
    EXPECT_EQ(diff[0][0], 9);
    EXPECT_EQ(diff[1][2], 45);
    EXPECT_EQ(diff[2][2], 54);
}

TEST(TMatrix, add_result_structure_preserved) {
    TMatrix<int> a(4);
    TMatrix<int> b(4);
    TMatrix<int> sum = a + b;
    EXPECT_EQ(sum.GetSize(), 4);
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(sum[i].GetSize(), 4 - i);
        EXPECT_EQ(sum[i].GetStartIndex(), i);
    }
}

TEST(TMatrix, empty_matrix) {
    TMatrix<int> m(0);
    EXPECT_EQ(m.GetSize(), 0);
    TMatrix<int> sum = m + m;
    EXPECT_EQ(sum.GetSize(), 0);
    TMatrix<int> diff = m - m;
    EXPECT_EQ(diff.GetSize(), 0);
}

TEST(TMatrixConversion, valid_vector_of_vectors) {
    TVector<TVector<int>> vv(3, 0);
    vv[0] = TVector<int>(3, 0);
    vv[1] = TVector<int>(2, 1);
    vv[2] = TVector<int>(1, 2);
    TMatrix<int> m(vv);
    EXPECT_EQ(m.GetSize(), 3);
    EXPECT_EQ(m[0].GetSize(), 3);
    EXPECT_EQ(m[1].GetStartIndex(), 1);
}

TEST(TMatrixConversion, invalid_structure_throws) {
    TVector<TVector<int>> vv(3, 0);
    vv[0] = TVector<int>(3, 0);
    vv[1] = TVector<int>(3, 0);
    vv[2] = TVector<int>(3, 0);
    EXPECT_THROW(TMatrix<int> m(vv), std::out_of_range);
}

TEST(TMatrix, throw_negative_or_too_large_size) {
    EXPECT_THROW(TMatrix<int>(-1), std::out_of_range);
    EXPECT_THROW(TMatrix<int>(MAX_MATRIX_SIZE + 1), std::out_of_range);
}

TEST(TMatrix, throw_access_out_of_range) {
    TMatrix<int> m(3);
    EXPECT_THROW(m[-1], std::out_of_range);
    EXPECT_THROW(m[3], std::out_of_range);
}

TEST(TMatrix, below_diagonal_not_accessible) {
    TMatrix<int> m(3);
    EXPECT_THROW(m[1][0], std::out_of_range);
    EXPECT_THROW(m[2][0], std::out_of_range);
    EXPECT_THROW(m[2][1], std::out_of_range);
    EXPECT_NO_THROW(m[1][1]);
    EXPECT_NO_THROW(m[2][2]);
}

TEST(TMatrix, throw_incompatible_sizes) {
    TMatrix<int> a(3);
    TMatrix<int> b(4);
    EXPECT_THROW(a + b, std::invalid_argument);
    EXPECT_THROW(a - b, std::invalid_argument);
}