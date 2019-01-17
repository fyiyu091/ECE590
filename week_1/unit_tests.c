#include "fraction.h"
#include "gtest/gtest.h"
#include "imaginary.h"

namespace {

    TEST(Fractions, Basics) {
        Fraction a = (Fraction) { 25, -50 };
        EXPECT_EQ(reduce(a).den,-2);
        EXPECT_EQ(reduce(a).num,1);
    }

    TEST(Imaginarys, Basics) {
        Imaginary a = (Imaginary) { 1, 2},
                  b = (Imaginary) { 3, 4 },
                  c = (Imaginary) {7, 8};
        EXPECT_EQ(add(a, b).real, 4);
        EXPECT_EQ(add(a, b).im, 6);
        EXPECT_EQ(negate(a).real, -1);
        EXPECT_EQ(negate(a).im, -2);
        EXPECT_EQ(conjugate(a).real, 1);
        EXPECT_EQ(conjugate(a).im, -2);
        EXPECT_EQ(multiply(a, b).real, -5);
        EXPECT_EQ(multiply(a, b).im, 10);
        EXPECT_NEAR(magnitude(c), 10.630145, 0.01);
    }

}
