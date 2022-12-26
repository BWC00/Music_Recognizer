/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file AudioRepresentation.cpp
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#include "AudioRepresentation.h"
#include "Util.h"
#include <iostream>
#include <fstream>
#include <regex>


AudioRepresentation::AudioRepresentation(const std::string &path, enum MusicGenres genre, bool isTitle) {
    this->_genre = genre;
    if (not isTitle) {
        std::smatch matches; // All matches for the regex
        this->_title = path; // Title itself is const
        std::regex removePath("/[^/]*$"); // Regex to remove the path
        if (std::regex_search(this->_title, matches, removePath)) { // Searching for matches and placing them in matches
            this->_title = matches[0]; // Getting the first (and only) match
            this->_title.erase(0, 1); // Erase the /, the regex above will give back /file.wav
        } else {
            this->_title = path;
        }
        std::regex removeExt(".[^.]*$"); // Regex to remove the extension
        this->_title = std::regex_replace(this->_title, removeExt, ""); // Replacing the extension with nothing
        if (!this->_title.empty()) { // If the title is not empty
            this->addTitleToLibrary(); // Add to library
        } else {
            std::cerr << "A file without an extension was provided." << std::endl;
        }
    } else {
        this->_title = path;
        this->addTitleToLibrary();
    }
}

void AudioRepresentation::addTitleToLibrary() {
    const std::vector<std::string> MusicGenresString =
            { "Classical", "ClassicalRock", "Dance", "Focus","ModernRock","Pop","MovieMusic" };
    std::string title = "library/" + MusicGenresString[this->_genre] + "/" + this->_title + ".bmh";
    std::fstream file(title,std::fstream::out);
    //file.open(title);
    //file << this->_title << "\n";
    //file.close();
}

void AudioRepresentation::addData(const std::string& data) {
    std::string fileLocation = "library/" + Config::MUSICGENRESSTRING[this->_genre] + "/" + this->_title + ".bmh";
    std::ofstream file;
    file.open(fileLocation, std::ios::app);
    file << data;
    file.close();
}

void AudioRepresentation::open(const std::string& title) {
    //this->_title = title;
}

std::ofstream * AudioRepresentation::getOstream() {
    std::string fileLocation = "library/" + Config::MUSICGENRESSTRING[this->_genre] + "/" + this->_title + ".bmh";
    auto * file = new std::ofstream();
    file->open(fileLocation, std::ios::out);
    return file;
}

std::ifstream * AudioRepresentation::getSongDataStream(const std::string& fileName) {
    auto * fileData = new std::ifstream();
    fileData->open(fileName);
    return fileData;
}
