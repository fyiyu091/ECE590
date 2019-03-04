#include "gtest/gtest.h"
#include "robot.h"
#include "stopwatch.h"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include "elma.h"

using namespace std::chrono;
using namespace elma;
//using nlohmann::json;

double tolerance = 0.01;
/*!!
 * Here we use your StopWatch class to time something.
 */
TEST(Question1, StopWatch) {
    Manager m;

    Stopwatch watch = Stopwatch();

    m.schedule(watch, 10_ms)
    .init()
    .start();

    std::cout << watch.seconds() << std::endl;

    m.emit(Event("start"));
    m.emit(Event("start"));
    m.emit(Event("start"));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 0.5, tolerance);

    std::cout << watch.seconds() << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 1.0, tolerance);

    std::cout << watch.seconds() << std::endl;

    m.emit(Event("stop"));

}
