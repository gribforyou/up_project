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
    QListWidget *listWidget = new QListWidget();
    listWidget->setObjectName("difficulty");
    listWidget->setFlow(QListWidget::LeftToRight);
    listWidget->setMaximumHeight(50);
    listWidget->addItem("Easy");
    listWidget->addItem("Normal");
    listWidget->addItem("Hard");
    listWidget->setCurrentRow(0);
    layout->addWidget(listWidget);
    connect(listWidget, &QListWidget::itemDoubleClicked, this, &SongInfoWidget::emitDifficultySelected);
    layout->addWidget(scores);
}

void SongInfoWidget::loadSongInfo(SongInfo songInfo)
{
    findChild<QLabel*>("title")->setText(songInfo.getTitle());
    scores->loadSongScores(songInfo.getId());
}

void SongInfoWidget::resizeEvent(QResizeEvent *event)
{
//    QPixmap pixmap;
//    pixmap.load("covers/test.png");
//    QLabel *label = findChild<QLabel*>("cover");
    //    label->setPixmap(pixmap.scaled(label->width(), label->height(), Qt::KeepAspectRatio));
}

void SongInfoWidget::selectDifficulty()
{
    findChild<QListWidget*>("difficulty")->setFocus();
}

void SongInfoWidget::emitDifficultySelected()
{
    QString difficulty;
    int row = findChild<QListWidget*>("difficulty")->currentRow();
    if (row == 0)
        difficulty = "easy";
    else
        if (row == 1)
            difficulty = "normal";
        else
            if (row == 2)
                difficulty = "hard";
    emit difficultySelected(difficulty);
}
