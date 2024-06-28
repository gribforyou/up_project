#include "gameplaywidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QDebug>
#include <QKeyEvent>

GameplayWidget::GameplayWidget(QWidget *parent) : QWidget(parent)
{
    time = 0;
    levelViewWidget = new LevelViewWidget();
    levelViewWidget->setupLevelView(&time);
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
    songPlayer = new QMediaPlayer();
    songPlayer->setMedia(QUrl::fromLocalFile("audio/1.mp3"));
    songPlayer->setVolume(20);
}

void GameplayWidget::showEvent(QShowEvent *event)
{
    countInTime = 3;
    countInTimer.start(1000);
    time = -3;
    timer.start(interval);
}

void GameplayWidget::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "it works";
    if (levelViewWidget->check())
        qDebug() << "it works";
}

void GameplayWidget::updateTime()
{
    time += interval / 1000.;
}

void GameplayWidget::countIn()
{
    if (countInTime > 0)
        countInTime--;
    else {
        songPlayer->play();
    };
}
