#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include "start_widget.h"
#include "menu_widget.h"
#include "settings_widget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent* event);
    ~MainWindow();

private:
    Start_Widget* start_widget;
    Menu_Widget* menu_widget;
    Settings_Widget* settings_widget;
    Ui::MainWindow *ui;

public slots:
    void playSlot();
    void settingsSlot();
    void exitSlot();
};
#endif // MAINWINDOW_H
