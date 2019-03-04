#include <iostream>
#include <chrono>
#include "elma.h"

using namespace elma;

/*!
 * This is an internally used by Robot. We won't be testing this class.
 */
class RobotState : public State {
public:
    /*
     * Question 2: define a 'RobotState' that inherits from 'State'
     * Hint 1: you'll need to implement the 'virtual' methods and inherit both of
     * the 'State' constructors.
     */
    RobotState() : State("RobotState") {}
    RobotState(std::string name) : State(name) {}
    void entry(const Event& e) {}
    void during() {}
    void exit(const Event& e) {}

};


class Robot : public StateMachine {
public:
    /*
     * Implement contructors. Constructors should instantiate states
     * and transitions AND should set initial_state so that Event('start')
     * sets the Robot to state 'Wander'
     *
     * Look at code for StateMachine.h and in examples and elma/example if you need help.
     *
     * States should have the EXACT names:
     * "Recharge"
     * "Wander"
     * "Find Recharge Station"
     * "Evade"
     * Make Noise"
     *
     * Robot should respond to events with the EXACT names:
     * "found recharge station"
     * "battery full"
     * "battery low"
     * "start"
     * "reset"
     * "intruder detected"
     * "proximity warning"
     */

    Robot() : StateMachine("Robot") {
        // instantiate states 
        // How to instantiate the transitions, must to add the transitions
        add_transition("start", init_state, Wander);
        add_transition("battery full", Recharge, Wander);
        add_transition("found recharge station", Find, Recharge);
        add_transition("battery low", Wander, Find);
        add_transition("battery low", Evade, Find);
        add_transition("reset", Evade, Noise);
        add_transition("reset", Noise, Wander);
        add_transition("proximity warning", Noise, Evade);
        add_transition("intruder detected", Wander, Noise);
        set_initial(init_state);
    }

    Robot(std::string name) : StateMachine(name) {
        // instantiate states 
        // How to instantiate the transitions, must to add the transitions
        add_transition("start", init_state, Wander);
        add_transition("battery full", Recharge, Wander);
        add_transition("found recharge station", Find, Recharge);
        add_transition("battery low", Wander, Find);
        add_transition("battery low", Evade, Find);
        add_transition("reset", Evade, Noise);
        add_transition("reset", Noise, Wander);
        add_transition("proximity warning", Noise, Evade);
        add_transition("intruder detected", Wander, Noise);
        set_initial(init_state);
    }
    
private:
    /*
     * Hint: You may want to keep RobotState here since locally declared variables are destroyed
     */
    RobotState init_state = RobotState("init_state");
    RobotState Recharge = RobotState("Recharge");
    RobotState Wander = RobotState("Wander");
    RobotState Find = RobotState("Find Recharge Station");
    RobotState Evade = RobotState("Evade");
    RobotState Noise = RobotState("Make Noise");
    
};