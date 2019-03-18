#include "httplib/httplib.h"
#include "json/json.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include "gtest/gtest.h"

namespace {
    using namespace std;
    using nlohmann::json; 
        
    class DataSender{
        public:
            DataSender(string name, httplib::Client& cli_): fname(name), cli(cli_)  {
                read();
                send();
            }
            void read(){
                fs.open(fname, fstream::in);
                string line;
                while(getline(fs,line)){
                    stringstream ss(line);
                    json request;
                    double x,y,temp;
                    char comma;
                    ss>> x >> comma >>y >> comma >> temp;    
                    data.emplace_back(make_tuple(x,y,temp));
                }
                fs.close();
            }
            void send(){
                json request;
                for(auto el: data){
                    request["x"] = get<0>(el);
                    request["y"] = get<1>(el);
                    request["temperature"] = get<2>(el);
                    auto res = cli.Post("/save", request.dump(), "json");
                }        
            }
            int get_above(int threshold){
                int count = 0;
                for(auto el: data){
                    int temp = get<2>(el);
                    if(temp>threshold)
                        count++;
                }
                return count;
            }
        private:
            fstream fs;
            string fname;
            httplib::Client& cli;
            vector<std::tuple<int, int, int>> data;
    };
    
    httplib::Client cli("ECEP590-server", 80);
    DataSender ds("data.csv", cli);

    TEST(GET, Above1) {
        int threshold = 10;
        auto res = cli.Get(("/above/"+to_string(threshold)).c_str());
        if (res && res->status == 200) {
            json data =  json::parse(res->body);
            //std::cout << "the data is " << data << '\n';
            EXPECT_EQ(data.size(), ds.get_above(threshold));
        }        
    }
    
    TEST(GET, Above2) {
        int threshold = 28;
        auto res = cli.Get(("/above/"+to_string(threshold)).c_str());
        if (res && res->status == 200) {
            json data =  json::parse(res->body);
            EXPECT_EQ(data.size(), ds.get_above(threshold));
        }        
    }
    TEST(GET, Above3) {
        int threshold = 15;
        auto res = cli.Get(("/above/"+to_string(threshold)).c_str());
        if (res && res->status == 200) {
            json data =  json::parse(res->body);
            EXPECT_EQ(data.size(), ds.get_above(threshold));
        }        
    }
    TEST(GET, Above4) {
        int threshold = 39;
        auto res = cli.Get(("/above/"+to_string(threshold)).c_str());
        if (res && res->status == 200) {
            json data =  json::parse(res->body);
            EXPECT_EQ(data.size(), ds.get_above(threshold));
        }        
    }
    TEST(GET, Above5) {
        int threshold = 0;
        auto res = cli.Get(("/above/"+to_string(threshold)).c_str());
        if (res && res->status == 200) {
            json data =  json::parse(res->body);
            EXPECT_EQ(data.size(), ds.get_above(threshold));
        }        
    }
    
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}