/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file foundsongswindow.h
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#ifndef FOUNDSONGSWINDOW_H
#define FOUNDSONGSWINDOW_H

#include <QDialog>
#include <sstream>
#include <iomanip>

namespace Ui {
class FoundSongsWindow;
}

/**
 * @class FoundSongsWindow
 * @brief window that shows the searchresults
 */
class FoundSongsWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param parent
     */
    explicit FoundSongsWindow(QWidget *parent = nullptr);
    /**
     * Destructor
     */
    ~FoundSongsWindow();

    /**
     * @brief display results
     * @param store results
     * @param runs amount of runs done
     */
    void displayResults(const std::map<std::string, int> &store, int runs);

private slots:
    void on_closeWindowButton_clicked();

private:
    Ui::FoundSongsWindow *ui;
};

#endif // FOUNDSONGSWINDOW_H
