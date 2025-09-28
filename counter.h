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
    QLabel ones;
    QLabel tens;
    QLabel hundreds;
};
