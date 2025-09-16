#include "gamewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w;
    w.setStyleSheet(R"(
        QExtendedButton {
            border-image: url(../../textures/cellup.svg) 0 0 0 0 stretch stretch;
        }
    )");
    w.show();
    return a.exec();
}
