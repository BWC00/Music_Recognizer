/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file mainwindow.cpp
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QMovie>
#include <QPixmap>
#include "musiclibrary.h"
#include "about.h"
#include "helppage.h"
#include "songsearcherwindow.h"
#include "AddSongToLibrary.h"
#include "GuiManager.h"
#include <iostream>

/**
 * QT ding
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString name = "Music recognizer";
    QWidget::setWindowTitle(name);
    QPixmap soundWavesPix("./src/GUI/waaave.png"); // /Users/cedricleclercq/Documents/School/ta/TAL-TO-Groep/src/GUI/waaave.png
    ui->labelPic->setPixmap(soundWavesPix.scaled(450,450,Qt::KeepAspectRatio));
}

MainWindow::~MainWindow() {
    delete ui;
}

#ifdef WIN64
QString getDefaultFilePath() {
    return "C://";
}
#else
/**
 * @brief returns default path
 */
QString getDefaultFilePath() {
    return "~/";
}
#endif

void MainWindow::on_fileselect_clicked()
{
    //ui->progressBar->setValue(10);
    QString file_name = QFileDialog::getOpenFileName(this, getDefaultFilePath(), "C://", tr("Wave Audio (*.wav)"));
    std::string fileNameSTD = file_name.toStdString();
    if (!fileNameSTD.empty()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "File confirmation",
                                      "Do you want to search the following file?\n\n" + file_name,
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            //ui->progressBar->setValue(10);
            GuiManager::getInstance()->showSongSearcher();
            GuiManager::getInstance()->startSearching(fileNameSTD);
        }
    }
}

void MainWindow::on_actionOpen_library_triggered()
{
    MusicLibrary lib;
    lib.exec();
}



void MainWindow::on_actionAbout_this_project_triggered()
{
    About aboutSection;
    aboutSection.exec();
}


void MainWindow::on_actionAbout_this_projects_algorithm_triggered()
{
    About aboutSection;
    aboutSection.exec();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionGet_help_window_triggered()
{
    HelpPage help;
    help.exec();
}


void MainWindow::on_HelpButton_clicked()
{
    this->on_actionGet_help_window_triggered();
}


void MainWindow::on_actionAdd_to_library_triggered()
{
    AddSongToLibrary addSongWindow;
    addSongWindow.exec();
}


void MainWindow::on_LibraryOpener_clicked()
{
    this->on_actionOpen_library_triggered();
}


void MainWindow::on_AddToLibraryButton_clicked()
{
    this->on_actionAdd_to_library_triggered();
}

