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
    int row;
    int col;
    Board* board;
    CellState state;
    int number;
    bool isDisabled = false;


signals:
    void rightClicked(int row, int col);
    void leftClicked(int row, int col);
};
