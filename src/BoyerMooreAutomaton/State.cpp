/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file State.cpp
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#include "State.h"

#include <map>
#include <cassert>
#include <string>
#include <utility>


State::State() = default;

State::State(std::string name, bool accepts, bool starts): _name(std::move(name)), _accepts(accepts), _start(starts) {}

State::State(State *s): _start(s->_start), _accepts(s->_accepts), _name(s->_name), _transitions(s->_transitions) {}

State *State::transition(char c) {
    // Transition to '*' if character is not defined in the transitiontable
    if(!hasTransitionTo(c)) {
        assert(hasTransitionTo('*'));
        return _transitions['*'];
    }
    return _transitions[c];
}

void State::addTransition(char c, State * s) {
    assert(s != nullptr);
    _transitions.insert({c, s});
}

bool State::hasTransitionTo(char c) {
    return _transitions.find(c) != _transitions.end();
}

bool State::isAcceptingState() const {
    return _accepts;
}

bool State::isStartingState() const {
    return _start;
}

std::string State::getName() const {
    return _name;
}

TransitionMap State::getTransitionMap() const {
    return _transitions;
}

void State::setAccepting(bool accepting) {
    this->_accepts = accepting;
}
