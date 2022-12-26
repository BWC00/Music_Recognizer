/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file SearchCmd.h
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#ifndef TAL_TO_GROEP_SEARCHCMD_H
#define TAL_TO_GROEP_SEARCHCMD_H


#include "CommandHandler.h"

/**
 * @class SearchCmd
 * @brief This command invokes a Boyer Moore Horspool search.
 */
class SearchCmd: public CommandHandler {
public:
    SearchCmd();
    std::string handle(std::vector<std::string> &args) override;
    std::string& getDescription() override {return description;}
    std::string& getSyntax() override {return syntax;}
    std::string& getName() override {return name;}
    std::map<std::string, std::string>& getArguments() override {return arguments;}

private:
    std::string description = "Zoekt het opgegeven patroon in de opgegeven tekst";
    std::string syntax = "<patroon> <tekst> (filename.dot)";
    std::string name = "search";
    std::map<std::string, std::string> arguments;

};


#endif //TAL_TO_GROEP_SEARCHCMD_H
