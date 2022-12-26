/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file ParseCmd.cpp
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#include "ParseCmd.h"
#include "../Audio.h"
#include <sstream>
#include <vector>

using namespace std;

ParseCmd::ParseCmd() {
    arguments.insert({"inputfile.wav", "Audiobestand van het geluidsfragment dat geparsed moet worden"});
    arguments.insert({"outputfile.bmh", "Bestand waar doubles naar geparsed moeten worden"});
}

std::string ParseCmd::handle(std::vector<std::string> &args){
    if(args.size() < 2)
        return "Expected two arguments!";

    std::string inputFile = args[0];

    Audio source;

    if (!source.load(inputFile)) {
        return "An error occured loading the input file. Does it exist?";
    }

    std::string outputFile = args[1];

    ofstream file;
    file.open(outputFile);

    source.serialise(file);

    file.close();

    return "Succes";
}