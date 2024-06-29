#include "gameplaywidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QDebug>
#include <QKeyEvent>
#include <fstream>

GameplayWidget::GameplayWidget(QWidget *parent) : QWidget(parent)
{
    time = 0;
    isActive = std::vector <bool>(4, false);
    notesVector.resize(4);
    levelViewWidget = new LevelViewWidget();
    levelViewWidget->setupLevelView(this, &isActive, &notesVector, &spb, &offset);
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->addWidget(levelViewWidget, 2);
    levelViewWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QGroupBox *groupBox = new QGroupBox();
//    groupBox->setMaximumHeight(70);
//    groupBox->setTitle("Score");
//    QVBoxLayout *groupBoxLayout = new QVBoxLayout(groupBox);
//    QLabel *label = new QLabel();
//    label->setText("000000");
//    label->setAlignment(Qt::AlignCenter);
//    groupBoxLayout->addWidget(label);
    horizontalLayout->addWidget(groupBox, 1);
    verticalLayout->addLayout(horizontalLayout);
    horizontalLayout = new QHBoxLayout();
    QLabel *label = new QLabel();
    label->setText("Press Enter to Pause");
    label->setAlignment(Qt::AlignHCenter);
    horizontalLayout->addWidget(label);
    label = new QLabel();
    label->setText("Press S to Show Settings");
    label->setAlignment(Qt::AlignHCenter);
    horizontalLayout->addWidget(label);
    label = new QLabel();
    label->setText("Press Escape to Exit to Menu");
    label->setAlignment(Qt::AlignHCenter);
    horizontalLayout->addWidget(label);
    verticalLayout->addLayout(horizontalLayout);
    connect(&countInTimer, &QTimer::timeout, this, &GameplayWidget::countIn);
    connect(&timer, &QTimer::timeout, this, &GameplayWidget::updateTime);
    connect(&timer, &QTimer::timeout, levelViewWidget, &LevelViewWidget::updateLevelView);
    songPlayer.setVolume(10);
    for (int i = 0; i < 4; i++) {
        QMediaPlayer *tapSoundPlayer = new QMediaPlayer();
        tapSoundPlayer->setMedia(QUrl::fromLocalFile("tap.mp3"));
        tapSoundPlayer->setVolume(20);
        tapSoundPlayers.push_back( tapSoundPlayer);
    };
}

bool GameplayWidget::loadLevel(SongInfo songInfo, QString difficulty)
{
    songPlayer.setMedia(QUrl::fromLocalFile("audio/levels/" + songInfo.getId() + ".mp3"));
    std::ifstream fin("charts/" + difficulty.toStdString() + "/" + songInfo.getId().toStdString() + ".chrt");
    if (!fin) {
        qDebug() << "error!!!";
        return false;
    };
    fin >> bpm >> offset;
    spb = 60. / bpm;
    fin.ignore();
    for (int i = 0; i < 4; i++) {
        std::string input;
        getline(fin, input);
        if (input != "") {
            QString notesDataLine = QString::fromStdString(input);
            QStringList notesDataList = notesDataLine.split(";");
            for (int j = 0; j < notesDataList.size(); j++)
                notesVector[i].push_back(std::make_pair(notesDataList[j].split(",")[0].toInt(), notesDataList[j].split(",")[1].toInt()));
        };
        qDebug() << notesVector[i].size();
    };
    return true;
}

void GameplayWidget::startLevel()
{
}

double GameplayWidget::getSongTime()
{
    return songPlayer.position() / 1000.;
}

void GameplayWidget::showEvent(QShowEvent *event)
{
    time = 0;
    connect(&timer, &QTimer::timeout, this, &GameplayWidget::countIn);
    timer.start(interval);
}

void GameplayWidget::hideEvent(QHideEvent *event)
{
    songPlayer.stop();
}

void GameplayWidget::keyPressEvent(QKeyEvent *event)
{
    if ((event->key() == Qt::Key_D || event->key() == Qt::Key_F || event->key() == Qt::Key_J || event->key() == Qt::Key_K) && event->isAutoRepeat() == false) {
        QMediaPlayer *tapSoundPlayer;
        if (event->key() == Qt::Key_D) {
            tapSoundPlayer = tapSoundPlayers[0];
            isActive[0] = true;
        }
        else
            if (event->key() == Qt::Key_F) {
                tapSoundPlayer = tapSoundPlayers[1];
                isActive[1] = true;
            }
            else
                if (event->key() == Qt::Key_J) {
                    tapSoundPlayer = tapSoundPlayers[2];
                    isActive[2] = true;
                }
                else
                    if (event->key() == Qt::Key_K) {
                        tapSoundPlayer = tapSoundPlayers[3];
                        isActive[3] = true;
                    };
        if (tapSoundPlayer != nullptr) {
            if (tapSoundPlayer->state() == QMediaPlayer::PlayingState)
                tapSoundPlayer->setPosition(0);
            else
                tapSoundPlayer->play();
        };
    };
}

void GameplayWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat() == false) {
        QMediaPlayer *tapSoundPlayer;
        if (event->key() == Qt::Key_D) {
            tapSoundPlayer = tapSoundPlayers[0];
            isActive[0] = false;
        }
        else
            if (event->key() == Qt::Key_F) {
                tapSoundPlayer = tapSoundPlayers[1];
                isActive[1] = false;
            }
            else
                if (event->key() == Qt::Key_J) {
                    tapSoundPlayer = tapSoundPlayers[2];
                    isActive[2] = false;
                }
                else
                    if (event->key() == Qt::Key_K) {
                        tapSoundPlayer = tapSoundPlayers[3];
                        isActive[3] = false;
                    };
        if (tapSoundPlayer != nullptr) {
            if (tapSoundPlayer->state() == QMediaPlayer::PlayingState && tapSoundPlayer->position() >= 150)
                tapSoundPlayer->setPosition(0);
            else
                if (tapSoundPlayer->state() == QMediaPlayer::StoppedState)
                    tapSoundPlayer->play();
        };
    };
}

void GameplayWidget::updateTime()
{
    time += interval / 1000.;
}

void GameplayWidget::countIn()
{
    if (time > 0) {
        songPlayer.play();
        qDebug() << time;
        disconnect(&timer, &QTimer::timeout, this, &GameplayWidget::countIn);
    };
}
