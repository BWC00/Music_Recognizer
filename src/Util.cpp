//
// Created by victor on 26/05/2021.
//

#include "Util.h"
#include <iostream>
#include <iomanip>

void Util::printProgressBar(double current, double max, int barWidth) {
    double progress = current/max;

    std::cout << "\r["; // Leading carriage return to write over the previously written progress bar.
    int pos = Util::roundToInt(barWidth * progress);
    for (int i = 0; i < barWidth; i++) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else if (i > pos) std::cout << " ";
    }

    std::cout << "] "
              // I obtained these output stream modifiers after consulting stackoverflow.
              << std::setw(5) << std::setprecision(1) << std::fixed
              << progress*100
              << "%" << std::flush;
}