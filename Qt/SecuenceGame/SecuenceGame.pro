#-------------------------------------------------
#
# Project created by QtCreator 2016-09-08T15:26:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SecuenceGame
TEMPLATE = app


SOURCES += main.cpp \
    Game.cpp \
    Button.cpp \
    BoardCard.cpp \
    DeckCard.cpp

HEADERS  += \
    Game.h \
    Button.h \
    BoardCard.h \
    DeckCard.h

RESOURCES += \
    resources.qrc
