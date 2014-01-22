#-------------------------------------------------
#
# Project created by QtCreator 2014-01-21T17:07:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../QGameOfLife.pri)

TARGET = QGameOfLife
TEMPLATE = app

CONFIG += c++11

INCLUDEPATH += $$QGAMEOFLIFE_LIB

LIBS += -L$$QGAMEOFLIFE_BIN -lQGameOfLife -lgtest

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.hpp

