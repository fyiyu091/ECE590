//
// Created by Justin Vrana on 2019-02-04.
//

#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <stdlib.h>
#include "gtest/gtest.h"
#include "utilities.h"
#include "typed_matrix.h"
#include <fstream>
using std::string;

/*
 * Sort by magnitude. Should be straight forward here.
 */
TEST(Question1, call_sort_by_magnitude) {
    std::vector<double> v;
    v.push_back(-1.0);
    v.push_back(22.2);
    v.push_back(0.0);
    v.push_back(-1000.1);

    std::vector<double> sorted = sort_by_magnitude(v);

    ASSERT_DOUBLE_EQ(sorted[0], 0.0);
    ASSERT_DOUBLE_EQ(sorted[1], -1.0);
    ASSERT_DOUBLE_EQ(sorted[2], 22.2);
    ASSERT_DOUBLE_EQ(sorted[3], -1000.1);
}

TEST(Question3, read_matrix_csv) {
    TypedMatrix<double> m = read_matrix_csv("example.csv");
    ASSERT_EQ(m.rows(), 2);
    ASSERT_EQ(m.cols(), 3);
    ASSERT_DOUBLE_EQ(m.get(0, 1), 23.34);
}


TEST(Question3, read_file_that_doesnt_exist) {
    EXPECT_ANY_THROW(read_matrix_csv("doesnotexist.csv"));
}

TEST(Question3, read_invalid_file) {
    string path = "invalid.csv";

    // exists
    std::ifstream ifs;
    ifs.open (path, std::ifstream::in);
    ASSERT_TRUE(ifs.good());
    ifs.close();

    EXPECT_ANY_THROW(read_matrix_csv("invalid.csv"));
}

TEST(Question4, write_matrix_csv) {
    TypedMatrix<double> m = TypedMatrix<double>(2,4);
    m.set(0,0,4.5);
    m.set(0,1,5.555);
    write_matrix_csv(m, "out.csv");
}

TEST(Question4, write_and_then_read_matrix_csv) {
    TypedMatrix<double> m = TypedMatrix<double>(2,4);
    m.set(0,0,4.5);
    m.set(0,1,5.555);

    string outpath = "mymatrix.csv";
    write_matrix_csv(m, outpath);

    TypedMatrix<double> m2 = read_matrix_csv(outpath);

    ASSERT_EQ(m2.rows(), m.rows());
    ASSERT_EQ(m2.cols(), m.cols());

    for (int i = 0; i < m.rows(); i++) {
        for (int j = 0; j < m.cols(); j++) {
            EXPECT_EQ(m.get(i, j), m2.get(i, j));
        }
    }
}


TEST(Question5, occurrence_map) {
    std::map<string, int> m = occurrence_map("in.txt");

    EXPECT_EQ(m["S&P"], 0); // not a valid word
    EXPECT_EQ(m["500"], 2); // numbers are ok
    EXPECT_EQ(m["the"], 6);
    EXPECT_EQ(m["exchange"], 1); // "Exchange." converted to 'exchange'
    EXPECT_EQ(m["says"], 1);
    EXPECT_EQ(m["wikipedia"], 1);
    EXPECT_EQ(m["Wikipedia"], 0); // keys should be lower case
    EXPECT_EQ(m["sp500"], 1); // this is OK
}