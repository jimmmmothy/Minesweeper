#pragma once

#include <QMainWindow>
#include <memory>
#include "board.h"
#include "qextendedbutton.h"

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
    QExtendedButton* InitButton(std::vector<std::vector<char>>* field, int row, int col);
    void DrawField(std::vector<std::vector<char>>* field);
    void GameOver(std::string str);

private slots:
    void onRightClicked(int row, int col);
    void onLeftClicked(int row, int col);
    void on_btnNewGame_clicked();

    void on_btnShowMines_clicked();

private:
    Ui::GameWindow *ui;
    std::unique_ptr<Board> board;
};
