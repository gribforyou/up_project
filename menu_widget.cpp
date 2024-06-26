#include "menu_widget.h"

Menu_Widget::Menu_Widget(QWidget *parent)
    : QWidget{parent}
{
    QHBoxLayout* hlayout = new QHBoxLayout();
    QVBoxLayout* layout = new QVBoxLayout();

    QLabel* title = new QLabel("the best title ever");
    QPushButton* play_button = new QPushButton("play");
    QPushButton* settings_button = new QPushButton("settings");
    QPushButton* exit_button = new QPushButton("exit");

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
