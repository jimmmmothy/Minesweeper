#include "gamewindow.h"
#include "cellitem.h"
// #include "qextendedbutton.h"
#include "ui_gamewindow.h"
#include "board.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <qlabel.h>
#include <unistd.h>
#include <QTransform>

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    board = std::make_unique<Board>(30, 24, 160);
    scene = new QGraphicsScene(this);

    // Adding visual elements in proper order in layouts
    mineCount = new Counter(board->GetMineCount());
    ui->hLayout->addLayout(mineCount);
    ui->hLayout->addWidget(ui->newGameBtn, 0, Qt::AlignCenter);
    ui->hLayout->setSizeConstraint(QLayout::SetMinimumSize);
    ui->hLayout->setAlignment(Qt::AlignHCenter);
    ui->vLayout->addWidget(ui->graphicsView, 0, Qt::AlignCenter);
    ui->vLayout->setAlignment(Qt::AlignTop);

    // Adds cells to the scene
    DrawField(PUBLIC);

    // Graphics view init thingies
    ui->graphicsView->setRenderHint(QPainter::Antialiasing, false);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFixedSize(scene->width() + 2, scene->height() + 2);
    ui->graphicsView->setScene(scene);
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::DrawField(FieldType field)
{
    mineCount->Set(board->GetMineCount());

    if (isFirstDraw) { // Only allocate the cells to heap once per app run
        for (int row = 0; row < board->GetSizex(); ++row) {
            for (int col = 0; col < board->GetSizey(); ++col) {
                CellItem* cell = new CellItem(CELL_SIZE, row, col, &board);
                cell->setPos(col * CELL_SIZE, row * CELL_SIZE);
                connect(cell, SIGNAL(leftClicked(int,int)), this, SLOT(onLeftClicked(int,int)));
                connect(cell, SIGNAL(rightClicked(int,int)), this, SLOT(onRightClicked(int,int)));
                scene->addItem(cell);
            }
        }

        isFirstDraw = false;
        return;
    }

    for (QGraphicsItem* item : scene->items()) {
        if (CellItem* cell = dynamic_cast<CellItem*>(item)) {
            cell->UpdateState(field);
        }
    }

    // Drawing takes longer than the time it takes for the code to move on to the next function call, e.g. GameOver(), so it would never draw.
    // processEvents waits for the cells to repaint themselves.
    qApp->processEvents();
}

void GameWindow::GameOver(std::string str)
{
    for (QGraphicsItem* item : scene->items()) {
        if (CellItem* cell = dynamic_cast<CellItem*>(item)) {
            cell->Disable();
        }
    }
}

void GameWindow::onLeftClicked(int row, int col)
{
    int res = board->RevealCell(row, col);
    if (res == -1)
    {
        DrawField(LOST);
        GameOver("Game over!");
    }
    else if (res == 1)
    {
        DrawField(PUBLIC);
    }
    else if (res == 2)
    {
        DrawField(PUBLIC);
        GameOver("You won!");
    }
}

void GameWindow::onRightClicked(int row, int col)
{
    board->FlagCell(row, col);
    DrawField(PUBLIC);
}

void GameWindow::on_newGameBtn_clicked()
{
    board->Reset();
    DrawField(PUBLIC);
    for (QGraphicsItem* item : scene->items()) {
        if (CellItem* cell = dynamic_cast<CellItem*>(item)) {
            cell->Enable();
        }
    }
    // this->centralWidget()->findChild<QPushButton*>("btnNewGame")->setText("New Game");
}

