/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file GuiManager.cpp
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#include "GuiManager.h"
#include <iostream>
#include <regex>
#include <QCoreApplication>

GuiManager* GuiManager::instance;

// Singleton
GuiManager *GuiManager::getInstance() {
    return GuiManager::instance;
}

void GuiManager::initializeSingleton() {
    instance = new GuiManager;
}

GuiManager::GuiManager() {
    GuiManager::instance = this;
    cancelSearching = false;
}

// Show windows

void GuiManager::showMain() {
    this->mainWindow.show();
}

void GuiManager::showSongSearcher() {
    this->songSearcherWindow.show();
    this->songSearcherWindow.setProgressbarVisible(true);
    this->songSearcherWindow.setStopButtonVisible(true);
}

void GuiManager::hideSongSearcher() {
    this->songSearcherWindow.hide();
}

void GuiManager::setProgressbar(double percentage) {
    assert(percentage >= 0);
    assert(percentage <= 1);
    this->songSearcherWindow.setProgressbar((int) percentage * 100);
}

void GuiManager::setProgressbar(double current, double max) {
    assert(current >= 0);
    assert(current <= max);
    this->songSearcherWindow.setProgressbar((int) ((current/max) * 100));
}

void GuiManager::startSearching(std::string &audioFile) {
    cancelSearching = false;

    Audio source;
    source.load(audioFile, true);
    if (!source.isLoaded()) {
        QMessageBox errorMessage;
        errorMessage.setText("That is not a valid audio file!");
        errorMessage.exec();
        return;
    }

    setProgressbar(0);
    showSongSearcher();

    QCoreApplication::processEvents();

    int bmhCount = 0, bmhCounter = 0;
    map<string, int> hits;

    for (auto & p : std::filesystem::recursive_directory_iterator("library")) {
        std::string filePath = p.path();
        if (filePath.size() < 4 || filePath.substr(filePath.size()-4, filePath.size()) != ".bmh") continue;
        hits[filePath] = 0;
        bmhCount++;
    }

    vector<BoyerMooreAutomaton*> bmas;

    string pattern;
    stringstream stream;
    source.serialise(stream, true);
    string full = stream.str();

    // Chop left and right from full
    for(int i = 1; i < (int)full.size(); i++) {
        if(isalpha(full[i])) {
            full.replace(0, i, "");
            break;
        }
    }
    for(int i = (int)full.size()-1; i > 0; i--) {
        if(isalpha(full[i])) {
            full.replace(i, full.size()-1, "");
            break;
        }
    }

    bool shouldChop = false;
    for (int i = 0; i < full.size(); i++) {
        if(shouldChop && isalpha(full[i])) {
            shouldChop = false;

            bmas.push_back(new BoyerMooreAutomaton(pattern));

            QCoreApplication::processEvents();
            if (cancelSearching) {
                for (auto p : bmas) delete p;
                return;
            }

            pattern.clear();
            break;
        }

        pattern.push_back(full[i]);

        if (i != 0 && i % Config::AUDIO_CHOPSIZE == 0) {
            if(isalpha(full[i])) {
                shouldChop = true;
                continue;
            }

            bmas.push_back(new BoyerMooreAutomaton(pattern));

            QCoreApplication::processEvents();
            if (cancelSearching) {
                for (auto p : bmas) delete p;
                return;
            }

            pattern.clear();
            break;
        }

    }

    int runs = 0, totalRuns = (int)bmas.size();

    for (auto& p : hits) {
        std::ifstream * input = AudioRepresentation::getSongDataStream(p.first);
        std::string haystack;
        (*input) >> haystack;
        (*input).close();
        delete input;

        for (auto bma : bmas) {
            if (bma->accepts(haystack)) {
                p.second++;
            }
            bma->restart();
            runs++;
            setProgressbar(totalRuns*bmhCounter + runs, totalRuns*bmhCount);
            QCoreApplication::processEvents();
            if (cancelSearching) {
                for (auto pointer : bmas) delete pointer;
                return;
            }

            bma->restart();
        }

        bmhCounter++;
        runs = 0;
    }

    setProgressbar(1);

    hideSongSearcher();

    for (auto pointer : bmas) delete pointer;

    foundSongsWindow.displayResults(hits, totalRuns);
}

void GuiManager::stopSearching() {
    cancelSearching = true;
}

// Guis
