#include <iostream>
#include <stdexcept>
#include "elma.h"

namespace elma {
    
    Channel& Channel::send(double value) {
        _queue.push_front(value);
        while ( _queue.size() > capacity() ) {
            _queue.pop_back();
        }
        return *this;
    }

    Channel& Channel::flush(double) {
        _queue.clear();
        return *this;
    }

    double Channel::latest() {
        if ( _queue.size() == 0 ) {
            throw std::range_error("Tried to get the latest value in an empty channel.");
        }
        return _queue.front();
    }

    double Channel::earliest() {
        if ( _queue.size() == 0 ) {
            throw std::range_error("Tried to get the earliest value in an empty channel.");
        }
        return _queue.back();        
    }

    //Q2
    vector<double> Channel::latest(int n)
    {
        vector<double> result;
        if (n > capacity())
        {
           throw std::range_error("Tried to access the range out of the capacity"); 
        }
        for (int i=0; i<n; i++)
        {
            result.push_back(_queue[i]);
        }
        return result;
    }

    //Q3    
    void Channel::change_capacity(int n)
    {
        if ( n <= 0 ) {
            throw std::range_error("The desired capacity is invalid.");
        }
        if (n > capacity())
        {
            _capacity = n;
        }
        else
        {
            int origin_size = _queue.size();
            for (int i=0; i<origin_size-n; i++)
            {
                _queue.pop_back();
            }
            _capacity = n;
        }
    }

}