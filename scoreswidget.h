#ifndef RECORDSWIDGET_H
#define RECORDSWIDGET_H

#include <QWidget>
#include <QTableWidget>

class ScoresWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScoresWidget(QWidget *parent = 0);
    void loadSongScores(QString);

private:
    QTableWidget *tableWidget;
    void resizeEvent(QResizeEvent *event) override;

signals:

public slots:
};

#endif // RECORDSWIDGET_H
