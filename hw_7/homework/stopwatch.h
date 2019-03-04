#include <iostream>
#include <chrono>
#include "elma.h"
#include <chrono>

using namespace elma;
using namespace std::chrono;
typedef std::chrono::duration<double,std::ratio<1,1>> seconds_type;

class Stopwatch : public Process {
      public:
      Stopwatch() : Process("Stopwatch") {}
      // The below functions are the standard functions of process
      // In the init, the stopwatch watch for the event
      void init() {
            watch("start", [this](Event& e) {
                 start();
            });
            watch("stop", [this](Event& e) {
                 _stop();
            });
            watch("reset", [this](Event& e){
                 _reset();
            });
        }
      void start() {
            start_time = high_resolution_clock::now();
            time_duration = seconds_type(0);
        }
      void update() {}
      void stop() {}

      // Local functions
      void _reset();
      void _stop();
      // The function to return the time_duration in the format of second
      double seconds ();

      // The declaration of the variable
      high_resolution_clock::time_point start_time;
      std::chrono::duration<double> time_duration;
};

class StopWatchUser : public Process {
      public:
      StopWatchUser() : Process("StopWatchUser") {}
      void init() {}
      void start() {}
      void update() {
           emit(Event("start"));
           emit(Event("stop"));
           emit(Event("reset"));
      }
      void stop() {}
};