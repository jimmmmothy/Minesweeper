#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <memory>
#include "board.h"

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
    void DrawField(int size);
    void on_cell_clicked();

private slots:
    void on_btnNewGame_clicked();

private:
    Ui::GameWindow *ui;
    std::unique_ptr<Board> board;
};
#endif // GAMEWINDOW_H
