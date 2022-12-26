/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file Util.h
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#ifndef TAL_TO_GROEP_UTIL_H
#define TAL_TO_GROEP_UTIL_H

#include <cmath>
#include <string>
#include <vector>

namespace Config {
    /**
     * The size of the substrings in which audio should be split when searching through the library.
     */
    const int AUDIO_CHOPSIZE = 50;
    /**
     * The alphabet of characters available to various AudioToString implementations.
     */
    const std::string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    /**
     * The genres in which music is categorised.
     * @warning The order in which these are displayed is important, but not configurable. Edit with caution.
     */
    const std::vector<std::string> MUSICGENRESSTRING =
            { "Classical", "ClassicalRock", "Dance", "Focus","ModernRock","Pop","MovieMusic" };
    /**
     * The length limit of how long audio is at max.
     */
    const double LENGTH_LIMIT_INPUT_AUDIO = 10.0;
}

namespace Util {
    /**
     * @brief Rounding function
     * Rounds doubles to ints in a mathematically correct fashion.
     *
     * @param d The double to round.
     * @return The resulting integer.
     */
    inline int roundToInt(double d) {
        return static_cast<int>(std::round(d));
    }

    /**
     * @brief Prints a progress bar.
     * This progress bar will overwrite other progress bars to simulate a singular, smooth scrolling progress bar.
     *
     * @param current The current progression
     * @param max The maximum progression (~ 100%)
     * @param barWidth The width of the bar in characters, excluding the brackets and percentage notation.
     */
    void printProgressBar(double current, double max, int barWidth = 70);
}

#endif //TAL_TO_GROEP_UTIL_H
