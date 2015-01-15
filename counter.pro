#-------------------------------------------------
#
# Project created by QtCreator 2015-01-10T22:58:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = counter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dic.cpp

HEADERS  += mainwindow.h \
    dic.h

FORMS    += mainwindow.ui
CONFIG += c++11
