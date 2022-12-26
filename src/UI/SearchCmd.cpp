/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file SearchCmd.cpp
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#include <regex>
#include <iostream>
#include "SearchCmd.h"
#include "../AudioRepresentation.h"
#include "../BoyerMooreAutomaton/BoyerMooreAutomaton.h"

using namespace std;

SearchCmd::SearchCmd() {
    // Add arguments
    arguments.insert({"patroon", "Substring om te zoeken in de tekst"});
    arguments.insert({"tekst", "Tekst waarin het patroon gezocht moet worden"});
    arguments.insert({"filename.dot", "Bestand waarnaar het Boyer Moore automaat geschreven moet worden"});
}

string SearchCmd::handle(vector<string> &args) {
    if(args.size() < 2) {
        return "There should be at least 2 arguments!";
    }
    string pattern = args[0];
    string text = args[1];
    BoyerMooreAutomaton automaton = BoyerMooreAutomaton(pattern);
    if(args.size() > 2) {
        string arg3 = args[2];
        if(arg3.find(".dot") != std::string::npos) {
            automaton.exportDot(arg3);
        }
    }
    cout << "Resultaat: " << boolalpha << automaton.accepts(text) << endl;
    return "Succes";
}
