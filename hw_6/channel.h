#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>
#include <deque>
#include <vector>

#include "elma.h"

namespace elma {

    using std::string;
    using std::deque;
    using std::vector;

    class Channel {

        public:

        Channel(string name) : _name(name), _capacity(100) {}
        Channel(string name, int capacity) : _name(name), _capacity(capacity) {}

        Channel& send(double);
        Channel& flush(double);
        // Q3
        void change_capacity(int);
        double latest();
        // Q2
        vector<double> latest(int);
        double earliest();
        inline int size() { return _queue.size(); }
        inline bool empty() { return _queue.size() == 0; }
        inline bool nonempty() { return _queue.size() > 0; }
        inline string name() { return _name; }
        inline int capacity() { return _capacity; }

        private:

        string _name;
        int _capacity;
        deque<double> _queue;

    };

}

#endif