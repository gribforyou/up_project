#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    start_widget = new Start_Widget;
    menu_widget = new Menu_Widget;
    settings_widget = new Settings_Widget;

    setCentralWidget(start_widget);
    update();

    connect(menu_widget, SIGNAL(play_signal()), this, SLOT(playSlot()));
    connect(menu_widget, SIGNAL(settings_signal()), this, SLOT(settingsSlot()));
    connect(menu_widget, SIGNAL(exit_signal()), this, SLOT(exitSlot()));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(dynamic_cast<Start_Widget*>(this->centralWidget())){
        this->takeCentralWidget();
        this->setCentralWidget(this->menu_widget);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::playSlot()
{
    takeCentralWidget();
}

void MainWindow::settingsSlot()
{
    takeCentralWidget();
    setCentralWidget(settings_widget);
}

void MainWindow::exitSlot()
{
    QCoreApplication::quit();
}
