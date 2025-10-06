#pragma once

#include <QLabel>
#include <qboxlayout.h>


class Counter : public QHBoxLayout
{
public:
    Counter(int count);
    ~Counter();
    void Set(int count);

signals:
    void layoutChanged();

private:
    QLabel m_ones;
    QLabel m_tens;
    QLabel m_hundreds;
};
