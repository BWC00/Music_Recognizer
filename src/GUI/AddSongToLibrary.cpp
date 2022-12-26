/**
 * ```text
 * ╒════════════════════════════════════╕
 * │          Audio Recognizer          │
 * │         Talen en Automaten         │
 * │             UAntwerpen             │
 * ╘════════════════════════════════════╛
 * ```
 *
 * @file AddSongToLibrary.cpp
 * @authors Cédric Leclercq, Robbe Nooyens, Mohammed Shakleya, Victor van Herel
 */

#include "AddSongToLibrary.h"
#include "ui_addsongtolibrary.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QDirIterator>
#include <regex>
#include "../AudioRepresentation.h"
#include "../Audio.h"


AddSongToLibrary::AddSongToLibrary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSongToLibrary)
{
    ui->setupUi(this);
    ui->pathShower->hide();
    ui->PathLabel->hide();
}

AddSongToLibrary::~AddSongToLibrary()
{
    delete ui;
}

#ifdef WIN64
QString getDefaultFilePathLib() {
    return "C://";
}
#else
/**
 * QT ding
 * @return defaultfilepathlib
 */
QString getDefaultFilePathLib() {
    return "~/";
}
#endif



void AddSongToLibrary::on_ClassicalSelector_clicked()
{
    //ui->ClassicalRockSelection->
}


void AddSongToLibrary::on_ClassicalRockSelection_clicked()
{

}


void AddSongToLibrary::on_DanceSelection_clicked()
{

}


void AddSongToLibrary::on_MovieMusicSelection_clicked()
{

}


void AddSongToLibrary::on_FocusSelection_clicked()
{

}


void AddSongToLibrary::on_ModernRockSelection_clicked()
{

}


void AddSongToLibrary::on_PopSelection_clicked()
{

}


void AddSongToLibrary::on_pushButton_2_clicked()
{
    this->close();
}

void AddSongToLibrary::on_fileselectLib_clicked()
{
    //ui->progressBar->setValue(10);
    QString file_name = QFileDialog::getOpenFileName(this, getDefaultFilePathLib(), "C://", tr("Wave Audio (*.wav)"));
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "File confirmation", "Do you want to add the following file?\n\n" + file_name,
                                    QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        //ui->progressBar->setValue(10);
        this->pathToSong = file_name.toStdString();
        ui->pathShower->setPlainText(file_name);
        ui->pathShower->show();
        ui->PathLabel->show();
    }
}


void AddSongToLibrary::on_pushButton_clicked()
{
    QString QTitle = ui->textEdit->toPlainText();
    std::string title = QTitle.toStdString();
    MusicGenres genre;
    if (title.empty() || title == "Enter title here.") {
        QMessageBox errorMessage;
        errorMessage.setText("You did not enter a title!\nPlease enter one.");
        errorMessage.exec();
        return;
    }
    if (this->pathToSong.empty()) {
        QMessageBox errorMessage;
        errorMessage.setText("You did not select a file.\n Please select one.");
        errorMessage.exec();
        return;
    }
    if (ui->PopSelection->isChecked()) {
        genre = MusicGenres::Pop;

    } else if (ui->ModernRockSelection->isChecked()) {
        genre = MusicGenres::ModernRock;

    } else if (ui->FocusSelection->isChecked()) {
        genre = MusicGenres::Focus;

    } else if (ui->MovieMusicSelection->isChecked()) {
        genre = MusicGenres::MovieMusic;

    } else if (ui->DanceSelection->isChecked()) {
        genre = MusicGenres::Dance;

    } else if (ui->ClassicalSelector->isChecked()) {
        genre = MusicGenres::Classical;

    } else if (ui->ClassicalRockSelection->isChecked()) {
        genre = MusicGenres::ClassicalRock;
    } else {
        QMessageBox errorMessage;
        errorMessage.setText("You did not select a genre!\nPlease select one.");
        errorMessage.exec();
        return;
    }

    const std::vector<std::string> MusicGenresString =
            { "Classical", "Classical Rock", "Dance", "Focus","Modern Rock","Pop","Movie Music" };

    std::string dir = "library/" + MusicGenresString[genre];
    QDirIterator it(QString::fromStdString(dir), {"*.bmh"}, QDir::Files, QDirIterator::Subdirectories);
    while(it.hasNext()) {
        std::string fileName = it.next().toStdString();
        std::smatch matches; // All matches for the regex
        std::regex removePath("/[^/]*$"); // Regex to remove the path
        if (std::regex_search(fileName, matches, removePath)) { // Searching for matches and placing them in matches
            fileName = matches[0]; // Getting the first (and only) match
            fileName.erase(0, 1); // Erase the /, the regex above will give back /file.wav
        }
        std::regex removeExt(".[^.]*$"); // Regex to remove the extension
        fileName = std::regex_replace(fileName, removeExt, ""); // Replacing the extension with nothing
        //fileName = fileName.substr(8,fileName.back());
        std::string copyFileName = fileName;
        std::string copyTitle = title;
        transform(copyFileName.begin(), copyFileName.end(), copyFileName.begin(), ::tolower);
        transform(copyTitle.begin(), copyTitle.end(), copyTitle.begin(), ::tolower);
        if (copyFileName == copyTitle) {
            QMessageBox errorMessage;
            errorMessage.setText("A song with this title already exists in the library. \nPlease select another one.");
            errorMessage.exec();
            return;
        }
    }

    AudioRepresentation AR = AudioRepresentation(title,genre,true);
    Audio data;
    bool result = data.load(this->pathToSong);
    if (result) {
        std::ofstream * toWrite = AR.getOstream();
        data.serialise(*toWrite);
        (*toWrite).close();
        delete toWrite;
        QMessageBox happyMessage;
        happyMessage.setText("Your song was successfully added!");
        happyMessage.exec();
    } else {
        QMessageBox sadMessage;
        sadMessage.setText("There was an error loading the file. Try again?");
        sadMessage.exec();
    }
    this->close();

}



