#include "stopwatch.h"


    void Stopwatch::_reset(){
            start_time = high_resolution_clock::now();
            time_duration = seconds_type(0);
        } 

    void Stopwatch::_stop(){
            time_duration = seconds_type(high_resolution_clock::now() - start_time);
        }

    double Stopwatch::seconds () {
        return seconds_type(high_resolution_clock::now() - start_time).count();
    }
    