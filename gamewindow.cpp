#include "gamewindow.h"
#include "qpushbutton.h"
#include "ui_gamewindow.h"
#include "board.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    board = std::make_unique<Board>(9, 10);
    DrawField(board->GetField());
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::DrawField(std::vector<std::vector<char>> field) {
    QGridLayout *layout = ui->field;

    for (int row = 0; row < field.size(); ++row) {
        for (int col = 0; col < field[row].size(); ++col) {
            QLayoutItem *item = layout->itemAtPosition(row, col);
            QPushButton *button = nullptr;

            button = new QPushButton(this);
            button->setFixedSize(24, 24);
            QPalette pal = button->palette();
            pal.setColor(QPalette::Button, QColor(Qt::gray));
            button->setAutoFillBackground(true);
            button->setPalette(pal);
            button->update();
            layout->addWidget(button, row, col);

            if (button) {
                button->setText(QString(field[row][col]));
            }
        }
    }
}
