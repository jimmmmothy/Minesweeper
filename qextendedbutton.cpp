#include "qextendedbutton.h"

QExtendedButton::QExtendedButton(int row, int col, CellState &state, QWidget *parent, int number) :
    QPushButton(parent)
{
    this->row = row;
    this->col = col;
    this->state = state;
    this->num = number;
    UpdateStyle();
}

void QExtendedButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
        emit leftClicked(row, col);

    else if(e->button() == Qt::RightButton)
        emit rightClicked(row, col);

    QPushButton::mousePressEvent(e);
}

void QExtendedButton::UpdateStyle()
{
    switch (state) {
    case FLAGGED:
        this->setStyleSheet("border-image: url(../../textures/cellflag.svg) 0 0 0 0 stretch stretch;");
        break;
    case MINE:
        this->setStyleSheet("border-image: url(../../textures/cellmine.svg) 0 0 0 0 stretch stretch;");
        break;
    case BLAST:
        this->setStyleSheet("border-image: url(../../textures/blast.svg) 0 0 0 0 stretch stretch;");
        break;
    case NUMBER:
    {
        std::string style = "border-image: url(../../textures/cell";
        style.append(std::to_string(num));
        style.append(".svg) 0 0 0 0 stretch stretch;");
        this->setStyleSheet(QString().fromStdString(style));
        break;
    }
    default:
        break;
    }
}
