#include "songlistwidget.h"

#include <QListWidget>
#include <QHeaderView>
#include <QLabel>
#include <QVBoxLayout>
#include <QTableWidgetItem>
#include <QDebug>
#include <QKeyEvent>

SongListWidget::SongListWidget(QWidget *parent) : QListWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Song List:");
    //layout->addWidget(label);
    //layout->addWidget(this);
    connect(this, &QListWidget::currentRowChanged, this, &SongListWidget::emitSelectedSongChanged);
    connect(this, &QListWidget::itemDoubleClicked, this, &SongListWidget::emitSongSelected);
}

void SongListWidget::showEvent(QShowEvent *event)
{
    setFocus();
}

void SongListWidget::keyPressEvent(QKeyEvent *event)
{
    //qDebug() << event->key();
    if (event->key() == 16777220) {
        emit songSelected();
        return;
    }
    if(event->key() == Qt::Key_S){
        emit settingsSignal();
        return;
    }
    if(event->key() == Qt::Key_E){
        emit exitSignal();
        return;
    }
    QListWidget::keyPressEvent(event);
}

void SongListWidget::emitSelectedSongChanged(int row)
{
    emit selectedSongChanged(row);
}

void SongListWidget::emitSongSelected()
{
    emit songSelected();
}

void SongListWidget::updateSongListWidget(const std::vector <SongInfo> &songInfoVector)
{
    this ->clear();
    for (int i = 0; i < songInfoVector.size(); i++)
        this->addItem(songInfoVector[i].getTitle());
    this->setCurrentRow(0);
}
