/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file CommandHandler.h
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#ifndef TAL_TO_GROEP_COMMANDHANDLER_H
#define TAL_TO_GROEP_COMMANDHANDLER_H


#include <string>
#include <vector>
#include <map>
/**
 * @class CommandHandler
 * @brief Abstract class representing a command.
 */
class CommandHandler {
public:
    /**
     * @brief Default constructor.
     */
    CommandHandler() = default;
    /**
     * @brief Default destructor.
     */
    virtual ~CommandHandler() = default;
    /**
     * @brief Called when the command is executed
     * @param arguments command argumenten
     * @return Successtring / error
     */
    virtual std::string handle(std::vector<std::string> &arguments) = 0;
    /**
     * @return description of the command
     */
    virtual std::string& getDescription() = 0;
    /**
     * @return command syntax description
     */
    virtual std::string& getSyntax() = 0;
    /**
     * @return command name
     */
    virtual std::string& getName() = 0;
    /**
     * @return map of each argument and its description
     */
    virtual std::map<std::string, std::string>& getArguments() = 0;

};


#endif //TAL_TO_GROEP_COMMANDHANDLER_H
