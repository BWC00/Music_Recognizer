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

#include "mainwindow.h"
#include "GuiManager.h"
#include "../Util.h"

#include <QApplication>
#include <filesystem>
#include <string>

/**
 * Main function
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    for (const std::string &cat : Config::MUSICGENRESSTRING) std::filesystem::create_directories("library/" + cat);
    QApplication a(argc, argv);
    GuiManager::initializeSingleton();
    GuiManager::getInstance()->showMain();
//    MainWindow w;
//    w.show();

    return a.exec();
}
