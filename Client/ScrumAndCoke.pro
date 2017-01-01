#-------------------------------------------------
#
# Project created by QtCreator 2016-04-16T15:51:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ScrumAndCoke
TEMPLATE = app


SOURCES +=\
        LoginWindow.cpp \
    Main.cpp \
    Socket.cpp \
    User.cpp

HEADERS  += LoginWindow.h \
    Socket.h \
    User.h

FORMS    += LoginWindow.ui
