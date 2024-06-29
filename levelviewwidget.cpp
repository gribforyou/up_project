#include "levelviewwidget.h"

#include <QPainter>
#include <QDebug>

LevelViewWidget::LevelViewWidget(QWidget *parent) : QWidget(parent)
{
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
        for (int j = 0; j < (*notesVector)[i].size(); j++) {
            std::pair <int, int> note = (*notesVector)[i][j];
            double noteStart = note.first * (*spb) + (*offset) / 1000., noteLength = note.second * (*spb);
            double notePos = std::max(0., noteStart - gameplayWidget->getSongTime());
            painter.drawRect(columnWidth * i, std::max(0., notePos * pps - 2.5), columnWidth, std::max(0., std::min(columnHeight - notePos * pps, (noteLength + (noteStart - gameplayWidget->getSongTime() - notePos)) * pps + 5)));
        };
    };
    painter.setBrush(Qt::black);
    for (int i = 0; i < 4; i++)
        if ((*isActive)[i])
            painter.drawRect(columnWidth * i, 0, columnWidth, 5);
    painter.setBrush(Qt::NoBrush);
    for (int i = 0; i < 5; i++)
        painter.drawLine(columnWidth * i, 0, columnWidth * i, columnHeight);
    painter.drawLine(0, 0, columnWidth * 4, 0);
    painter.drawLine(0, 5, columnWidth * 4, 5);
}

void LevelViewWidget::setupLevelView(GameplayWidget *gameplayWidget, std::vector <bool> *isActive, std::vector <std::vector <std::pair <int, int>>> *notesVector, double *spb, int *offset)
{
    this->gameplayWidget = gameplayWidget;
    this->isActive = isActive;
    this->notesVector = notesVector;
    this->spb = spb;
    this->offset = offset;
}

void LevelViewWidget::updateLevelView()
{
    for (int i = 0; i < 4; i++) {
        int j = 0;
        while (j < (*notesVector)[i].size()) {
            std::pair <int, int> note = (*notesVector)[i][j];
            double noteStart = note.first * (*spb) + (*offset) / 1000., noteLength = note.second * (*spb);
            if (noteStart < 0 && noteLength + (noteStart - gameplayWidget->getSongTime() - std::max(0., noteStart - gameplayWidget->getSongTime())) < 0)
                    (*notesVector)[i].erase((*notesVector)[i].begin() + j);
            else
                j++;
        };
    };
    update();
}
