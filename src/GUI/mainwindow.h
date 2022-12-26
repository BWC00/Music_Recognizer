/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file mainwindow.h
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Main window. Always visible.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * Mainwindow constructor
     */
    MainWindow(QWidget *parent = nullptr);
    /**
     * Destructor
     */
    ~MainWindow();
    /**
     * @brief Sets progress bar to given value
     */
    void setProgressbar(int value);
    /**
     * @brief Sets progresbar visibility
     */
    void setProgressbarVisible(bool visible);
    /**
     * @brief updates label
     */
    void updateLabel(QString text);
    /**
     * @brief sets result visibility
     * @param visible
     */
    void setResultVisible(bool visible);

private slots:

    void on_fileselect_clicked();

    void on_actionOpen_library_triggered();

    void on_actionAbout_this_project_triggered();

    void on_actionAbout_this_projects_algorithm_triggered();


    void on_actionExit_triggered();

    void on_actionGet_help_window_triggered();

    void on_HelpButton_clicked();

    void on_actionAdd_to_library_triggered();

    void on_LibraryOpener_clicked();

    void on_AddToLibraryButton_clicked();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
