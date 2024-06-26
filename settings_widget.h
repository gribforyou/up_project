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
private slots:
    void cancel_slot();
signals:
    void cancel_signal();
};

#endif // SETTINGS_WIDGET_H
