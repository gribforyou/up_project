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
    horizontalLayout->addWidget(songListWidget, 1);
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
    connect(songInfoWidget, &SongInfoWidget::difficultySelected, this, &SongSelectMenu::emitLevelSelected);
    songInfoWidget->loadSongInfo(songInfoVector[0]);
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

void SongSelectMenu::changeSelectedSong(int song)
{
    songInfoWidget->loadSongInfo(songInfoVector[song]);
    selectedSong = song;
}

void SongSelectMenu::emitLevelSelected(QString difficulty)
{
    emit levelSelected(songInfoVector[selectedSong], difficulty);
}
