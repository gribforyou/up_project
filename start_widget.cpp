#include "start_widget.h"

Start_Widget::Start_Widget() {

    QHBoxLayout* hlayout = new QHBoxLayout();
    QVBoxLayout* layout = new QVBoxLayout();

    QLabel* title = new QLabel("The best title ever");
    QLabel* press = new QLabel("Press any key to start");

    title->setFont(QFont("Arial", 40));

    title->setAlignment(Qt::AlignCenter);
    press->setAlignment(Qt::AlignCenter);

    layout->addStretch();
    layout->addWidget(title);
    layout->addWidget(press);
    layout->addStretch();

    hlayout->addStretch();
    hlayout->addLayout(layout);
    hlayout->addStretch();

    this->setLayout(hlayout);

    QPalette* pal = new QPalette();
    pal->setColor(this->backgroundRole(), Qt::white);
    this->setPalette(*pal);
    this->setAutoFillBackground(true);
}


