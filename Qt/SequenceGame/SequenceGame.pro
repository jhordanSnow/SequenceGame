#-------------------------------------------------
#
# Project created by QtCreator 2016-09-11T16:57:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SequenceGame
TEMPLATE = app


SOURCES += main.cpp \
    Game.cpp \
    BoardCard.cpp \
    Button.cpp \
    DeckCard.cpp \
    Player.cpp \
    CircleListPlayers.cpp

HEADERS  += \
    Game.h \
    BoardCard.h \
    Button.h \
    DeckCard.h \
    Player.h \
    CircleListPlayers.h

RESOURCES += \
    resources.qrc
