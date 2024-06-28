#ifndef SONGINFOWIDGET_H
#define SONGINFOWIDGET_H

#include <QWidget>
#include "difficultlistwidget.h"
#include "scoreswidget.h"
#include "songinfo.h"

class SongInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SongInfoWidget(QWidget *parent = 0);
    void loadSongInfo(SongInfo);
    DifficultListWidget* getDifficultListWidget();
private:
    DifficultListWidget* difficulty;
    ScoresWidget *scores;

signals:
    void difficultySelected(QString);

public slots:
    void selectDifficulty();
    void emitDifficultySelected();
};

#endif // SONGINFOWIDGET_H
