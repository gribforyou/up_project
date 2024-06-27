#ifndef SONGINFOWIDGET_H
#define SONGINFOWIDGET_H

#include <QWidget>
#include "scoreswidget.h"
#include "songinfo.h"

class SongInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SongInfoWidget(QWidget *parent = 0);
    void loadSongInfo(SongInfo);

private:
    ScoresWidget *scores;
    void resizeEvent(QResizeEvent *event) override;

signals:

public slots:
};

#endif // SONGINFOWIDGET_H
