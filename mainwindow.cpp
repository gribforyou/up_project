#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    start_widget = new Start_Widget;
    menu_widget = new Menu_Widget;

    setCentralWidget(start_widget);
    update();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(dynamic_cast<Start_Widget*>(this->centralWidget())){
        this->takeCentralWidget();
        this->setCentralWidget(this->menu_widget);
    }

    QCoreApplication::quit();
}

MainWindow::~MainWindow()
{
    delete ui;
}
