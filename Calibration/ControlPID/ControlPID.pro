#-------------------------------------------------
#
# Project created by QtCreator 2013-09-29T19:07:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

TARGET = ControlPID

SOURCES += main.cpp \
    controlpid.cpp \
    ../../AddOn/qcustomplot.cpp

HEADERS += \
    controlpid.h \
    ../../AddOn/qcustomplot.h

FORMS += \
    controlpid.ui
