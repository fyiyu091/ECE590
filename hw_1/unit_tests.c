#include "fraction.h"
#include "imaginary.h"
#include "gtest/gtest.h"


TEST(ExampleFracctions, Basics) {
    Fraction    a = (Fraction) { 2, 3 },
                b = (Fraction) { 4, 5 };
    EXPECT_EQ(add(a,b).num,22);
    EXPECT_EQ(add(a,b).den,15);
    EXPECT_EQ(multiply(a,b).num,8);
    EXPECT_EQ(multiply(a,b).den,15);
}

TEST(ExampleReduce, Basics) {
    Fraction    c = (Fraction) { 2, 4 },
                d = (Fraction) { 3, 39 },
                h = (Fraction) { 25, 30 };
    EXPECT_EQ(reduce(d).num,1);
    EXPECT_EQ(reduce(d).den,13);
    EXPECT_EQ(reduce(h).num,5);
    EXPECT_EQ(reduce(h).den,6);
}

TEST(ExampleReduce, Negative) {
    Fraction    a = reduce((Fraction) { 2, -4 });
    EXPECT_TRUE((a.num == 1 && a.den == -2) || (a.num == -1 && a.den == 2));
}

TEST(GradingReduce, Zero) {
    Fraction a = reduce((Fraction) { -2, 0 });
    EXPECT_EQ(a.num, 1);
    EXPECT_EQ(a.den, 0);
}

TEST(ExampleImaginaryNumbers, Add) {
    Imaginary   c = (Imaginary) { -5, -9 },
                d = (Imaginary) { 10, 4 };
    EXPECT_EQ(add(c, d).real,5);
    EXPECT_EQ(add(c, d).im,-5);
}

TEST(ExampleImaginaryNumbers, Multiply) {
    Imaginary   a = (Imaginary) { -1.1, -4 },
                b = (Imaginary) { -2, -3 };
    EXPECT_EQ(multiply(a, b).real,0);
    EXPECT_EQ(multiply(a, b).im,0);
}

TEST(ExampleImaginaryNumbers, Negate) {
    Imaginary   a = (Imaginary) { 1, 4 };
    EXPECT_EQ(negate(a).real,-1);
    EXPECT_EQ(negate(a).im,-4);
}

TEST(ExampleImaginaryNumbers, Conjugate) {
    Imaginary   a = (Imaginary) { 1, 4 };
    EXPECT_EQ(conjugate(a).real,1);
    EXPECT_EQ(conjugate(a).im,-4);
}

TEST(ExampleImaginaryNumbers, Magnitude) {
    Imaginary   a = (Imaginary) { 1, 4 };
    EXPECT_NEAR(magnitude(a), 4.1231, 0.0001);
}