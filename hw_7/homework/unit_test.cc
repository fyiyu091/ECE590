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

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 0.5, tolerance);

    std::cout << watch.seconds() << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 1.0, tolerance);

    std::cout << watch.seconds() << std::endl;

    m.emit(Event("stop"));

}


/*!!
 * Here we use your Robot class to give the robot
 * a little trial and see what state its in.
 *
 * Variants of tests will include more than one robot,
 * non-sense events, and varying event sequences.
 */

TEST(Question2, RobotEnvironment1) {

    // create a new robot
    Robot robot = Robot("What a very nice robot");
    // Robot robot = Robot(); // << this should also work

    // init manager
    Manager m;
    m.schedule(robot, 10_ms)
    .init()
    .start()
    .emit(Event("start"));


    string wander = "Wander";
    string noise = "Make Noise";
    string evade = "Evade";

    /*
     * Send signals to robot and test
     */
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), wander.c_str());

    m.emit(Event("intruder detected"));
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), noise.c_str());

    m.emit(Event("proximity warning"));
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), evade.c_str());

    m.emit(Event("battery full"));
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), evade.c_str());
}

/*!!
 * Here we will create various StateMachines and validate the JSON from the to_json method.
 */
TEST(Question3, to_json) {
    /*
     * coming soon... but this is straight-forward to test. At this point, you shouldn't
     * need help writing tests for this one.
     */

    class tMode : public State {
    public:
    tMode(std::string name) : State(name) {}
    tMode() : State("tMode") {}
    void entry(const Event& e) {}
    void during() {}
    void exit(const Event& e) {}
    };


    StateMachine ttt;
    tMode test1("test1");
    tMode test2("test2");
    ttt.set_initial(test1);
    ttt.add_transition("good testing", test1, test2);
    ttt.add_transition("nice testing", test2, test1);
    json result = ttt.to_json();
    //EXPECT_EQ(result["name"], "unnamed state machine");
    std::cout << result.dump() << '\n';
    std::cout << result["transitions"][0] << '\n';
}

/*!!
 * Here we will test priority of watching events. Events with higher priority should always be
 * executed before events of lower priority.
 *
 * Test variants will include testing various events of lower and higher priority.
 */

class TestProcess : public Process {
    public:
        TestProcess(std::string name) : Process(name) {}
        void init() {
            watch("hello", [this](const Event& e) { 
                str = "priority 0";
            }, 0);
            watch("hello", [this](const Event& e) { 
                str = "priority 1";
            }, 1);
            watch("hello", [this](const Event& e) { 
                str = "priority 2";
            }, 2);
            watch("hello", [this](const Event& e) { 
                str = "priority 3";
            }, 3);
            watch("hello", [this](const Event& e) { 
                str = "priority 11";
            }, 1);
            watch("hello", [this](const Event& e) { 
                str = "priority 88";
            });
            

            watch("value", [this](const Event& e) { 
                x = 3;
            },3); 
            watch("value", [this](const Event& e) { 
                x = 1;
            },0);
            watch("value", [this](const Event& e) { 
                x = 9;
            },9); 


            watch("calculate", [this](const Event& e) { 
                result = 15;
            },10); 
            watch("calculate", [this](const Event& e) { 
                result+=13;
            },4); 
            watch("calculate", [this](const Event& e) { 
                result/=5;
            },8);
            watch("calculate", [this](const Event& e) { 
                result*=10;
            });          
        }
        void start() {}
        void update() { 
            emit(Event("hello"));
            std::cout << str << "\n";
            ASSERT_EQ("priority 88", str);

            emit(Event("value"));
            std::cout << x << "\n";
            ASSERT_EQ(1, x);
            emit(Event("calculate"));
            std::cout << result << "\n";
            ASSERT_EQ(160, result);
        }
        void stop() {}
    private:
        string str;
        double x;
        int result;
};

/*!!
 * Here we will test priority of watching events. Events with higher priority should always be
 * executed before events of lower priority.
 *
 * Test variants will include testing various events of lower and higher priority.
 */
TEST(Question4, WatchPriority) {
    /*
     * coming soon...
     */
     TestProcess p("WatchPriority");        
        Manager m;
        m.schedule(p,10_ms)
          .init();
        p.update();
}