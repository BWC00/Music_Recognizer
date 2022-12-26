/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file CommandManager.cpp
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#include <sstream>
#include <cassert>
#include "CommandManager.h"
#include "LibraryCmd.h"
#include "SearchCmd.h"
#include "RunCmd.h"
#include "TestRunCmd.h"
#include "ParseCmd.h"

using namespace std;

void CommandManager::parseCommand(string &line, string &command, vector<string> &args) {

    if (line.empty())
        return;
    args.clear();
    stringstream cmdStream(line);
    // Get command
    getline(cmdStream, command, ' ');
    // Get arguments
    string argument;
    while (getline(cmdStream, argument, ' ')) {
        args.push_back(argument);
    }
}

void CommandManager::printHelp(ostream& stream) {
    string line = "+-------------------------------------------------------------------------------------+";
    stream <<  line << endl;
    stream << "Commands overview:" << endl;
    string indentation = "  ";
    for(auto* handler: handlers) {
        stream << indentation << handler->getName() << ' ' << handler->getSyntax() << ": " << handler->getDescription() << endl;
        for(auto& argument: handler->getArguments())
            stream << indentation << indentation << argument.first << " = " << argument.second << endl;
    }
    stream << indentation << "exit: Sluit het programma" << endl << indentation << "help: Toon een lijst met commandos" << endl;
    stream << line << endl;
}

CommandManager::CommandManager() {
    // Load all commandhandlers
    handlers.push_back(new LibraryCmd());
    handlers.push_back(new SearchCmd());
    handlers.push_back(new RunCmd());
    handlers.push_back(new TestRunCmd());
    handlers.push_back(new ParseCmd());
}

CommandManager::~CommandManager() {
    for(auto* handler: handlers) {
        delete handler;
    }
}

std::string CommandManager::handle(string &command) {
    std::string name;
    vector<string> args;
    parseCommand(command, name, args);
    for(auto* handler: handlers) {
        if(handler->getName() == name) {
            return handler->handle(args);
        }
    }
    return "Unknown command!";
}
