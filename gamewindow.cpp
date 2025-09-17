#include "gamewindow.h"
#include "qpushbutton.h"
#include "qextendedbutton.h"
#include "ui_gamewindow.h"
#include "board.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    board = std::make_unique<Board>(30, 24, 160);
    DrawField(board->GetField());
}

GameWindow::~GameWindow()
{
    delete ui;
}

QExtendedButton* GameWindow::InitButton(std::vector<std::vector<char>>* field, int row, int col)
{
    CellState state;

    switch ((*field)[row][col]) {
    case '.':
        state = UNOPENED;
        break;
    case 'F':
        state = FLAGGED;
        break;
    case 'M':
        state = MINE;
        break;
    case 'B':
        state = BLAST;
        break;
    case 'X':
        state = FALSE;
        break;
    default:
        state = NUMBER;
    }

    if (state == NUMBER)
        return new QExtendedButton(row, col, state, this, (*field)[row][col] - '0');
    else
        return new QExtendedButton(row, col, state, this);
}

void GameWindow::DrawField(std::vector<std::vector<char>>* field)
{
    this->centralWidget()->findChild<QLabel*>("mineCountLbl")->setText(QString::fromStdString(std::to_string(board->GetMineCount())));

    QGridLayout *layout = ui->field;
    int sizex = board->GetSizex();
    int sizey = board->GetSizey();

    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (QWidget* widget = item->widget())
            widget->deleteLater();
        delete item;
    }

    for (int row = 0; row < sizex; ++row) {
        for (int col = 0; col < sizey; ++col) {
            QExtendedButton* button = InitButton(field, row, col);
            button->setFixedSize(24, 24);
            connect(button, SIGNAL(leftClicked(int,int)), this, SLOT(onLeftClicked(int,int)));
            connect(button, SIGNAL(rightClicked(int,int)), this, SLOT(onRightClicked(int,int)));
            layout->addWidget(button, row, col);
        }
    }
}

void GameWindow::on_btnNewGame_clicked()
{
    board->Reset();
    DrawField(board->GetField());
    this->centralWidget()->findChild<QPushButton*>("btnNewGame")->setText("New Game");
}

void GameWindow::GameOver(std::string str)
{
    // Button needs to be resized
    QPushButton *newGame = this->centralWidget()->findChild<QPushButton*>("btnNewGame");
    newGame->setText(QString::fromStdString(str));
    QGridLayout *layout = this->ui->field;
    int sizex = board->GetSizex();
    int sizey = board->GetSizey();

    for (int row = 0; row < sizex; ++row) {
        for (int col = 0; col < sizey; ++col) {
            QPushButton* button = qobject_cast<QPushButton*>(layout->itemAtPosition(row, col)->widget());
            button->setEnabled(false);
        }
    }
}

void GameWindow::onLeftClicked(int row, int col)
{
    QObject *senderObj = sender();
    QPushButton *button = qobject_cast<QPushButton *>(senderObj);

    if (button) {
        int res = board->RevealCell(row, col);
        if (res == -1)
        {
            DrawField(board->GetLosingField());
            GameOver("Game over!");
        }
        else if (res == 1)
        {
            DrawField(board->GetField());
        }
        else if (res == 2)
        {
            DrawField(board->GetField());
            GameOver("You won!");
        }
        return;
    }
}

void GameWindow::onRightClicked(int row, int col)
{
    QObject *senderObj = sender();
    QPushButton *button = qobject_cast<QPushButton *>(senderObj);

    if (button) {
        board->FlagCell(row, col);
        DrawField(board->GetField());
        return;
    }
}

void GameWindow::on_btnShowMines_clicked()
{
    DrawField(board->GetPrivField());
}

