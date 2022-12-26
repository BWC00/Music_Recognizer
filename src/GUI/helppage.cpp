/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file helppage.cpp
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#include "helppage.h"
#include "ui_helppage.h"
#include "about.h"
#include "musiclibrary.h"
#include "AddSongToLibrary.h"

HelpPage::HelpPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpPage)
{
    ui->setupUi(this);
}

HelpPage::~HelpPage()
{
    delete ui;
}

void HelpPage::on_pushButton_clicked()
{
    this->close();
}


void HelpPage::on_AboutButton_clicked()
{
    About aboutSection;
    this->close();
    aboutSection.exec();
}


void HelpPage::on_OpenLibraryButton_clicked()
{
    MusicLibrary libSection;
    this->close();
    libSection.exec();
}


void HelpPage::on_AddToLibraryButton_clicked()
{
    AddSongToLibrary addSongWindow;
    this->hide();
    addSongWindow.exec();
}

