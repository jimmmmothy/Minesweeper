#pragma once

#include <QMainWindow>
#include <memory>
#include <qgraphicsview.h>
#include "board.h"
#include "counter.h"
#include "enums.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class GameWindow;
}
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    // QExtendedButton* InitButton(char** field, int row, int col);
    void DrawField(FieldType type);
    void GameOver(std::string str);

private slots:
    void onRightClicked(int row, int col);
    void onLeftClicked(int row, int col);
    void on_newGameBtn_clicked();

private:
    const int CELL_SIZE = 20;
    bool isFirstDraw = true;
    bool isFirstClick = true;
    Ui::GameWindow *ui;
    Board board;
    Counter mineCount;
    QGraphicsScene scene;
};
