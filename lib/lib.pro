#-------------------------------------------------
#
# Project created by QtCreator 2014-01-21T17:07:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../QGameOfLife.pri)

TARGET = QGameOfLife
TEMPLATE = lib

CONFIG += c++11

SOURCES += board.cpp

HEADERS  += board.hpp

