#ifndef _MEASURELAMBDA_H
#define _MEASURELAMBDA_H

#include "elma.h"
#include <string>
#include <tuple>
#include <chrono>
#include <json/json.h>

using nlohmann::json;
typedef std::chrono::duration<double,std::ratio<1,1>> seconds_type;

namespace elma {

    // Here is my node.JS lambda function~~~~~~~~~~~~~~~~ 
    /*
    exports.handler = async (event) => {
    let x = "";
    let y = "";
    let op = "";
    var result;
    try {
      x = JSON.parse(event.body).x;
      y = JSON.parse(event.body).y;
      op = JSON.parse(event.body).op;
      if (op == "multiply") {
          result = parseInt(x)*parseInt(y);
      }
      else if (op == "add") {
          result = parseInt(x)+parseInt(y);
      }
      else if (op == "subtract") {
          result = parseInt(x)-parseInt(y);
      }
      else if (op == "divide") {
          result = parseInt(x)/parseInt(y);
      }
      else {
          result = "unknown operations";
      }
    } catch(e) {
      result = "error: " + e;
    }
    const response = {
        statusCode: 200,
        body: JSON.stringify({ result: result })
    };
    return response;
    };
    */
    class MeasureLambda : public Process {
        public:
        // Add the constructor for measurelambda
        // Need to use client post and get method for send data to AWS lambda and receive the data back from lambda
        MeasureLambda(std::string op, double x, double y) {
            data["x"] = x;
            data["y"] = y;
            data["op"] = op;
        }

        void init() {
            lamclient.post("https://bz7mzpduj7.execute-api.us-east-2.amazonaws.com/default/testing_func", data, [](json& response) {           
            }); 
            start_time = high_resolution_clock::now();
            time_duration = seconds_type(0);
            
        }
        void start() {}
        void update() {
            lamclient.get("https://bz7mzpduj7.execute-api.us-east-2.amazonaws.com/default/testing_func", [](json& response) {
                EXPECT_EQ(3, (int)response["result"]);
            }); 
            time_duration = high_resolution_clock::now() - start_time;
            time_vector.push_back(time_duration);
        }
        void stop() {}

        // Using client function to post and get the values from the lambda function

        double min() {
            std::chrono::duration<double> min;
            for (int i=0; i<time_vector.size(); i++)
            {
                 if (time_vector[i] < min) {
                     min = time_vector[i];
                 }
            }
            return min.count();}

        double max() {
            std::chrono::duration<double> max;
            for (int i=0; i<time_vector.size(); i++)
            {
                 if (time_vector[i] < max) {
                     max = time_vector[i];
                 }
            }
            return max.count();}

        double mean() {
            double sum = 0;
            for (int i=0; i<time_vector.size(); i++)
            {
                 sum = time_vector[i].count() + sum;
            }
            return sum/time_vector.size();}

        private:
        json data;
        high_resolution_clock::time_point start_time;
        std::chrono::duration<double> time_duration;
        std::vector<std::chrono::duration<double>> time_vector;
        Client lamclient;

    };

}

#endif