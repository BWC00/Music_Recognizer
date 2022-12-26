/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file Audio.cpp
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#include "Audio.h"
#include <algorithm>
using namespace std;

Audio::Audio() = default;

Audio::~Audio() = default;

bool Audio::load(const std::string &fileName, bool shouldClip) {
    bool result = AudioFile::load(fileName);

    title = fileName;

    if (result) {
        if (!isMono()) {
            // Place the average of all samples on all channels onto the first channel.
            for(int i = 0; i < getNumSamplesPerChannel(); i++) {
                float sum = 0;
                for (int c = 0; c < getNumChannels(); c++) sum += samples[c][i];
                sum /= (float)getNumChannels();
                samples[0][i] = sum;
            }
            // Get rid of extraneous data in the leftover channels.
            setAudioBufferSize(1, getNumSamplesPerChannel());
        }

        if (shouldClip && getNumSamplesPerChannel() > getSampleRate()*Config::LENGTH_LIMIT_INPUT_AUDIO)
            setAudioBufferSize(1, Util::roundToInt(getSampleRate()*Config::LENGTH_LIMIT_INPUT_AUDIO));

        for (double d : samples[0]) {
            if (d < 0) continue;
            data.push_back(Config::ALPHABET.at(Util::roundToInt((d*((int)Config::ALPHABET.size()-1)))));
        }
    } else {
        title = "";
        data = "";
    }

    loaded = result;
    return result;
}

bool Audio::isLoaded() const {
    return loaded;
}

int Audio::getNumCharacters() const {
    return (int)data.size();
}

char Audio::operator[](int i) {
    assert(loaded);
    assert(i >= 0);
    assert(i < getNumCharacters());

    return data.at(i);
}

void Audio::serialise(std::ostream &writeOn, bool compressed) {
    assert(loaded);

    if (compressed) {
        char last = 0;
        int amount = 0;
        for (char current : data) {
            if (last == current) {
                amount++;
            } else {
                if (last != 0) writeOn << last << amount;
                last = current;
                amount = 1;
            }
        }
        if (last != 0) writeOn << last << amount;
    } else {
        writeOn << data;
    }
}
