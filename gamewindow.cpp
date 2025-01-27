#include "gamewindow.h"
#include "qpushbutton.h"
#include "ui_gamewindow.h"
#include "board.h"
#include <iostream>

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    board = std::make_unique<Board>(9, 10);
    board->PlaceMines();
    DrawField(board->GetSize());
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::DrawField(int size)
{
    QGridLayout *layout = ui->field;

    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            if (layout->itemAtPosition(row,col)) {
                QWidget *widget = layout->itemAtPosition(row, col)->widget();
                QPushButton *button = qobject_cast<QPushButton*>(widget);
                button->setText(QString('.'));
            } else {
                QPushButton *button = new QPushButton(this);
                button->setFixedSize(24, 24);
                connect(button, &QPushButton::clicked, this, &GameWindow::on_cell_clicked);
                layout->addWidget(button, row, col);
                button->setText(QString('.'));
            }
        }
    }
}

void GameWindow::on_btnNewGame_clicked()
{
    this->board->Reset();
    DrawField(board->GetSize());
}

void GameWindow::on_cell_clicked()
{
    QObject *senderObj = sender(); // This will give Sender object
    QPushButton *button = qobject_cast<QPushButton *>(senderObj);

    if (button) {
        QGridLayout *layout = ui->field; // Get the layout
        for (int row = 0; row < layout->rowCount(); ++row) {
            for (int col = 0; col < layout->columnCount(); ++col) {
                if (layout->itemAtPosition(row, col) &&
                    layout->itemAtPosition(row, col)->widget() == button) {
                    char cell = board->RevealCell(row, col);
                    button->setText(QString(cell));
                    return;
                }
            }
        }
    }
}
