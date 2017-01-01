#-------------------------------------------------
#
# Project created by QtCreator 2016-04-10T13:41:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BoxRun
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    physics.cpp

HEADERS  += mainwindow.h \
    physics.h

FORMS    += mainwindow.ui

LIBS += $$PWD/libs/Box2D/libBox2D.a

INCLUDEPATH += $$PWD/includes


