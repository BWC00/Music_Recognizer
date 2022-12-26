/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file RunCmd.cpp
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#include <regex>
#include <iostream>
#include <filesystem>
#include "RunCmd.h"
#include "../Util.h"
#include "../AudioRepresentation.h"
#include "../Audio.h"
#include "../BoyerMooreAutomaton/BoyerMooreAutomaton.h"

using namespace std;

RunCmd::RunCmd() {
    arguments.insert({"filename", "Audiobestand van het geluidsfragment dat gezocht moet worden"});
    arguments.insert({"genre", "Limiteer de zoekopdracht naar enkel dit genre"});
}

std::string RunCmd::handle(vector<std::string> &args) {
    if (args.size() != 1 && args.size() != 2) return "An incorrect amount of arguments was provided!";

    Audio source;
    source.load(args[0], true);
    if (!source.isLoaded()) return "Something went wrong parsing the input file... Is it a .wav file?";

    int bmhCount = 0, bmhCounter = 0;
    map<string, int> hits;

    string genreFilter;
    if (args.size() == 2) genreFilter = args[1];
    for (auto & p : std::filesystem::recursive_directory_iterator("library")) {
        std::string filePath = p.path();
        if (filePath.size() < 4 || filePath.substr(filePath.size()-4, filePath.size()) != ".bmh") continue;
        if (!genreFilter.empty() && filePath.find(genreFilter) == string::npos) continue;
        hits[filePath] = 0;
        bmhCount++;
    }

    vector<BoyerMooreAutomaton*> bmas;

    string pattern;
    stringstream stream;
    source.serialise(stream, true);
    string full = stream.str();

    // Chop left and right from full
    for(int i = 1; i < full.size(); i++) {
        if(isalpha(full[i])) {
            full.replace(0, i, "");
            break;
        }
    }
    for(int i = full.size()-1; i > 0; i--) {
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

            cout << '\r' << bmas.size() << flush;

            pattern.clear();
        }

        pattern.push_back(full[i]);

        if (i != 0 && i % Config::AUDIO_CHOPSIZE == 0) {
            if(isalpha(full[i])) {
                shouldChop = true;
                continue;
            }

            bmas.push_back(new BoyerMooreAutomaton(pattern));

            cout << '\r' << bmas.size() << flush;

            pattern.clear();
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

            Util::printProgressBar(totalRuns*bmhCounter + runs, totalRuns*bmhCount);

            bma->restart();
        }

        bmhCounter++;
        runs = 0;
    }

    Util::printProgressBar(1, 1);
    cout << endl;

    for (auto pointer : bmas) delete pointer;

    for (auto& p : hits) {
        cout << p.first << ' ' << 100*(double)p.second/totalRuns << '%' << endl;
    }

    return "Succes";
}
