/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file LibraryCmd.h
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#ifndef TAL_TO_GROEP_LIBRARYCMD_H
#define TAL_TO_GROEP_LIBRARYCMD_H


#include "CommandHandler.h"
#include "../Audio.h"

/**
 * @class LibraryCmd
 * @brief Command that managers the audio library.
 */
class LibraryCmd: public CommandHandler {
public:
    /**
     * Default Constructor
     */
    LibraryCmd();
    /**
     * @brief Handles the library command
     * @param args library command arguments
     * @return successtring
     */
    std::string handle(std::vector<std::string> &args) override;
    /**
     * @brief Description of the command
     * @return description
     */
    std::string& getDescription() override {return description;}
    /**
     * @brief Commandsyntax
     * @return syntax to use
     */
    std::string& getSyntax() override {return syntax;}
    /**
     * @brief Command label
     * @return label to use to trigger this command
     */
    std::string& getName() override {return name;}
    /**
     * @brief Argument descriptions
     * @return map with arguments and their descriptions
     */
    std::map<std::string, std::string>& getArguments() override {return arguments;}

private:
    std::string description = "Beheert de audio library van geparste bestanden";
    std::string syntax = "add <filename> <genre>";
    std::string name = "library";
    std::map<std::string, std::string> arguments;

};


#endif //TAL_TO_GROEP_LIBRARYCMD_H
