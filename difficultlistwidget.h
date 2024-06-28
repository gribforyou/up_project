#ifndef DIFFICULTLISTWIDGET_H
#define DIFFICULTLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QShowEvent>
#include <QKeyEvent>

class DifficultListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit DifficultListWidget(QWidget *parent = nullptr);

private:
    void keyPressEvent(QKeyEvent* event);

signals:
    void difficultySelected(QString);
    void difficultSettingsSignal();
    void difficultExitSignal();
    void backToSongs();

public slots:
    void selectDifficulty();
    void emitDifficultySelected();
};

#endif // DIFFICULTLISTWIDGET_H
