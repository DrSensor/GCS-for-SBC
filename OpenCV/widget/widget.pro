#-------------------------------------------------
#
# Project created by QtCreator 2013-10-27T05:14:01
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = widget

TEMPLATE = app

LIBS += -lGLU -lopencv_core -lopencv_highgui -lopencv_imgproc

SOURCES += main.cpp \
    opencvwidget.cpp \
    opencvprocess.cpp

HEADERS += \
    opencvwidget.h \
    opencvprocess.h
