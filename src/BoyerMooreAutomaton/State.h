/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file State.h
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#ifndef AUTOMATA_STATE_H
#define AUTOMATA_STATE_H

#include <map>
#include <vector>
#include <set>
#include <string>

class State;

/**
 * Typedef TransitionMap
 */
using TransitionMap = std::map<char, State*>;

/**
 * @class State
 * @brief Represents a state in the Boyer Moore Horspool automaton.
 */
class State {
public:
    /**
     * @brief Default constructor
     */
    State();
    /**
     * @brief Constructor constructor for a state - initialises all member variables
     *
     * @param name
     * @param accepts
     * @param starts
     */
    explicit State(std::string name, bool accepts, bool starts);
    /**
     * @brief copy constructor
     *
     * @param s
     */
    explicit State(State* s);
    /**
     * @brief Finds the transitions from this object on input symbol char
     *
     * @param c
     * @return vector of states
     */
    State* transition(char c);
    /**
     * @brief Adds a transition
     *
     * @param c input symbol for this transition
     * @param s state to which the transition should be
     */
    void addTransition(char c, State* s);
    /**
     * @brief Checks if the the state has a transition on char
     *
     * @param c
     * @return bool
     */
    bool hasTransitionTo(char c);
    /**
     * @brief Returns if a state is accepting or not
     *
     * @return this->accepting
     */
    bool isAcceptingState() const;
    /**
     * @brief Returns if a state is starting or not
     *
     * @return this->starting
     */
    bool isStartingState() const;
    /**
     * @brief Sets whether or not this state is a final state
     *
     * @param accepting
     */
    void setAccepting(bool accepting = true);
    /**
     * @brief Returns the name
     *
     * @return this->name
     */
    std::string getName() const;
    /**
     * @brief Returns the transition map
     *
     * @return this->transitionMap
     */
    TransitionMap getTransitionMap() const;

private:
    std::string _name; // Name of the state
    bool _accepts = false; // Indicator for if state is accepting
    bool _start = false; // Indicator for if state is starting
    TransitionMap _transitions; // All transitions from this state
};


#endif //AUTOMATA_STATE_H
