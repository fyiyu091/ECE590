#include <iostream>
#include "elma.h"

namespace elma {

    int State::_id_counter = 0;

    StateMachine& StateMachine::set_initial(State& s) {
        _initial = &s;
        return *this;
    }

    StateMachine& StateMachine::add_transition(string event_name, State& from, State& to) {
        _transitions.push_back(Transition(event_name, from, to));
        to._state_machine_ptr = this;
        from._state_machine_ptr = this;
        return *this;
    }

    void StateMachine::init() {
        for (auto transition : _transitions ) {
            watch(transition.event_name(), [this, transition](Event& e) {
                if ( _current->id() == transition.from().id() ) {
                    _current->exit(e);
                    _current = &transition.to();
                    _current->entry(e);
                    if ( !_propagate ) {
                      e.stop_propagation();
                    }
                }
            });
        }
    }

    void StateMachine::start() {
        if ( _initial == NULL ) { 
            throw(Exception("State machine started without an initial state (call set_initial(...) first)"));
        }
        _current = _initial;
        _current->entry(Event("start"));
    }

    void StateMachine::update() {
        _current->during();
    }

    void StateMachine::stop() {}

    json StateMachine::to_json() {
           
        json value;
        vector<std::string> t_name;
        vector<json> t_trans;
        json tmp;
        value["name"] = this->name();
        // Get the state from transition.from or transition.to
        for (int i=0; i<_transitions.size(); i++)
        {
            t_name.push_back(_transitions[i].from().name());
        }
        // then convert t_name to an array
        value["state"] = t_name;
        for (int i=0; i<_transitions.size(); i++)
        {
            tmp["from"] = _transitions[i].from().name();
            tmp["to"] = _transitions[i].to().name();
            tmp["when"] = _transitions[i].event_name();
            t_trans.push_back(tmp);
        }
        value["transitions"] = t_trans;
        return value;
        }
        

};