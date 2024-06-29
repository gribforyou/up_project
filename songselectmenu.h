#ifndef SONGSELECTMENU_H
#define SONGSELECTMENU_H

#include <QWidget>
#include "songlistwidget.h"
#include "songinfowidget.h"
#include "songinfo.h"
#include <QMediaPlayer>

class SongSelectMenu : public QWidget
{
    Q_OBJECT
public:
    explicit SongSelectMenu(QWidget *parent = 0);
    void loadSongInfoVector();
    SongListWidget *getSongListWidget();
    SongInfoWidget *getSongInfoWidget();
    int getSelectedSong() const;
    void setSongInfoWidget(SongInfoWidget *newSongInfoWidget);

private:
    QMediaPlayer previewPlayer;
    std::vector <SongInfo> songInfoVector;
    int selectedSong = 0;
    SongListWidget *songListWidget;
    SongInfoWidget *songInfoWidget;
    void hideEvent(QHideEvent *event);

signals:
    void levelSelected(SongInfo, QString);

public slots:
    void backToSongs();
    void changeSelectedSong(int);
    void emitLevelSelected(QString);
};

#endif // SONGSELECTMENU_H
