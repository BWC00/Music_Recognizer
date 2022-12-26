/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file Audio.h
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#ifndef TAL_TO_GROEP_AUDIO_H
#define TAL_TO_GROEP_AUDIO_H

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <limits>
#include <cassert>

#include "Library/AudioFile.h"
#include "Util.h"

/**
 * @class Audio
 * @brief Represents a loaded audio object.
 * Contains data from a loaded audio file, provides functions for converting the audio file to a string of characters.
 */
class Audio : public AudioFile<float> {
public:
    /**
     * @brief Default constructor for an Audio object.
     */
    Audio();
    /**
     * @brief Default destructor.
     */
    ~Audio();

    /**
     * @brief Loads audio data from a file.
     * Will also reset the current position.
     *
     * @param fileName
     * @param shouldClip This requests that the method drops any extraneous audio data found to exceed the length limit configured in Util.h
     * @return Successvalue
     */
    bool load(const std::string& fileName, bool shouldClip = false);
    /**
     * @brief Returns wether or not audio is loaded.
     *
     * @return
     */
    bool isLoaded() const;

    /**
     * @brief Returns the number of characters in the string.
     *
     * @return
     */
    int getNumCharacters() const;

    /**
     * @brief Fetches the character associated with the i-th datapoint.
     *
     * @param i
     * @return
     */
    char operator[](int i);
    /**
     * @brief Serializes the entire audio file and writes it to the provided output stream.
     *
     * @param writeOn Outputstream to write data to.
     * @param compressed Wether or not the information should be compressed.
     */
    void serialise(std::ostream &writeOn, bool compressed = true);

private:
    bool loaded;
    std::string title;
    std::string data;

};


#endif //TAL_TO_GROEP_AUDIO_H
