#-------------------------------------------------
#
# Project created by QtCreator 2013-09-29T15:48:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Streaming
TEMPLATE = app

LIBS += -lvlc-qt -lvlc-qt-widgets

SOURCES += main.cpp\
    streaming.cpp

HEADERS  += \
    streaming.h

FORMS    += \
    streaming.ui
