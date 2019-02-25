// Backbone code for HW6_Question1

#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

using namespace std::chrono;

class Stopwatch{
    public:
        typedef std::chrono::duration<double,std::ratio<1,1>> seconds_type;
        Stopwatch(){time_duration = seconds_type(0);}
        void start();              // starts the timer
        void stop();               // stops the timer
        void reset();              // sets stopwatch to zero

        double get_minutes();      // number of minutes counted
        double get_seconds();      // number of seconds counted
        double get_milliseconds(); // number of milliseconds counted
        double get_nanoseconds();  // number of nanoseconds counted
    private:
        // declare any private variable you need here, we won't access them since they are private
        high_resolution_clock::time_point start_time;
        std::chrono::duration<double> time_duration;
};

#endif