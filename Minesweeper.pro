QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    board.cpp \
    main.cpp \
    gamewindow.cpp \
    qextendedbutton.cpp

HEADERS += \
    board.h \
    gamewindow.h \
    qextendedbutton.h

FORMS += \
    gamewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    textures/blast.svg \
    textures/cell0.svg \
    textures/cell1.svg \
    textures/cell2.svg \
    textures/cell3.svg \
    textures/cell4.svg \
    textures/cell5.svg \
    textures/cell6.svg \
    textures/cell7.svg \
    textures/cell8.svg \
    textures/cellflag.svg \
    textures/cellmine.svg \
    textures/cellup.svg \
    textures/falsemine.svg
