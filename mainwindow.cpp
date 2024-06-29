#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    songSelectMenu = new SongSelectMenu();
    songSelectMenu->resize(size());
    connect(songSelectMenu, &SongSelectMenu::levelSelected, this, &MainWindow::showGameplayWidget);
    gameplayWidget = new GameplayWidget();

    this->setWindowTitle("The best title ever");
    this->setFixedSize(this->width(), this->height());

    music_sound_level = 5;
    fx_sound_level = 5;

    start_widget = new Start_Widget;
    menu_widget = new Menu_Widget;
    settings_widget = new Settings_Widget;

    settings_widget->setFixedSize(260, 170);
    settings_widget->setWindowTitle("Settings");

    setCentralWidget(start_widget);
    update();

    connect(menu_widget, SIGNAL(play_signal()), this, SLOT(playSlot()));
    connect(menu_widget, SIGNAL(settings_signal()), this, SLOT(settingsSlot()));
    connect(menu_widget, SIGNAL(exit_signal()), this, SLOT(exitSlot()));

    connect(settings_widget, SIGNAL(cancel_signal()), this, SLOT(settingsCancel()));
    connect(settings_widget, SIGNAL(ok_signal(int ,int )), this, SLOT(changeSound(int ,int )));

    connect(songSelectMenu->getSongListWidget(), SIGNAL(settingsSignal()), this, SLOT(settingsSlot()));
    connect(songSelectMenu->getSongListWidget(), SIGNAL(exitSignal()), this, SLOT(exitSlot()));

    connect(songSelectMenu->getSongInfoWidget()->getDifficultListWidget(), SIGNAL(difficultSettingsSignal()), this, SLOT(settingsSlot()));
    connect(songSelectMenu->getSongInfoWidget()->getDifficultListWidget(), SIGNAL(difficultExitSignal()), this, SLOT(exitSlot()));

    settings_widget->setParent(this);
    settings_widget->move(width()/2-130, height()/2-85);
    settings_widget->close();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        if (dynamic_cast<GameplayWidget*>(this->centralWidget())) {
            gameplayWidget = dynamic_cast<GameplayWidget*>(takeCentralWidget());
            setCentralWidget(songSelectMenu);
            songSelectMenu->changeSelectedSong(songSelectMenu->getSelectedSong());
        }
        else
            QCoreApplication::quit();
    };
    if(dynamic_cast<Start_Widget*>(this->centralWidget())){
        this->setCentralWidget(this->menu_widget);
    };
    if((event->key() == 16777220 || event->key() == Qt::Key_D || event->key() == Qt::Key_F || event->key() == Qt::Key_J || event->key() == Qt::Key_K) && dynamic_cast<GameplayWidget*>(this->centralWidget())){
        if (settings_widget->isVisible() == false)
            gameplayWidget->keyPressEvent(event);
    };
    if (event->key() == Qt::Key_S && event->isAutoRepeat() == false) {
        if (dynamic_cast<GameplayWidget*>(this->centralWidget()))
            gameplayWidget->keyPressEvent(event);
        settingsSlot();
    };
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if((event->key() == Qt::Key_D || event->key() == Qt::Key_F || event->key() == Qt::Key_J || event->key() == Qt::Key_K) && dynamic_cast<GameplayWidget*>(this->centralWidget())){
        gameplayWidget->keyReleaseEvent(event);
    };
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::playSlot()
{
    setCentralWidget(songSelectMenu);
    songSelectMenu->changeSelectedSong(0);
}

void MainWindow::menuSlot()
{
    setCentralWidget(menu_widget);
}

void MainWindow::settingsSlot()
{
    settings_widget->set_sliders(music_sound_level, fx_sound_level);
    centralWidget()->setEnabled(false);
    settings_widget->show();
    settings_widget->raise();
}

void MainWindow::exitSlot()
{
    QCoreApplication::quit();
}

void MainWindow::showGameplayWidget(SongInfo songInfo, QString difficulty)
{
    if (gameplayWidget->loadLevel(songInfo, difficulty)) {
        if (dynamic_cast<SongSelectMenu*>(this->centralWidget()))
            songSelectMenu = dynamic_cast<SongSelectMenu*>(takeCentralWidget());
        setCentralWidget(gameplayWidget);
    }
    else
        QMessageBox::information(this, "Error", "Level file not found");
}

void MainWindow::changeSound(int m, int f)
{
    this->music_sound_level = m;
    this->fx_sound_level = f;
    gameplayWidget->setMusicVolume(m);
    gameplayWidget->setFxVolume(f);
    songSelectMenu->setMusicVolume(m);
    settings_widget->hide();
    centralWidget()->setEnabled(true);
}

void MainWindow::settingsCancel()
{
    settings_widget->hide();
    centralWidget()->setEnabled(true);
}


