/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file GuiManager.h
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#ifndef TAL_TO_GROEP_GUIMANAGER_H
#define TAL_TO_GROEP_GUIMANAGER_H

#include <filesystem>
#include <QMessageBox>

#include "mainwindow.h"
#include "musiclibrary.h"
#include "helppage.h"
#include "songsearcherwindow.h"
#include "foundsongswindow.h"
#include "../BoyerMooreAutomaton/BoyerMooreAutomaton.h"
#include "../Audio.h"
#include "../AudioRepresentation.h"

using namespace std;


/**
 * @class GuiManager
 * @brief Management singleton for the GUI components.
 */
class GuiManager {
public:
    // Singleton
    /**
     * @brief Method to get the singleton instance
     * @return GuiManager*: singleton instance
     */
    static GuiManager* getInstance();
    /**
     * Initializes singleton
     */
    static void initializeSingleton();

    // Show
    /**
     * @brief Open the MainWindow
     */
    void showMain();
    /**
     * @brief Open the Songsearcher window with the progressbar and stop button
     */
    void showSongSearcher();

    // Hide
    /**
     * @brief Hide the Songsearcher
     */
    void hideSongSearcher();

    // Visual elements
    /**
     * @brief Fills the progress bar for the given percentage
     * @param percentage: double; Number between 0 and 1 that represents the amount of songs searched so far
     */
    void setProgressbar(double percentage);
    /**
     * @brief Sets the progress bar to the given position
     * @param current Current value.
     * @param max Goal value.
     */
    void setProgressbar(double current, double max);

    // Events
    /**
     * @brief Parse the given file and search the parsed string across the library strings
     * @param audioFile: string; Path to the audio file to parse
     */
    void startSearching(std::string &audioFile);
    /**
     * @brief Stop searching the audio file
     */
    void stopSearching();

private:
    // Singleton
    GuiManager();
    static GuiManager* instance;

    // Guis
    MainWindow mainWindow;
    MusicLibrary musicLibrary;
    HelpPage helpPage;
    SongSearcherWindow songSearcherWindow;
    FoundSongsWindow foundSongsWindow;

    bool cancelSearching;
};


#endif //TAL_TO_GROEP_GUIMANAGER_H
