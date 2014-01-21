#-------------------------------------------------
#
# Project created by QtCreator 2014-01-21T17:07:42
#
#-------------------------------------------------

QT       += core

include(../QGameOfLife.pri)

TARGET = tests
TEMPLATE = app

CONFIG += c++11

INCLUDEPATH += $$QGAMEOFLIFE_LIB

LIBS += -L$$QGAMEOFLIFE_BIN -lQGameOfLife -lgtest

SOURCES += main.cpp \
    testboard.cpp

#HEADERS  +=

