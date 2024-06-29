#include "difficultlistwidget.h"
#include <QDebug>

DifficultListWidget::DifficultListWidget(QWidget *parent)
    : QListWidget{parent}
{
    this->setFlow(QListWidget::LeftToRight);

    this->addItem(new QListWidgetItem("easy"));
    this->addItem(new QListWidgetItem("normal"));
    this->addItem(new QListWidgetItem("hard"));
    setCurrentRow(0);
    this->setFixedHeight(35);
}

void DifficultListWidget::keyPressEvent(QKeyEvent *event)
{
    qDebug() << event->key();
    if(event->key()==16777220){
        emitDifficultySelected();
    }
    if(event->key() == Qt::Key_S || event->key() == 1067){
        emit difficultSettingsSignal();
    }
    if(event->key() == Qt::Key_E || event->key() == 1059){
        emit difficultExitSignal();
    }
    if(event->key() == Qt::Key_Backspace){
        qDebug() << "backSpace";
        emit backToSongs();
    }
    QListWidget::keyPressEvent(event);
}

void DifficultListWidget::selectDifficulty()
{
    setFocus();
}

void DifficultListWidget::emitDifficultySelected()
{
    QString difficulty;
    int row = this->currentRow();
    if (row == 0)
        difficulty = "easy";
    else
        if (row == 1)
            difficulty = "normal";
        else
            if (row == 2)
                difficulty = "hard";
    emit difficultySelected(difficulty);
}
