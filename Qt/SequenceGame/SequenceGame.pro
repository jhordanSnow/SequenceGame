#-------------------------------------------------
#
# Project created by QtCreator 2016-09-12T19:53:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SequenceGame
TEMPLATE = app


SOURCES += main.cpp \
    BoardCard.cpp \
    Button.cpp \
    CircleListPlayers.cpp \
    DeckCard.cpp \
    Game.cpp \
    Player.cpp \
    ArrayStackDeck.cpp \
    ArrayCard.cpp \
    Board.cpp \
    Token.cpp \
    Play.cpp \
    UndoStack.cpp

HEADERS  += \
    BoardCard.h \
    Button.h \
    CircleListPlayers.h \
    DeckCard.h \
    Game.h \
    Player.h \
    ArrayStackDeck.h \
    ArrayCard.h \
    Board.h \
    Token.h \
    Play.h \
    UndoStack.h

RESOURCES += \
    resources.qrc
