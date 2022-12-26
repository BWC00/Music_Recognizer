/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file musiclibrary.cpp
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#include "musiclibrary.h"
#include "ui_musiclibrary.h"
#include "AddSongToLibrary.h"
#include <regex>
#include <QDirIterator>
#include <QScrollBar>


MusicLibrary::MusicLibrary(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::MusicLibrary) {
    ui->setupUi(this);
    this->ui_Write_Results(MusicGenres::Classical);
    ui->libIndicator->setText("Classical");
    ui->libIndicator->selectAll();
    ui->libIndicator->setAlignment(Qt::AlignCenter);
    QString name = "Music library";
    QWidget::setWindowTitle(name);
    ui->songListView->verticalScrollBar()->setValue(0);
}

MusicLibrary::~MusicLibrary() {
    delete ui;
}


void MusicLibrary::on_AddToLibraryButton_clicked() {
    AddSongToLibrary window;
    window.exec();
}


void MusicLibrary::on_BackButton_clicked() {
    this->close();
}

void MusicLibrary::ui_Write_Results(enum MusicGenres genre) {
    ui->songListView->clear();
    const std::vector<std::string> MusicGenresString =
            {"Classical", "ClassicalRock", "Dance", "Focus", "ModernRock", "Pop", "MovieMusic"};
    QString QGenreName = QString::fromStdString(MusicGenresString[genre]);
    ui->libIndicator->setText(QGenreName);
    ui->libIndicator->setAlignment(Qt::AlignCenter);
    std::string dir = "library/" + MusicGenresString[genre];
    QDirIterator it(QString::fromStdString(dir), {"*.bmh"}, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        std::string fileName = it.next().toStdString();
        std::smatch matches; // All matches for the regex
        std::regex removePath("/[^/]*$"); // Regex to remove the path
        if (std::regex_search(fileName, matches, removePath)) { // Searching for matches and placing them in matches
            fileName = matches[0]; // Getting the first (and only) match
            fileName.erase(0, 1); // Erase the /, the regex above will give back /file.wav
        }
        std::regex removeExt(".[^.]*$"); // Regex to remove the extension
        fileName = std::regex_replace(fileName, removeExt, ""); // Replacing the extension with nothing
        fileName += "\n"; // Include spacing
        //fileName = fileName.substr(8, fileName.back());
        //fileName.erase(fileName.begin(),8);
        QString QFileName = QString::fromStdString(fileName);
        ui->songListView->append(QFileName);
    }
    QFont font("fontSongTitles");
    font.setStyleHint(QFont::Helvetica);
    font.setPixelSize(15);
    ui->songListView->setFont(font);
    ui->songListView->verticalScrollBar()->setValue(0);
}


void MusicLibrary::on_ClassicalTab_clicked() {
    this->ui_Write_Results(MusicGenres::Classical);
}


void MusicLibrary::on_ClassicalRockTab_clicked() {
    this->ui_Write_Results(MusicGenres::ClassicalRock);
}


void MusicLibrary::on_DanceTab_clicked() {
    this->ui_Write_Results(MusicGenres::Dance);
}


void MusicLibrary::on_FocusTab_clicked() {
    this->ui_Write_Results(MusicGenres::Focus);
}


void MusicLibrary::on_ModernRockTab_clicked() {
    this->ui_Write_Results(MusicGenres::ModernRock);
}


void MusicLibrary::on_PopTab_clicked() {
    this->ui_Write_Results(MusicGenres::Pop);
}


void MusicLibrary::on_MovieMusicTab_clicked() {
    this->ui_Write_Results(MusicGenres::MovieMusic);
}

