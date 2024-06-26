#ifndef MENU_WIDGET_H
#define MENU_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class Menu_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Menu_Widget(QWidget *parent = nullptr);

signals:
};

#endif // MENU_WIDGET_H
