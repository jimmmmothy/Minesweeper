#include "gamewindow.h"
#include "qpushbutton.h"
#include "qrightclickbutton.h"
#include "ui_gamewindow.h"
#include "board.h"
#include <iostream>

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    board = std::make_unique<Board>(16, 40);
    board->PlaceMines();
    DrawField();
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::DrawField()
{
    QGridLayout *layout = ui->field;
    std::vector<std::vector<char>> field = board->GetField();
    int size = board->GetSize();

    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (QWidget* widget = item->widget())
            widget->deleteLater();
        delete item;
    }

    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            QRightClickButton *button = new QRightClickButton(this);
            button->setFixedSize(24, 24);
            connect(button, &QPushButton::clicked, this, &GameWindow::on_cell_clicked);
            connect(button, SIGNAL(rightClicked()), this, SLOT(onRightClicked()));
            layout->addWidget(button, row, col);
            button->setText(QString(field[row][col]));
        }
    }
}

void GameWindow::on_btnNewGame_clicked()
{
    this->board->Reset();
    DrawField();
}

void GameWindow::on_cell_clicked()
{
    QObject *senderObj = sender();
    QPushButton *button = qobject_cast<QPushButton *>(senderObj);

    if (button) {
        QGridLayout *layout = ui->field;
        for (int row = 0; row < layout->rowCount(); ++row) {
            for (int col = 0; col < layout->columnCount(); ++col) {
                if (layout->itemAtPosition(row, col) &&
                    layout->itemAtPosition(row, col)->widget() == button) {
                    board->RevealCell(row, col);
                    DrawField();
                    return;
                }
            }
        }
    }
}

void GameWindow::onRightClicked()
{
    QObject *senderObj = sender();
    QPushButton *button = qobject_cast<QPushButton *>(senderObj);

    if (button) {
        QGridLayout *layout = ui->field;
        for (int row = 0; row < layout->rowCount(); ++row) {
            for (int col = 0; col < layout->columnCount(); ++col) {
                if (layout->itemAtPosition(row, col) &&
                    layout->itemAtPosition(row, col)->widget() == button) {
                    board->FlagCell(row, col);
                    DrawField();
                    return;
                }
            }
        }
    }
}
