#-------------------------------------------------
#
# Project created by QtCreator 2017-11-17T18:17:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Einsteinchess
TEMPLATE = app


SOURCES += main.cpp\
        chessboard.cpp \
    einsteinchess.cpp \
    game.cpp \
    display.cpp \
    footwork.cpp

HEADERS  += chessboard.h \
    einsteinchess.h \
    game.h \
    display.h \
    footwork.h

FORMS    += chessboard.ui
