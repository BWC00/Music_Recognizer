/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file foundsongswindow.cpp
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#include <iostream>
#include "foundsongswindow.h"
#include "ui_foundsongswindow.h"

FoundSongsWindow::FoundSongsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FoundSongsWindow)
{
    ui->setupUi(this);
}

FoundSongsWindow::~FoundSongsWindow()
{
    delete ui;
}

void FoundSongsWindow::on_closeWindowButton_clicked()
{
    this->close();
}

void FoundSongsWindow::displayResults(const std::map<std::string, int> &store, int runs) {
    std::vector<std::pair<double, std::string>> orderedResults;

    for (auto &p : store) {
        double match = 100*(double)p.second/runs;

        if (match <= 10) continue;

        std::string name;
        char last = 0;
        for (char c : p.first) {
            if (c != '/' && last != '\\') {
                name.push_back(c);
            } else {
                name.clear();
            }
            last = c;
        }
        name = name.substr(0, name.size()-4);

        auto toOrder = make_pair(match, name);
        bool inserted = false;
        for (auto it = orderedResults.begin(); it != orderedResults.end(); it++) {
            if (toOrder.first > (*it).first) {
                orderedResults.insert(it, toOrder);
                inserted = true;
                break;
            }
        }
        if (!inserted) orderedResults.push_back(toOrder);
    }

    for (const auto & p : orderedResults) std::cout << p.second << ' ' << p.first << std::endl;

    if (!orderedResults.empty()) {
        std::stringstream bestMatchTitle;
        std::stringstream toDisplay;
        bestMatchTitle << orderedResults[0].second + " (with " << std::setprecision(3) << orderedResults[0].first << "%)";
        ui->matchedSongBox->setText(QString::fromStdString(bestMatchTitle.str()));
        ui->matchedSongBox->setAlignment(Qt::AlignCenter);
        orderedResults.erase(orderedResults.begin());

        ui->resultsLabel->setVisible(true);
        ui->results->setVisible(true);

        for (const auto & p :  orderedResults) {
            toDisplay << "\"" << p.second << "\" matched the search for " << std::setprecision(3) << p.first << "%" << std::endl << std::endl;
        }
        ui->results->setText(QString::fromStdString(toDisplay.str()));
    } else {
        ui->matchedSongBox->setText(QString::fromStdString("We were unable to find any matching songs :("));
        ui->matchedSongBox->setAlignment(Qt::AlignCenter);
        ui->resultsLabel->setVisible(false);
        ui->results->setVisible(false);
    }



    this->show();
}

