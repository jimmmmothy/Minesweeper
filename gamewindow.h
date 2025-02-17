#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <memory>
#include "board.h"
#include "qpushbutton.h"

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
    void DrawField();
    void on_cell_clicked();

private slots:
    void on_btnNewGame_clicked();
    void onRightClicked();

private:
    Ui::GameWindow *ui;
    std::unique_ptr<Board> board;
};
#endif // GAMEWINDOW_H
