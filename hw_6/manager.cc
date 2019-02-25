#include <stdexcept>
#include <iostream>
#include "elma.h"
#include <tuple>

namespace elma {

    Manager& Manager::schedule(
        Process& process, 
        high_resolution_clock::duration period) {

        process._period = period;
        _processes.push_back(&process); 
        process._manager_ptr = this;            

        return *this;

    }

    Manager& Manager::drop(Process&) {

    }

    Manager& Manager::add_channel(Channel& channel) {
        _channels[channel.name()] = &channel;
        return *this;
    }

    Channel& Manager::channel(string name) {
        if ( _channels.find(name) != _channels.end() ) {
          return *(_channels[name]);
        } else {
            throw std::domain_error("Tried to access an unregistered or non-existant channel.");
        }
    }

    Manager& Manager::all(std::function< void(Process&) > f) {
        for(auto process_ptr : _processes) {
            f(*process_ptr);
        }
        return *this;
    }

    Manager& Manager::init() {
        return all([](Process& p) { p._init();});
    }

    Manager& Manager::start() {
        return all([this](Process& p) { p._start(_elapsed) ;});
    }    

    Manager& Manager::stop() {
        return all([](Process& p) { p._stop(); });
    }    

    Manager& Manager::update() { 
        return all([this](Process& p) {
            if ( _elapsed > p.last_update() + p.period() ) {
                p._update(_elapsed);
            }
        });
    }

    Manager& Manager::run(high_resolution_clock::duration runtime) {

        _start_time = high_resolution_clock::now();
        _elapsed = high_resolution_clock::duration::zero();
        start();        

        while ( _elapsed < runtime ) {
            update();
            _elapsed = high_resolution_clock::now() - _start_time;
        }

        stop();

        return *this;

    }

    map<string, tuple<string, double, double, int>> Manager::ps(){
        map<string, tuple<string, double, double, int>> info;
        typedef enum { UNINITIALIZED, STOPPED, RUNNING } status_type;
        typedef std::chrono::duration<double,std::ratio<1,1000>> milli_type;
        string _status;
        // TODO: Question 5
        for(auto process_ptr : _processes) {
            switch(process_ptr->status())
            {
                case STOPPED: _status = "STOPPED"; break;
                case RUNNING: _status = "RUNNING"; break;
                case UNINITIALIZED: _status = "UNINITIALIZED"; break;
            }
            info[process_ptr->name()] = std::make_tuple(_status, milli_type(process_ptr->last_update()).count(), process_ptr->delta(), process_ptr->num_updates());
        }
        return info;
    }

}