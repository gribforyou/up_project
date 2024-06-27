#include "songinfowidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QDebug>

SongInfoWidget::SongInfoWidget(QWidget *parent) : QWidget(parent)
{
    scores = new ScoresWidget();
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel();
    label->setObjectName("title");
    label->setText("Song title");
    label->setMaximumHeight(50);
    layout->addWidget(label);
//    label = new QLabel();
//    label->setObjectName("cover");
//    label->setText("Song cover");
//    QPixmap pixmap;
//    pixmap.load("covers/test.png");
//    label->setMaximumWidth(500);
//    layout->addWidget(label);
//    label->setPixmap(pixmap.scaled(label->width(), label->height(), Qt::KeepAspectRatio));
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
