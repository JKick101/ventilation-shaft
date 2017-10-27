#-------------------------------------------------
#
# Project created by QtCreator 2017-03-29T22:23:50
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS=-std=gnu++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = went
TEMPLATE = app


SOURCES += main.cpp\
        wentil.cpp \
    panelwidget.cpp \
    connect.cpp \
    qcustomplot.cpp \
    graphic.cpp

HEADERS  += wentil.h \
    panelwidget.h \
    connect.h \
    qcustomplot.h \
    graphic.h

win32: LIBS += -L$$PWD/Modbus/lib/ -lmodbus

INCLUDEPATH += $$PWD/Modbus/include
DEPENDPATH += $$PWD/Modbus/include
