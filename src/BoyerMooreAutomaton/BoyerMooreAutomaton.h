/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file BoyerMooreAutomaton.h
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#ifndef TAL_TO_GROEP_BOYERMOOREAUTOMATON_H
#define TAL_TO_GROEP_BOYERMOOREAUTOMATON_H

#include <string>
#include <vector>
#include <map>
#include "../AudioRepresentation.h"

class State;

/**
 * @class BoyerMooreAutomaton
 * @brief Briefdesc
 * Desc
 */
class BoyerMooreAutomaton {
public:
    /**
     * @brief default constructor
     */
    BoyerMooreAutomaton();
    /**
     * @brief destructor
     */
    ~BoyerMooreAutomaton();
    /**
     * @brief Constructs an automaton from a pattern
     *
     * @param pattern
     */
    explicit BoyerMooreAutomaton(const std::string &pattern);
    /**
     * @brief Loads a string in this automaton
     *
     * @param pattern
     */
    void preprocess(const std::string &pattern);
    /**
     * @brief Check if this automaton accepts a string
     *
     * @param str The input string.
     * @return bool The result after evaluation.
     */
    bool accepts(std::string &str);
    /**
     * @brief Resets the automaton
     */
    void transitionToStart();
    /**
     * @brief Gets the current state of the automaton
     *
     * @return this->currentState
     */
    State* getCurrentState();
    /**
     * @brief Operator <<
     *
     * @param c
     */
    void operator<<(char c);
    /**
     * @brief Export to a .dot file for visual representation
     *
     * @param fileName
     */
    void exportDot(std::string &fileName);
    /**
     * @brief Resets the automaton
     */
    void reset();
    /**
     * @brief Prepares the BMA for a completely new search.
     */
    void restart();

private:
    State* startState = nullptr; // Start state of the automaton
    State* currentState = nullptr; // Current state of the automaton

    std::map<State*, int> lookupTable;
    std::vector<State*> states;

    unsigned int patternSize;
};


#endif //TAL_TO_GROEP_BOYERMOOREAUTOMATON_H
