#ifndef SETTINGS_WIDGET_H
#define SETTINGS_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QPushButton>

class Settings_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Settings_Widget(QWidget *parent = nullptr);
    void set_sliders(int m, int f);
private:
    QSlider* music_slider;
    QSlider* fx_slider;
private slots:
    void cancel_slot();
    void ok_slot();
signals:
    void cancel_signal();
    void ok_signal(int mLevel, int fLevel );
};

#endif // SETTINGS_WIDGET_H
