#ifndef GAMEPLAYWIDGET_H
#define GAMEPLAYWIDGET_H

#include <QWidget>
#include "songinfo.h"
#include "levelviewwidget.h"
#include <vector>
#include <QTimer>
#include <QMediaPlayer>

class GameplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameplayWidget(QWidget *parent = 0);
    void loadLevel(SongInfo, QString);
    void startLevel();

private:
    QTimer timer, countInTimer;
    int interval = 25, countInTime;
    double time;
    int bpm = 172;
    LevelViewWidget *levelViewWidget;
    QMediaPlayer *songPlayer;
    void showEvent(QShowEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void updateTime();
    void countIn();

signals:

public slots:
};

#endif // GAMEPLAYWIDGET_H
