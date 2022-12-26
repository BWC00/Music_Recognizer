/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file songsearcherwindow.cpp
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#include "songsearcherwindow.h"
#include "ui_songsearcherwindow.h"
#include "GuiManager.h"
#include <QMessageBox>

SongSearcherWindow::SongSearcherWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SongSearcherWindow)
{
    ui->setupUi(this);
    QString name = "Searching...";
    QWidget::setWindowTitle(name);
}

SongSearcherWindow::~SongSearcherWindow()
{
    delete ui;
}

void SongSearcherWindow::setStopButtonVisible(bool visible) {
    ui->stop->setVisible(visible);
}

void SongSearcherWindow::setProgressbar(int value) {
    ui->progressBar->setValue(value);
}

void SongSearcherWindow::setProgressbarVisible(bool visible) {
    ui->progressBar->setVisible(visible);
}

void SongSearcherWindow::updateLabel(QString text) {
    //ui->result->setText(text);
}

void SongSearcherWindow::setResultVisible(bool visible) {
    //ui->result->setVisible(visible);
}

void SongSearcherWindow::on_stop_clicked()
{
    QMessageBox::StandardButton reply;
          reply = QMessageBox::question(this, "Stop searching", "Are you sure that you want to stop searching?\nYou might miss out on the super cool, amazing songs our application will find :(.\nDon't worry, we won't take it personally.",
                                        QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        GuiManager::getInstance()->stopSearching();
        this->close();
    }

}

