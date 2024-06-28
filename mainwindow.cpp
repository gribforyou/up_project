#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    music_sound_level = 0;
    fx_sound_level = 0;

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

    settings_widget->setParent(this);
    settings_widget->move(width()/2-130, height()/2-85);
    settings_widget->close();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(dynamic_cast<Start_Widget*>(this->centralWidget())){
        this->setCentralWidget(this->menu_widget);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::playSlot()
{
    setCentralWidget(songSelectMenu);
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

void MainWindow::showGameplayWidget(SongInfo, QString)
{
    setCentralWidget(gameplayWidget);
}

void MainWindow::changeSound(int m, int f)
{
    this->music_sound_level = m;
    this->fx_sound_level = f;
    settings_widget->close();
    centralWidget()->setEnabled(true);
}

void MainWindow::settingsCancel()
{
    settings_widget->close();
    centralWidget()->setEnabled(true);
}


