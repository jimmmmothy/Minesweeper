#pragma once

#include <QPushButton>
#include <QMouseEvent>

enum CellState {
    UNOPENED, FLAGGED, MINE, BLAST, NUMBER
};

class QExtendedButton : public QPushButton
{
    Q_OBJECT

public:
    explicit QExtendedButton(int row, int col, CellState &state, QWidget *parent = 0, int number = 0);
    void UpdateStyle();

private:
    int row;
    int col;
    CellState state;
    int num;

private slots:
    void mousePressEvent(QMouseEvent *e);

signals:
    void rightClicked(int row, int col);
    void leftClicked(int row, int col);    
};
