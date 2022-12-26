/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file BoyerMooreAutomaton.cpp
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#include <cassert>
#include <fstream>
#include "BoyerMooreAutomaton.h"
#include "State.h"
#include <list>
#include <algorithm>
#include <iostream>
#include <sstream>

/**
 * @brief Macro to check if an item is in a vector.
 */
#define VECTOR_CONTAINS(vector, item) (std::find(vector.begin(), vector.end(), item) != vector.end())

using namespace std;

BoyerMooreAutomaton::BoyerMooreAutomaton() = default;

// Algorithm based on https://www.youtube.com/watch?v=PHXAOKQk2dw
void BoyerMooreAutomaton::preprocess(const string &pattern) {
    assert(!pattern.empty());

    // Reverse pattern
    string reversedPattern = pattern;
    reverse(reversedPattern.begin(), reversedPattern.end());

    // Save pattern size so we know where to start
    patternSize = (unsigned int) pattern.size();

    // Map each character to an int that represents the amount of chars we can skip on mismatch
    map<char, int> lookupChars;
    int size = (int)pattern.size();
    // Initially map last character to size
    lookupChars[pattern.back()] = size;
    // Map each character to size - i - 1
    for(int i = 0; i < size-1; i++) {
        lookupChars[pattern[i]] = max(size - i - 1, 1); //
    }


    // Create start state
    stringstream startName;
    startName << "Start (" << size << ")";
    this->startState = new State(startName.str(), false, true);
    lookupTable[this->startState] = size;
    this->currentState = startState;
    // Add transition to itself
    this->startState->addTransition('*', this->startState);

    char firstChar = reversedPattern.front();
    int firstCharValue = lookupChars[firstChar];

    // Create default lookup table
    map<char, State*> lookupTableStates;
    for(auto &charEntry: lookupChars) {
        // Skip lookuptable for first character
        if(charEntry.first == firstChar)
            continue;
        stringstream name;
        name << "LookupTable_" << charEntry.first << " (" << charEntry.second << ")";
        auto* state = new State(name.str(), false, false);
        state->addTransition('*', startState);
        if(charEntry.first != reversedPattern.front()) {
            // Prevent transition from startstate to lookuptablestate with first letter
            startState->addTransition(charEntry.first, state);
            // Prevent transition to same Lookuptablestate on first character match
            state->addTransition(charEntry.first, state);
        }
        lookupTable[state] = charEntry.second;
        lookupTableStates[charEntry.first] = state;
        states.push_back(state);
    }

    // Chain states
    State* previous = this->startState;
    State* current;
    State* firstCharState;
    for (int i = 0; i < size; i++) {
        char ch = reversedPattern[i];

        // Create matching state
        stringstream name;
        name << "Matched_" << ch << " (" << -1 << ")";
        current = new State(name.str(), false, false);
        lookupTable[current] = -1;
        if (previous == this->startState) {
            firstCharState = current; // Saving a pointer to the state directly after the start state
        }
        previous->addTransition(ch, current);

        // Create mismatch state
        if(i < size-1) {
            int skipAmount = firstCharValue + i + 1;
            stringstream misName;
            misName << "Mismatched_" << i << " (" << skipAmount << ")";
            auto* mismatch = new State(misName.str(), false, false);
            lookupTable[mismatch] = skipAmount;
            // Add transitions
            current->addTransition('*', mismatch);
            mismatch->addTransition(firstChar, firstCharState);
            mismatch->addTransition('*', startState);
            for(auto& pair: lookupTableStates) {
                mismatch->addTransition(pair.first, pair.second);
            }
        }

        this->states.push_back(current);
        previous = current;
    }
    // Make the last chained state the accepting state
    current->setAccepting();
    current->addTransition('*', current);

    for(auto &pair: lookupTableStates) {
        // Link lookupTableStates to second character
        pair.second->addTransition(reversedPattern.front(), firstCharState);
        for(auto &linkTo: lookupTableStates) {
            if(pair.first == linkTo.first && linkTo.first != reversedPattern.front())
                continue;
            pair.second->addTransition(linkTo.first, linkTo.second);
        }
    }

    assert(this->startState != nullptr);
    assert(this->currentState != nullptr);
}

/**
 * Extract states into a vector
 */
void extractStates(State* state, vector<State*> &visitedStates, map<State*, map<char, State*>> &transitions) {
    if(VECTOR_CONTAINS(visitedStates, state))
        return;
    visitedStates.push_back(state);
    for(auto transition: state->getTransitionMap()) {
        transitions[state].insert(transition);
        extractStates(transition.second, visitedStates, transitions);
    }
}

void BoyerMooreAutomaton::exportDot(string &fileName) {
    assert(this->startState != nullptr);
    assert(!fileName.empty());
    ofstream file;
    file.open(fileName.c_str());
    assert(file.is_open());

    // Export begin
    file << "digraph BoyerMoore {" << endl;
    file << "  rankdir = \"LR\";" << endl;

    vector<State*> visitedStates;
    map<State*, map<char, State*>> transitions;
    extractStates(this->startState, visitedStates, transitions);

    for(int i = 0; i < visitedStates.size(); i++) {
        State* state = visitedStates[i];
        string shape = (state->isAcceptingState() ? "doublecircle" : "circle");
        file << "  " << i << " [label=\"" << state->getName() << "\" shape=\"" << shape << "\"];" << endl;
        if(state->isStartingState()){
            std::string name = "startarrow";
            name += to_string(i);
            file << "  " << name << " [style=invis];" << endl << "  " << name << " -> " << i << ";" << endl;
        }
        for(auto transition: transitions[state]) {
            int index = 0;
            while(visitedStates[index] != transition.second && index < visitedStates.size()) {
                index++;
                if (index == visitedStates.size()) {
                    cerr << "Error: invalid reference in transition function from " << state->getName() << " with "
                         << transition.first;
                    continue;
                }
            }
            file << "  " << i << " -> " << index << " [label=\"" << transition.first << "\"];" << endl;
        }

    }
    // Export end
    file << "}" << endl;

    file.close();
    assert(!file.is_open());
}

void BoyerMooreAutomaton::transitionToStart() {
    assert(this->startState != nullptr);
    this->currentState = this->startState;
}

State *BoyerMooreAutomaton::getCurrentState() {
    return currentState;
}

void BoyerMooreAutomaton::operator<<(char c) {
    assert(this->currentState != nullptr);
    this->currentState = this->currentState->transition(c);
}

bool BoyerMooreAutomaton::accepts(string &str) {
    assert(this->currentState != nullptr);
    assert(!str.empty());
    if(str.size() < patternSize)
        return false;
    transitionToStart();
    char* begin = str.begin().base();
    char* end = str.end().base();
    char* ptr = begin;
    ptr += patternSize - 1;
    while(ptr >= begin && ptr <= end) {
//        cout << "BoyerMooreAutomaton " << *ptr << endl;
        *this << *ptr;
        ptr += lookupTable[currentState];
        if(currentState->isAcceptingState())
            return true;
    }
    return false;
}

BoyerMooreAutomaton::BoyerMooreAutomaton(const std::string &pattern) {
    this->preprocess(pattern);
}

BoyerMooreAutomaton::~BoyerMooreAutomaton() {
    for(auto* state: states) {
        delete state;
    }
}

void BoyerMooreAutomaton::reset() {
    for(auto* state: states) {
        delete state;
    }
    states.clear();
    lookupTable.clear();
    currentState = nullptr;
    startState = nullptr;
    patternSize = 0;
}

void BoyerMooreAutomaton::restart() {
    currentState = startState;
}
