#include "levelviewwidget.h"

#include <QPainter>

LevelViewWidget::LevelViewWidget(QWidget *parent) : QWidget(parent)
{
    waitingNotes.resize(4);
    visibleNotes.resize(4);
    visibleNotes[0].push_back(std::make_pair(500, 100));
}

void LevelViewWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int width = size().width(), height = size().height();
    int columnWidth = width / 8, columnHeight = height * 4 / 5;
    painter.translate(width / 4, height * 9 / 10);
    painter.scale(1, -1);
    painter.setBrush(Qt::gray);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < visibleNotes[i].size(); j++) {
            std::pair <int, int> note = visibleNotes[i][j];
            int notePos = std::max(0., note.first - noteSpeed * (*time));
            painter.drawRect(columnWidth * i, notePos, columnWidth, note.second + (note.first - noteSpeed * (*time) - notePos));
        };
    };
    painter.setBrush(Qt::NoBrush);
    for (int i = 0; i < 5; i++)
        painter.drawLine(columnWidth * i, 0, columnWidth * i, columnHeight);
    painter.drawLine(0, 20, columnWidth * 4, 20);
    painter.drawLine(0, 25, columnWidth * 4, 25);
}

void LevelViewWidget::setupLevelView(double *time)
{
    this->visibleNotes = visibleNotes;
    this->time = time;
}

void LevelViewWidget::updateLevelView()
{
    for (int i = 0; i < 4; i++) {
        int j = 0;
        while (j < visibleNotes[i].size()) {
            std::pair <int, int> note = visibleNotes[i][j];
            if (note.second + (note.first - noteSpeed * (*time) - std::max(0., note.first - noteSpeed * (*time))) <= 0)
                    visibleNotes[i].erase(visibleNotes[i].begin() + j);
            else
                j++;
        };
    };
    update();
}
