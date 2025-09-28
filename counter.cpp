#include "counter.h"

Counter::Counter(int count)
{
    // ones = new QLabel();
    // tens = new QLabel();
    // hundreds = new QLabel();

    hundreds.setFixedSize(20, 40);
    tens.setFixedSize(20, 40);
    ones.setFixedSize(20, 40);

    hundreds.setScaledContents(true);
    tens.setScaledContents(true);
    ones.setScaledContents(true);

    this->addWidget(&hundreds);
    this->addWidget(&tens);
    this->addWidget(&ones);

    this->setSpacing(0);

    Set(count);
}

Counter::~Counter()
{
    // delete ones;
    // delete tens;
    // delete hundreds;
}

void Counter::Set(int count)
{
    short ones = count % 10;
    short tens = (count / 10) % 10;
    short hundreds = (count / 100) % 10;

    QString base = ":/textures/textures/counters/counter";

    QPixmap p1(base + QString::number(ones) + ".png");
    this->ones.setPixmap(p1);

    QPixmap p2(base + QString::number(tens) + ".png");
    this->tens.setPixmap(p2);

    QPixmap p3(base + QString::number(hundreds) + ".png");
    this->hundreds.setPixmap(p3);
}
