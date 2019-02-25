// Backbone code for HW6_Question1
#include "stopwatch.h"
#include <iostream>

void Stopwatch::start(){
    typedef std::chrono::duration<double,std::ratio<1,1>> seconds_type;
    start_time = high_resolution_clock::now();
}

void Stopwatch::stop(){
    typedef std::chrono::duration<double,std::ratio<1,1>> seconds_type;
    time_duration = seconds_type(high_resolution_clock::now() - start_time) + time_duration;
}

void Stopwatch::reset(){
    typedef std::chrono::duration<double,std::ratio<1,1>> seconds_type;
    start_time = high_resolution_clock::now();
    time_duration = seconds_type(0);
}

double Stopwatch::get_minutes(){
    typedef std::chrono::duration<double,std::ratio<60,1>> minutes_type;
    return minutes_type(time_duration).count();
}

double Stopwatch::get_seconds(){
    return time_duration.count();
}

double Stopwatch::get_milliseconds(){
    typedef std::chrono::duration<double,std::ratio<1,1000>> milli_type;
    return milli_type(time_duration).count();
}

double Stopwatch::get_nanoseconds(){
    typedef std::chrono::duration<double,std::ratio<1,1000000000>> nano_type;
    return nano_type(time_duration).count();
}
