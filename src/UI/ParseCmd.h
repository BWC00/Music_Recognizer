/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file ParseCmd.h
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#ifndef TAL_TO_GROEP_PARSECMD_H
#define TAL_TO_GROEP_PARSECMD_H


#include "CommandHandler.h"

/**
 * @class ParseCmd
 * @brief Parses a .wav file to a string in the given the output file.
 */
class ParseCmd: public CommandHandler {
public:
    ParseCmd();
    std::string handle(std::vector<std::string> &args) override;
    std::string& getDescription() override {return description;}
    std::string& getSyntax() override {return syntax;}
    std::string& getName() override {return name;}
    std::map<std::string, std::string>& getArguments() override {return arguments;}

private:
    std::string description = "Parse een audiofile naar een string en schrijf deze naar een file";
    std::string syntax = "<inputfile.wav> <outputfile.bmh>";
    std::string name = "parse";
    std::map<std::string, std::string> arguments;

};

#endif //TAL_TO_GROEP_PARSECMD_H
