#ifndef SONGLISTWIDGET_H
#define SONGLISTWIDGET_H

#include <QWidget>
#include <QList>
#include <QListWidget>
#include "songinfo.h"

class SongListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit SongListWidget(QWidget *parent = 0);

private:
    QList <std::pair <QString, QString>> songList;
    void showEvent(QShowEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void selectedSongChanged(int);
    void songSelected();
    void settingsSignal();
    void exitSignal();

private slots:
    void emitSelectedSongChanged(int);
    void emitSongSelected();

public slots:
    void updateSongListWidget(const std::vector <SongInfo>&);
};

#endif // SONGLISTWIDGET_H
