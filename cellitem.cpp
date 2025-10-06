#include "cellitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QImage>
#include <QString>

CellItem::CellItem(int size, int row, int col, Board* board)
    : QGraphicsRectItem(0, 0, size, size), m_row(row), m_col(col), m_board(board)
{
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
    UpdateState(PUBLIC);
}

void CellItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QImage drawImg;
    switch (m_state) {
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
        style.append(std::to_string(m_number));
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
    m_isDisabled = true;
}

void CellItem::Enable()
{
    m_isDisabled = false;
}

void CellItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (m_isDisabled)
        return;

    if (event->button() == Qt::LeftButton) {
        emit leftClicked(m_row, m_col);
    } else if (event->button() == Qt::RightButton) {
        emit rightClicked(m_row, m_col);
    }
}

void CellItem::UpdateState(FieldType field)
{
    char cell;
    if (field == PRIV)
        cell = m_board->GetPrivField()[m_row][m_col];
    else if (field == LOST)
        cell = m_board->GetLosingField()[m_row][m_col]; // WHY DOES THIS NOT SHOW??
    else
        cell = m_board->GetPublicField()[m_row][m_col];

    switch (cell) {
    case '.':
        m_state = UNOPENED;
        break;
    case 'F':
        m_state = FLAGGED;
        break;
    case 'M':
        m_state = MINE;
        break;
    case 'B':
        m_state = BLAST;
        break;
    case 'X':
        m_state = FALSE;
        break;
    default:
        m_state = NUMBER;
        m_number = cell - '0';
        break;
    }

    update();// trigger repaint
}
