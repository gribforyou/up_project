#ifndef GAMEPLAYWIDGET_H
#define GAMEPLAYWIDGET_H

#include <QWidget>
#include "songinfo.h"
#include "levelviewwidget.h"
#include <vector>
#include <QTimer>

class GameplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameplayWidget(QWidget *parent = 0);
    void loadLevel(SongInfo, QString);
    void startLevel();

private:
    QTimer timer;
    int interval = 25;
    double time;
    LevelViewWidget *levelViewWidget;

private slots:
    void updateTime();

signals:

public slots:
};

#endif // GAMEPLAYWIDGET_H
