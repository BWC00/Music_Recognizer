/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file musiclibrary.h
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include <QDialog>
#include "../AudioRepresentation.h"

namespace Ui {
class MusicLibrary;
}

/**
 * @class MusicLibrary
 * @brief Library browsing window
 */
class MusicLibrary : public QDialog
{
    Q_OBJECT

public:
    /**
     * Constructor
     */
    explicit MusicLibrary(QWidget *parent = nullptr);
    /**
     * Destructor
     */
    ~MusicLibrary();



private slots:

    void on_AddToLibraryButton_clicked();

    void on_BackButton_clicked();

    void ui_Write_Results(enum MusicGenres genre);

    void on_ClassicalTab_clicked();

    void on_ClassicalRockTab_clicked();

    void on_DanceTab_clicked();

    void on_FocusTab_clicked();

    void on_ModernRockTab_clicked();

    void on_PopTab_clicked();

    void on_MovieMusicTab_clicked();

private:
    Ui::MusicLibrary *ui;
};

#endif // MUSICLIBRARY_H
