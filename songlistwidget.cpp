#include "songlistwidget.h"

#include <QListWidget>
#include <QHeaderView>
#include <QLabel>
#include <QVBoxLayout>
#include <QTableWidgetItem>
#include <QDebug>

SongListWidget::SongListWidget(QWidget *parent) : QWidget(parent)
{
    listWidget = new QListWidget();
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel();
    label->setText("Song List:");
    layout->addWidget(label);
    layout->addWidget(listWidget);
    connect(listWidget, &QListWidget::currentRowChanged, this, &SongListWidget::emitSelectedSongChanged);
}

void SongListWidget::resizeEvent(QResizeEvent *event)
{
}

void SongListWidget::emitSelectedSongChanged(int row)
{
    emit selectedSongChanged(row);
}

void SongListWidget::updateSongListWidget(const std::vector <SongInfo> &songInfoVector)
{
    listWidget->clear();
    for (int i = 0; i < songInfoVector.size(); i++)
        listWidget->addItem(songInfoVector[i].getTitle());
    listWidget->setCurrentRow(0);
}
