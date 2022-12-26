/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file RunCmd.h
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#ifndef TAL_TO_GROEP_RUNCMD_H
#define TAL_TO_GROEP_RUNCMD_H


#include "CommandHandler.h"
#include <sstream>

/**
 * @class RunCmd
 * @brief Runs a search on the library for the passed audio file.
 */
class RunCmd: public CommandHandler {
public:
    RunCmd();
    std::string handle(std::vector<std::string> &args) override;
    std::string& getDescription() override {return description;}
    std::string& getSyntax() override {return syntax;}
    std::string& getName() override {return name;}
    std::map<std::string, std::string>& getArguments() override {return arguments;}

private:
    std::string description = "Zoek het fragment in de library";
    std::string syntax = "<filename> [genre]";
    std::string name = "run";
    std::map<std::string, std::string> arguments;

};


#endif //TAL_TO_GROEP_RUNCMD_H
