#include "gamewindow.h"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w;
    std::cout << "cellmine null? " << QPixmap(":/textures/textures/cellmine.svg").isNull() << std::endl;
    w.setStyleSheet(R"(
        QExtendedButton {
            border-image: url(:/textures/textures/cellup.svg) 0 0 0 0 stretch stretch;
        }
    )");
    w.show();
    return a.exec();
}
