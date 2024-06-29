#ifndef GAMEPLAYWIDGET_H
#define GAMEPLAYWIDGET_H

#include <QWidget>
#include "songinfo.h"
#include "levelviewwidget.h"
#include <vector>
#include <QTimer>
#include <QMediaPlayer>

class LevelViewWidget;

class GameplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameplayWidget(QWidget *parent = 0);
    bool loadLevel(SongInfo, QString);
    void startLevel();
    double getSongTime();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    QTimer timer, countInTimer;
    int interval = 25, countInTime;
    double time;
    int bpm, offset;
    double spb;
    LevelViewWidget *levelViewWidget;
    QMediaPlayer songPlayer;
    std::vector <QMediaPlayer*> tapSoundPlayers;
    void showEvent(QShowEvent *event);
    std::vector <bool> isActive;
    std::vector <std::vector <std::pair <int, int>>> notesVector;
    void hideEvent(QHideEvent *event);

private slots:
    void updateTime();
    void countIn();

signals:

public slots:
};

#endif // GAMEPLAYWIDGET_H
