/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file songsearcherwindow.h
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#ifndef SONGSEARCHERWINDOW_H
#define SONGSEARCHERWINDOW_H

#include <QDialog>

namespace Ui {
    /**
     * @class SongSearcherWindow
     */
class SongSearcherWindow;
}

/**
 * @class SongSearcherWindow
 * @brief GUI Component that informs the user of the progression of a search action.
 */
class SongSearcherWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * Constructor
     */
    explicit SongSearcherWindow(QWidget *parent = nullptr);
    /**
     * Destructor
     */
    ~SongSearcherWindow();
    /**
     * @brief Set stop button visibility
     */
    void setStopButtonVisible(bool visible);

    /**
     * @brief Set progress bar value
     */
    void setProgressbar(int value);

    /**
     * @brief Set progress bar visibility
     */
    void setProgressbarVisible(bool visible);

    /**
     * @brief updates label
     */
    void updateLabel(QString text);

    /**
     * Set results visibility
     */
    void setResultVisible(bool visible);


private slots:
    void on_stop_clicked();

private:
    Ui::SongSearcherWindow *ui;
};

#endif // SONGSEARCHERWINDOW_H
