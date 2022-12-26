/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file TestRunCmd.h
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */


#include "TestRunCmd.h"
#include <ctime>
#include <unistd.h>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <random>
#include <sstream>
#include "../BoyerMooreAutomaton/BoyerMooreAutomaton.h"

using namespace std;

TestRunCmd::TestRunCmd() {
    arguments.insert({"amount","Hoeveel strings er gemaakt moeten worden om te testen"});
    arguments.insert({"stringsize","Lengte van de teststrings"});
    arguments.insert({"--dot","Exporteer errors naar een dotfile in de testdot folder"});
}

/**
 * Get random string
 * @param len string length
 * @return
 */
string gen_random(const int len) {

    string tmp_s;
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i)
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];

    if (!tmp_s.empty())
        return tmp_s;
    else return "1";
}

string TestRunCmd::handle(std::vector<std::string> &args) {

    // Testing the new adjustments
    //string testString = "kaqtc";
    //string adjusted = "r";
    //BoyerMooreAutomaton add = BoyerMooreAutomaton(adjusted);
    //if (add.accepts(testString)) {
        //cout << "adjusted test succes" << endl;
    //}
    //string fileName = "adjusted.dot";
    //add.exportDot(fileName);

    int amount = 1000, stringSize = 15, falsePositives = 0, falseNegatives = 0, testsInclusive = 0, testsExclusive = 0;
    if (args.size() > 0)
        amount = stoi(args[0]);
    if (args.size() > 1)
        stringSize = stoi(args[1]);
    bool outputDot = args.size() > 2 && (args[2] == "--dot" || args[2] == "-d");

    stringstream outputMessage;
    for (int i = 0; i < amount; i++) {
        string test = gen_random(stringSize);
        int firstBorder = (int) rand() % test.size() + 0;
        int secondBorder = (int) rand() % test.size() + 0;
        if (0 + (rand() % (2)) == 1) {
            if (firstBorder > secondBorder) {
                swap(firstBorder,secondBorder);
            } else if (firstBorder == secondBorder) {
                if (secondBorder + 1 <= test.size()) {
                    secondBorder += 1;
                } else if (secondBorder - 1 > 0) {
                    secondBorder -= 1;
                }
            }
            string subString = test.substr(firstBorder, secondBorder);
//            cout << "Testing " << subString << " in " << test << endl;
            BoyerMooreAutomaton automato = BoyerMooreAutomaton(subString);
            if (!automato.accepts(test)) {
                falseNegatives++;
                outputMessage << "+-------------------------------------------------------+" << endl;
                outputMessage << " Pattern: " << subString << endl;
                outputMessage << " String: " << test << endl;
                outputMessage << " Expected: true" << endl << " Got: false" << endl;
                outputMessage << "+-------------------------------------------------------+" << endl << endl;
                if(outputDot) {
                    string fileName = "testdot/" + subString + ".dot";
                    automato.exportDot(fileName);
                }
            }
            testsInclusive++;
        } else {
            string wrongString = to_string(rand() % 10 + 0);
            while (test.find(wrongString) != std::string::npos) {
                wrongString += to_string(rand() % 10 + 0);
            }
            BoyerMooreAutomaton automato = BoyerMooreAutomaton(wrongString);
//            cout << "Testing " << wrongString << " in " << test << endl;
            if (automato.accepts(test)) {
                falsePositives++;
                outputMessage << "+-------------------------------------------------------+" << endl;
                outputMessage << " Pattern: " << wrongString << endl;
                outputMessage << " String: " << test << endl;
                outputMessage << " Expected: false" << endl << " Got: true" << endl;
                outputMessage << "+-------------------------------------------------------+" << endl << endl;
                if(outputDot) {
                    string fileName = "testdot/" + test + ".dot";
                    automato.exportDot(fileName);
                }
            }
            testsExclusive++;
        }
    }
    int errors = falsePositives + falseNegatives;
    cout << "+==============[ TEST SAMPLES SUMMARY ]=================+" << endl;
    cout << " Tests run: " << amount << endl;
    cout << " String size: " << stringSize << endl;
    cout << " Errors: " << errors << endl;
    cout << " False positives: " << falsePositives << " of " << testsExclusive << endl;
    cout << " False negatives: " << falseNegatives << " of " << testsInclusive << endl;
    cout << "+=======================================================+" << endl << endl;
    return outputMessage.str().empty() ? "Succes" : outputMessage.str();
}

