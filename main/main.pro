#-------------------------------------------------
#
# Project created by QtCreator 2013-10-14T14:17:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = main
TEMPLATE = app

LIBS += -lvlc-qt -lvlc-qt-widgets

INCLUDEPATH += \
../Streaming/

SOURCES += main.cpp \
    mainwindow.cpp \
    ../Streaming/streaming.cpp

HEADERS  += mainwindow.h \
    ../Streaming/streaming.h

FORMS    += mainwindow.ui \
    ../Streaming/streaming.ui
