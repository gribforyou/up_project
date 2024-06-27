#include "settings_widget.h"

Settings_Widget::Settings_Widget(QWidget *parent)
    : QWidget{parent}
{
    QHBoxLayout* hlayout1 = new QHBoxLayout();
    QHBoxLayout* hlayout2 = new QHBoxLayout();
    QVBoxLayout* layout1 = new QVBoxLayout();
    QVBoxLayout* layout2 = new QVBoxLayout();
    QVBoxLayout* layout3 = new QVBoxLayout();

    QLabel* first_label = new QLabel("Set sound level");
    QLabel* music_label = new QLabel("music");
    QLabel* fx_label = new QLabel("fx");

    music_slider = new QSlider(Qt::Horizontal);
    fx_slider = new QSlider(Qt::Horizontal);

    QPushButton* ok_button = new QPushButton("ok");
    QPushButton* cancel_button = new QPushButton("cancel");

    connect(cancel_button, SIGNAL(clicked()), this, SLOT(cancel_slot()));
    connect(ok_button, SIGNAL(clicked()), this, SLOT(ok_slot()));

    music_slider->setFixedSize(100, 20);
    fx_slider->setFixedSize(100, 20);

    music_label->setFixedSize(100, 20);
    fx_label->setFixedSize(100, 20);

    first_label->setFixedSize(200, 15);
    first_label->setAlignment(Qt::AlignCenter);

    layout1->addStretch();
    layout1->addWidget(music_label);
    layout1->addWidget(fx_label);
    layout1->addWidget(ok_button);
    layout1->addStretch();

    layout2->addStretch();
    layout2->addWidget(music_slider);
    layout2->addWidget(fx_slider);
    layout2->addWidget(cancel_button);
    layout2->addStretch();

    hlayout1->addStretch();
    hlayout1->addWidget(first_label);
    hlayout1->addStretch();

    hlayout2->addStretch();
    hlayout2->addLayout(layout1);
    hlayout2->addLayout(layout2);
    hlayout2->addStretch();

    layout3->addStretch();
    layout3->addLayout(hlayout1);
    layout3->addSpacing(5);
    layout3->addLayout(hlayout2);
    layout3->addStretch();

    this->setLayout(layout3);

    QPalette* pal = new QPalette();
    pal->setColor(this->backgroundRole(), Qt::lightGray);
    this->setPalette(*pal);
    this->setAutoFillBackground(true);
}

void Settings_Widget::set_sliders(int m, int f)
{
    music_slider->setValue(m);
    fx_slider->setValue(f);
}


void Settings_Widget::cancel_slot()
{
    emit cancel_signal();
}

void Settings_Widget::ok_slot()
{
    int mLevel = music_slider->value();
    int fLevel = fx_slider->value();
    emit ok_signal(mLevel, fLevel);
}

