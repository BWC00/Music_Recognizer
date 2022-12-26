/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file AddSongToLibrary.h
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#ifndef ADDSONGTOLIBRARY_H
#define ADDSONGTOLIBRARY_H
#include <QDialog>

namespace Ui {
    /**
     * @class addsongtolibrary
     * QT ding
     */
class AddSongToLibrary;
}

/**
 * @class AddSongToLibrary
 * @brief Window that manages information about adding a song to the library.
 */
class AddSongToLibrary : public QDialog
{
    Q_OBJECT
    std::string pathToSong;

public:
    /**
     * Window to add song to library
     */
    explicit AddSongToLibrary(QWidget *parent = nullptr);
    /**
     * Destructor
     */
    ~AddSongToLibrary();

private slots:
    void on_ClassicalSelector_clicked();

    void on_ClassicalRockSelection_clicked();

    void on_DanceSelection_clicked();

    void on_MovieMusicSelection_clicked();

    void on_FocusSelection_clicked();

    void on_ModernRockSelection_clicked();

    void on_PopSelection_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_fileselectLib_clicked();

private:
    Ui::AddSongToLibrary *ui;
};

#endif // ADDSONGTOLIBRARY_H
