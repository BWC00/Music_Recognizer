/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file TestRunCmd.cpp
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#ifndef TAL_TO_GROEP_TESTRUNCMD_H
#define TAL_TO_GROEP_TESTRUNCMD_H

#include "CommandHandler.h"

/**
 * @class TestRunCmd
 * @brief This command tests the Boyer Moore Horspool automaton by generating random strings.
 */
class TestRunCmd: public CommandHandler {
public:
    TestRunCmd();
    std::string handle(std::vector<std::string> &args) override;
    std::string& getDescription() override {return description;}
    std::string& getSyntax() override {return syntax;}
    std::string& getName() override {return name;}
    std::map<std::string, std::string>& getArguments() override {return arguments;}

private:
    std::string description = "Voert het Boyer Moore algoritme uit op verschillende random strings";
    std::string syntax = "<amount> <stringsize>";
    std::string name = "testdot";
    std::map<std::string, std::string> arguments;
};


#endif //TAL_TO_GROEP_TESTRUNCMD_H
