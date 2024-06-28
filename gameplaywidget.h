#ifndef GAMEPLAYWIDGET_H
#define GAMEPLAYWIDGET_H

#include <QWidget>
#include "songinfo.h"

class GameplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameplayWidget(QWidget *parent = 0);
    void loadLevel(SongInfo, QString);
    void startLevel();

signals:

public slots:
};

#endif // GAMEPLAYWIDGET_H
