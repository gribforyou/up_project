#include "songselectmenu.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include "songinfo.h"
#include <fstream>
#include <QStringList>
#include <string>
#include <QLabel>

SongSelectMenu::SongSelectMenu(QWidget *parent) : QWidget(parent)
{
    songInfoWidget = new SongInfoWidget();
    songListWidget = new SongListWidget();

    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    QHBoxLayout *horizontalLayout = new QHBoxLayout();

    horizontalLayout->addWidget(songInfoWidget, 2);
    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->addWidget(new QLabel("Song list:"));
    vlayout->addWidget(songListWidget);
    horizontalLayout->addLayout(vlayout, 1);
    verticalLayout->addLayout(horizontalLayout);
    horizontalLayout = new QHBoxLayout();
    QLabel *label = new QLabel();
    label->setText("Press Enter to Choose");
    label->setAlignment(Qt::AlignHCenter);
    horizontalLayout->addWidget(label);
    label = new QLabel();
    label->setText("Press S to Show Settings");
    label->setAlignment(Qt::AlignHCenter);
    horizontalLayout->addWidget(label);
    label = new QLabel();
    label->setText("Press Escape to Exit");
    label->setAlignment(Qt::AlignHCenter);
    horizontalLayout->addWidget(label);
    verticalLayout->addLayout(horizontalLayout);
    loadSongInfoVector();
    songListWidget->updateSongListWidget(songInfoVector);
    connect(songListWidget, &SongListWidget::selectedSongChanged, this, &SongSelectMenu::changeSelectedSong);
    connect(songListWidget, &SongListWidget::songSelected, songInfoWidget, &SongInfoWidget::selectDifficulty);
    connect(songInfoWidget->getDifficultListWidget(), &DifficultListWidget::difficultySelected, this, &SongSelectMenu::emitLevelSelected);
    songInfoWidget->loadSongInfo(songInfoVector[0]);
    previewPlayer.setVolume(20);
    connect(this->getSongInfoWidget()->getDifficultListWidget(), SIGNAL(backToSongs()), this, SLOT(backToSongs()));
}

void SongSelectMenu::loadSongInfoVector()
{
    std::ifstream fin("songinfo.dat");
    if (!fin) {
        qDebug() << "error!";
        return;
    };
    while (!fin.eof()) {
        std::string input;
        getline(fin, input);
        if (input != "") {
            QString songInfoLine = QString::fromStdString(input);
            QStringList songInfoList = songInfoLine.split(";");
            SongInfo songInfo;
            songInfo.setId(songInfoList[0]);
            songInfo.setTitle(songInfoList[1]);
            songInfo.setAuthor(songInfoList[2]);
            songInfo.setLength(songInfoList[3]);
            songInfoVector.push_back(songInfo);
        };
    };
}

SongListWidget *SongSelectMenu::getSongListWidget()
{
    return this->songListWidget;
}

SongInfoWidget *SongSelectMenu::getSongInfoWidget()
{
    return this->songInfoWidget;
}

int SongSelectMenu::getSelectedSong() const
{
    return selectedSong;
}

void SongSelectMenu::hideEvent(QHideEvent *event)
{
    previewPlayer.stop();
}

void SongSelectMenu::backToSongs()
{
    this->songListWidget->setFocus();
}

void SongSelectMenu::changeSelectedSong(int selectedSong)
{
    SongInfo songInfo = songInfoVector[selectedSong];
    previewPlayer.setMedia(QUrl::fromLocalFile("audio/previews/" + songInfo.getId() + ".mp3"));
    previewPlayer.play();
    songInfoWidget->loadSongInfo(songInfo);
    this->selectedSong = selectedSong;
}

void SongSelectMenu::emitLevelSelected(QString difficulty)
{
    emit levelSelected(songInfoVector[selectedSong], difficulty);
}
