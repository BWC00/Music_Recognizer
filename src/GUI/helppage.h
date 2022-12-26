/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file helppage.h
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#ifndef HELPPAGE_H
#define HELPPAGE_H

#include <QDialog>

namespace Ui {
class HelpPage;
}

/**
 * @class HelpPage
 * @brief GUI component displaying basic information on how to use the application.
 */
class HelpPage : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Create Help page
     * @param parent
     */
    explicit HelpPage(QWidget *parent = nullptr);
    /**
     * Destructor
     */
    ~HelpPage();

private slots:
    void on_pushButton_clicked();

    void on_AboutButton_clicked();

    void on_OpenLibraryButton_clicked();

    void on_AddToLibraryButton_clicked();

private:
    Ui::HelpPage *ui;
};

#endif // HELPPAGE_H
