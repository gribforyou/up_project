#include "menu_widget.h"
#include <QApplication>

Menu_Widget::Menu_Widget(QWidget *parent)
    : QWidget{parent}
{
    QHBoxLayout* hlayout = new QHBoxLayout();
    QVBoxLayout* layout = new QVBoxLayout();

    QLabel* title = new QLabel("the best title ever");
    QPushButton* play_button = new QPushButton("play");
    QPushButton* settings_button = new QPushButton("settings");
    QPushButton* exit_button = new QPushButton("exit");

    connect(play_button, SIGNAL(clicked()), this, SLOT(play_slot()));
    connect(settings_button, SIGNAL(clicked()), this, SLOT(settings_slot()));
    connect(exit_button, SIGNAL(clicked()), this, SLOT(exit_slot()));

    title->setFont(QFont("Arial", 25));

    layout->addStretch();
    layout->addWidget(title);
    layout->addWidget(play_button);
    layout->addWidget(settings_button);
    layout->addWidget(exit_button);
    layout->addStretch();

    hlayout->addStretch();
    hlayout->addLayout(layout);
    hlayout->addStretch();

    this->setLayout(hlayout);
}

void Menu_Widget::play_slot()
{
    emit play_signal();
}

void Menu_Widget::settings_slot()
{
    emit settings_signal();
}

void Menu_Widget::exit_slot()
{
    emit exit_signal();
}
