/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file CommandManager.h
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#ifndef TAL_TO_GROEP_COMMANDMANAGER_H
#define TAL_TO_GROEP_COMMANDMANAGER_H


#include <vector>
#include "CommandHandler.h"

/**
 * @class CommandManager
 * @brief Class that keeps track of commands. Entry point for command execution.
 */
class CommandManager {
public:
    /**
     * Constructor
     */
    CommandManager();
    /**
     * Destructor
     */
    ~CommandManager();
    /**
     * @brief Handles a command
     * @param command executed command
     */
    std::string handle(std::string& command);
    /**
     * @brief Parse a command 'line' into command and args
     * @param line command line command
     * @param command label
     * @param args arguments
     */
    static void parseCommand(std::string& line, std::string& command, std::vector<std::string>& args);
    /**
     * Prints help page
     */
    void printHelp(std::ostream& stream);
private:

    std::vector<CommandHandler*> handlers;
};


#endif //TAL_TO_GROEP_COMMANDMANAGER_H
