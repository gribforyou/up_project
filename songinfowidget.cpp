#include "songinfowidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include <QListWidget>
#include <QListView>
#include <QSizePolicy>

SongInfoWidget::SongInfoWidget(QWidget *parent) : QWidget(parent)
{
    scores = new ScoresWidget();

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel();
    label->setObjectName("title");
    label->setText("Song title");
    label->setMaximumHeight(50);
    layout->addWidget(label);

    label = new QLabel();
    label->setObjectName("cover");
    label->setText("Song cover");

    QPixmap pixmap;
    pixmap.load("covers/test.png");
    label->setMaximumWidth(500);
    layout->addWidget(label);
    label->setPixmap(pixmap.scaled(label->width(), label->height(), Qt::KeepAspectRatio));

    difficulty = new DifficultListWidget();
    layout->addWidget(difficulty);

    connect(this->difficulty, &QListWidget::itemDoubleClicked, this, &SongInfoWidget::emitDifficultySelected);
    layout->addWidget(scores);
}

void SongInfoWidget::loadSongInfo(SongInfo songInfo)
{
    findChild<QLabel*>("title")->setText(songInfo.getTitle());
    scores->loadSongScores(songInfo.getId());
}

DifficultListWidget *SongInfoWidget::getDifficultListWidget()
{
    return this->difficulty;
}

void SongInfoWidget::selectDifficulty()
{
    this->difficulty->selectDifficulty();
}

void SongInfoWidget::emitDifficultySelected()
{
    this->difficulty->emitDifficultySelected();
}
