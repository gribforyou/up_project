#include "difficultlistwidget.h"

DifficultListWidget::DifficultListWidget(QWidget *parent)
    : QListWidget{parent}
{
    this->setFlow(QListWidget::LeftToRight);

    this->addItem(new QListWidgetItem("easy"));
    this->addItem(new QListWidgetItem("normal"));
    this->addItem(new QListWidgetItem("hard"));

    this->setFixedHeight(35);
}

void DifficultListWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==16777220){
        emitDifficultySelected();
    }
    if(event->key() == Qt::Key_S){
        emit difficultSettingsSignal();
    }
    if(event->key() == Qt::Key_E){
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
