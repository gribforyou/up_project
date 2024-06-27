#include "scoreswidget.h"

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QLabel>
#include <fstream>
#include <QDebug>
#include <string>

ScoresWidget::ScoresWidget(QWidget *parent) : QWidget(parent)
{
    tableWidget = new QTableWidget();
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel();
    label->setText("Top scores:");
    layout->addWidget(label);
    tableWidget->setColumnCount(2);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->horizontalHeader()->hide();
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    tableWidget->setFocusPolicy(Qt::NoFocus);
    layout->addWidget(tableWidget);
}

void ScoresWidget::loadSongScores(QString id)
{
    std::ifstream fin("scores/" + id.toStdString() + ".dat");
    if (!fin) {
        qDebug() << "ERROR!!";
        return;
    };
    std::vector <QStringList> scoreInfoListVector;
    while (!fin.eof()) {
        std::string input;
        getline(fin, input);
        if (input != "") {
            QString scoreInfoLine = QString::fromStdString(input);
            QStringList scoreInfoList = scoreInfoLine.split(";");
            scoreInfoListVector.push_back(scoreInfoList);
        };
    };
    tableWidget->setRowCount(scoreInfoListVector.size());
    for (int i = 0; i < scoreInfoListVector.size(); i++) {
        tableWidget->setItem(i, 0, new QTableWidgetItem(scoreInfoListVector[i][0]));
        tableWidget->setItem(i, 1, new QTableWidgetItem(scoreInfoListVector[i][1]));
    };
}

void ScoresWidget::resizeEvent(QResizeEvent *event)
{
}
