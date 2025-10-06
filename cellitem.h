#pragma once

#include "board.h"
#include "enums.h"
#include <QGraphicsRectItem>

class CellItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    CellItem(int size, int row, int col, Board* board);
    void UpdateState(FieldType = PUBLIC);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void Disable();
    void Enable();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    int m_row;
    int m_col;
    Board* m_board;
    CellState m_state;
    int m_number;
    bool m_isDisabled = false;


signals:
    void rightClicked(int row, int col);
    void leftClicked(int row, int col);
};
