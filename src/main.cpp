/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file main.cpp
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <ctime>
#include <filesystem>
#include "UI/CommandManager.h"
#include "Library/Timer.h"
#include "Audio.h"

using namespace std;

/**
 * @brief The entry point for the project.
 *
 * @return Returncode
 */
int main() {
    srand( (unsigned) time(NULL) * getpid());
    CommandManager commandManager = CommandManager();
    commandManager.printHelp(std::cout);
    string command;

    for (const string &cat : Config::MUSICGENRESSTRING) filesystem::create_directories("library/" + cat);

    while(true) {
        getline(cin, command);
        if(command == "exit")
            break;
        else if(command == "help")
            commandManager.printHelp(std::cout);
        else {
            Timer commandTimer = Timer();
            commandTimer.start();
            std::string feedback = commandManager.handle(command);
            if(!feedback.empty() && feedback != "Succes") {
                cerr << feedback << endl;
            }
            commandTimer.stop();
            cout << "Done! Command took " << commandTimer.elapsedMilliseconds() << "ms to execute." << endl;
        }
    }
    return 0;
}
