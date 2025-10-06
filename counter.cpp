#include "counter.h"

Counter::Counter(int count)
{
    // ones = new QLabel();
    // tens = new QLabel();
    // hundreds = new QLabel();

    m_hundreds.setFixedSize(20, 40);
    m_tens.setFixedSize(20, 40);
    m_ones.setFixedSize(20, 40);

    m_hundreds.setScaledContents(true);
    m_tens.setScaledContents(true);
    m_ones.setScaledContents(true);

    this->addWidget(&m_hundreds);
    this->addWidget(&m_tens);
    this->addWidget(&m_ones);

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
    this->m_ones.setPixmap(p1);

    QPixmap p2(base + QString::number(tens) + ".png");
    this->m_tens.setPixmap(p2);

    QPixmap p3(base + QString::number(hundreds) + ".png");
    this->m_hundreds.setPixmap(p3);
}
