#ifndef LEVELVIEWWIDGET_H
#define LEVELVIEWWIDGET_H

#include <QWidget>
#include <vector>

class LevelViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LevelViewWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event) override;
    void setupLevelView(double*);

private:
    std::vector <std::vector <std::pair <int, int>>> waitingNotes, visibleNotes;
    int noteSpeed = 100;
    double *time;

signals:

public slots:
    void updateLevelView();
};

#endif // LEVELVIEWWIDGET_H
