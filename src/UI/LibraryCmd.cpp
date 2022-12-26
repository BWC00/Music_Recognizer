/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file LibraryCmd.cpp
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#include <regex>
#include "LibraryCmd.h"
#include "../AudioRepresentation.h"

using namespace std;

LibraryCmd::LibraryCmd() {
    // Add arguments
    arguments.insert({"add", "Voeg audio bestanden toe aan de library"});
    arguments.insert({"<filename>", "Audio om toe te voegen in WAV formaat"});
    arguments.insert({"<genre>", "Audio genre om de map in de library te bepalen"});
}

string LibraryCmd::handle(vector<string> &args) {
    if(args.empty()) {
        return "There should be at least one argument!";
    }
    if(args[0] == "add") {
        if(args.size() == 1)
            return "Expected filename argument!";
        std::string filename;
        for(int i = 1; i < args.size() - 1; i++) {
            filename.append(args[i]);
            if(i == args.size() - 2) {
                break;
            }
            filename.push_back(' ');
        }
        if (not regex_match(filename.begin(),filename.end(),regex(R"(^.*\.[^\\]+$)"))) {
            return "The provided file is missing an extension. Please enter another file.";
        } else {
            if (args.size() <= 2) {
                return "A music genre was not provided. Choose out of one of the following genres:\n"
                       "Classical,ClassicalRock,Dance,Focus,ModernRock,Pop or MovieMusic";
            }
            MusicGenres genre;
            const std::vector<std::string> MusicGenresString =
                    { "classical", "classicalrock", "dance", "focus","modernrock","pop","moviemusic" };

            string genreName = args.back();
            std::transform(genreName.begin(), genreName.end(), genreName.begin(), ::tolower);
            if (genreName == "classical") {
                genre = MusicGenres::Classical;
            } else if (genreName == "classicalrock") {
                genre = MusicGenres::ClassicalRock;
            } else if (genreName == "dance") {
                genre = MusicGenres::Dance;
            } else if (genreName == "focus") {
                genre = MusicGenres::Focus;
            } else if (genreName == "modernrock") {
                genre = MusicGenres::ModernRock;
            } else if (genreName == "pop") {
                genre = MusicGenres::Pop;
            } else if (genreName == "moviemusic") {
                genre = MusicGenres::MovieMusic;
            } else {
                return "A correct music genre was not provided. Choose out of one of the following genres:\n "
                       "Classical,ClassicalRock,Dance,Focus,ModernRock,Pop or MovieMusic";
            }

            AudioRepresentation AR = AudioRepresentation(filename,genre);
            Audio data;
            cout << "filename: " << filename << endl;
            bool result = data.load(filename);
            if (!result) {
                return "An error was encountered while loading the audio data.";
            }

            std::ofstream * toWrite = AR.getOstream();
            data.serialise(*toWrite);
            (*toWrite).close();
            delete toWrite;

            return "Succes";

        }
    } else {
        return "Invalid argument!";
    }
}
