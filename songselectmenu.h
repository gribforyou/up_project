#ifndef SONGSELECTMENU_H
#define SONGSELECTMENU_H

#include <QWidget>
#include "songlistwidget.h"
#include "songinfowidget.h"
#include "songinfo.h"

class SongSelectMenu : public QWidget
{
    Q_OBJECT
public:
    explicit SongSelectMenu(QWidget *parent = 0);
    void loadSongInfoVector();

private:
    std::vector <SongInfo> songInfoVector;
    SongListWidget *songListWidget;
    SongInfoWidget *songInfoWidget;

signals:

public slots:
    void loadSongInfo(int);
    void changeSelectedSong(int);
};

#endif // SONGSELECTMENU_H
