#ifndef LEVELVIEWWIDGET_H
#define LEVELVIEWWIDGET_H

#include <QWidget>
#include <vector>
#include "gameplaywidget.h"

class GameplayWidget;

class LevelViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LevelViewWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event) override;
    void setupLevelView(GameplayWidget*, std::vector <bool>*, std::vector <std::vector <std::pair <int, int>>>*, double*, int*);

private:
    std::vector <std::vector <std::pair <int, int>>> *notesVector;
    int pps = 200, *offset;
    double *spb;
    std::vector <bool> *isActive;
    GameplayWidget *gameplayWidget;

signals:

public slots:
    void updateLevelView();
};

#endif // LEVELVIEWWIDGET_H
