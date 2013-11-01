#-------------------------------------------------
#
# Project created by QtCreator 2013-09-29T16:19:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

TARGET = AHRS

SOURCES += main.cpp \
    ../AddOn/qcustomplot.cpp \
    ahrs.cpp

HEADERS += \
    ../AddOn/qcustomplot.h \
    ahrs.h

FORMS += \
    ahrs.ui
