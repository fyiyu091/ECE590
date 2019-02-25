// Backbone code for HW6_Question4

#ifndef RANDOM_FILTER_H
#define RANDOM_FILTER_H

#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>

#include "elma.h"

using std::string;
using std::vector;

namespace random_filter {
    class Random : public elma::Process {
      public: 
        // you may initialize other private data in constructor
        Random(string name) : Process(name) {}
        void init() {}
        void start() {}
        void update() {
            // TODO
            // generate a random double
            _num = (double) rand()/RAND_MAX;
            //std::cout << "the _num is " << _num << '\n';
            channel("link").send(_num);
        }
        void stop() {}
      private:
        // add any private variable you need here
        double _num;
    };


    class Filter : public elma::Process {
      public: 
        // you may initialize other private data in constructor
        Filter(std::string name, vector<double> weight) : Process(name) {_weight = weight;}
        void init() {
            // TODO 
            if (_weight.size()>channel("link").capacity())
            {
                channel("link").change_capacity(_weight.size());
            }
        }
        void start() {}
        void update() {
            // TODO
            if(channel("link").nonempty())
            {
              v.push_back(channel("link").latest());
            }
        }
        inline double value() {
            // TODO
            double result = 0;
            if (v.size()<_weight.size())
            { 
               for (int i=0; i<v.size(); i++)
               {
                 result = _weight[i]*v[i] + result;
               }
            }
            else
            {
              for (int i=0; i<_weight.size(); i++)
              {
                  result = _weight[i]*v[v.size()-_weight.size()+i] + result;
                  //std::cout << "the weight[i] is " << _weight[i] << '\n';
                  //std::cout << "the v[i] is " << v[i] << '\n';
              }
            }
            return result;
        }
        void stop() {}
      private:
        // add any private variable you need here
        vector<double> v;
        vector<double> _weight;
    };
}

#endif