#-------------------------------------------------
#
# Project created by QtCreator 2018-07-19T12:28:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Application
TEMPLATE = app


SOURCES += main.cpp\
        maininterfacewindow.cpp \
    canvas.cpp

HEADERS  += maininterfacewindow.h \
    canvas.h

FORMS    += maininterfacewindow.ui

LIBS += -lgdal -lGL -lGLU -lglut
