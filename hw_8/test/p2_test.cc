#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <string>
#include <chrono>
#include "gtest/gtest.h"
#include "elma.h"

namespace {

    using namespace std;
    using namespace elma;

    class DataGenerator{
        public:
            DataGenerator(int min=-5, int max=5): _min(min), _max(max) {
                srand(time(NULL));
            }
            json gen(){
                json data;
                data["x"] = _min + rand()%(_max-_min+1);
                data["y"] = _min + rand()%(_max-_min+1);
                double f = (double)rand()/RAND_MAX;
                data["temperature"] = 32 + f*(104-32);
                return data;
            }
        private:
            int _max, _min;
    };

    DataGenerator ds;

    TEST(Client, Post1) {
        Client c;
        json data = ds.gen();
        c.post("http://ECEP590-server/save", data, [this](json& response) {
        }); 
        std::this_thread::sleep_for(std::chrono::seconds(1));
        c.get("http://ECEP590-server/find/"+to_string(0), [&](json& response) {
              EXPECT_EQ((int)data["x"], (int)response["x"]);
              EXPECT_EQ((int)data["y"], (int)response["y"]);
              EXPECT_NEAR((double)data["temperature"], (double)response["temperature"], 0.1);
        });   
        std::this_thread::sleep_for(std::chrono::seconds(1));
        EXPECT_EQ(2,c.num_responses());
        c.process_responses();
    }

    TEST(Client, Post2) {
        Client c;
        for(int i=1; i<6; i++){
            json data = ds.gen();
            c.post("http://ECEP590-server/save", data, [this](json& response) {
            }); 

            std::this_thread::sleep_for(std::chrono::seconds(1));  
            
            c.get("http://ECEP590-server/find/"+to_string(i), [data](json& response) {
                EXPECT_EQ((int)data["x"], (int)response["x"]);
                EXPECT_EQ((int)data["y"], (int)response["y"]);
                EXPECT_NEAR((double)data["temperature"], (double)response["temperature"], 0.1);
            });       
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        EXPECT_EQ(10,c.num_responses());
        c.process_responses();
    }
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}