#-------------------------------------------------
#
# Project created by QtCreator 2013-10-14T14:17:36
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = main
TEMPLATE = app

LIBS += -lvlc-qt -lvlc-qt-widgets

INCLUDEPATH += \
../ \
../Streaming/ \
../Calibration/ControlPID \
../AHRS \
../Navigation \
../Connection


SOURCES += main.cpp \
    mainwindow.cpp \
    ../Streaming/streaming.cpp \
    ../Calibration/ControlPID/controlpid.cpp \
    ../AHRS/ahrs.cpp \
    ../Navigation/navigation.cpp \
    ../Connection/connectiondialog.cpp \
    ../AddOn/qcustomplot.cpp

HEADERS  += mainwindow.h \
    ../Streaming/streaming.h \
    ../Calibration/ControlPID/controlpid.h \
    ../AHRS/ahrs.h \
    ../Navigation/navigation.h \
    ../Connection/GCS_SBC_Data.h \
    ../Connection/connectiondialog.h \
    ../AddOn/qcustomplot.h

FORMS    += mainwindow.ui \
    ../Streaming/streaming.ui \
    ../Calibration/ControlPID/controlpid.ui \
    ../AHRS/ahrs.ui \
    ../Navigation/navigation.ui
