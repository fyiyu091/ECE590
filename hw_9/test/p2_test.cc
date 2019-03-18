#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <string>
#include <chrono>
#include "gtest/gtest.h"
#include "elma.h"
#include "MeasureLambda.h"

namespace {

    using namespace std;
    using namespace elma;

    TEST(MeasureLambda, connection) {
        // Where should I put the post and get function, inside or outside??
        Manager m;
        MeasureLambda ml("add", 1, 2);
        m.schedule(ml, 1_s)
        .init()
        .run(20_s);

        std::cout << ml.min() << ", " << ml.max() << ", " << ml.mean() << "\n";
    }
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}