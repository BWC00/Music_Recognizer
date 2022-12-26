/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file about.h
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

namespace Ui {
class About;
}

/**
 * @class About
 * @brief GUI Component displaying miscellaneous information
 */
class About : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the about window
     * @param parent
     */
    explicit About(QWidget *parent = nullptr);
    /**
     * @brief Destructor for the about window
     */
    ~About();

private slots:
    /**
     * @brief Button to close this window
     */
    void on_returnHomeButton_clicked();

private:
    Ui::About *ui;
};

#endif // ABOUT_H
