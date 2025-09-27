#include "cellitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QImage>
#include <QString>

CellItem::CellItem(int size, int row, int col, std::unique_ptr<Board>* board)
    : QGraphicsRectItem(0, 0, size, size), row(row), col(col), board(board)
{
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
    UpdateState(PUBLIC);
}

void CellItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QImage drawImg;
    switch (state) {
    case UNOPENED:
    {
        drawImg.load(":/textures/textures/cells/cellup.svg");
        painter->drawImage(rect(), drawImg);
        break;
    }
    case FLAGGED:
    {
        drawImg.load(":/textures/textures/cells/cellflag.svg");
        painter->drawImage(rect(), drawImg);
        break;
    }
    case MINE:
    {
        drawImg.load(":/textures/textures/cells/cellmine.svg");
        painter->drawImage(rect(), drawImg);
        break;
    }
    case BLAST:
    {
        drawImg.load(":/textures/textures/cells/blast.svg");
        painter->drawImage(rect(), drawImg);
        break;
    }
    case FALSE:
    {
        drawImg.load(":/textures/textures/cells/falsemine.svg");
        painter->drawImage(rect(), drawImg);
        break;
    }
    case NUMBER:
    {
        std::string style = ":/textures/textures/cells/cell";
        style.append(std::to_string(number));
        style.append(".svg");
        drawImg.load(QString().fromStdString(style));
        painter->drawImage(rect(), drawImg);
        break;
    }
    default:
        break;
    }
}

void CellItem::Disable()
{
    isDisabled = true;
}

void CellItem::Enable()
{
    isDisabled = false;
}

void CellItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (isDisabled)
        return;

    if (event->button() == Qt::LeftButton) {
        emit leftClicked(row, col);
    } else if (event->button() == Qt::RightButton) {
        emit rightClicked(row, col);
    }
}

void CellItem::UpdateState(FieldType field)
{
    char cell;
    if (field == PRIV)
        cell = (*board)->GetPrivField()[row][col];
    else if (field == LOST)
        cell = (*board)->GetLosingField()[row][col]; // WHY DOES THIS NOT SHOW??
    else
        cell = (*board)->GetPublicField()[row][col];

    switch (cell) {
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
        number = cell - '0';
        break;
    }

    update();// trigger repaint
}
