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
    canvas.cpp \
    ../Additional/Libraries/LM/shpreader.cpp \
    ../Additional/Libraries/LM/reader.cpp

HEADERS  += maininterfacewindow.h \
    canvas.h \
    ../Additional/Libraries/LM/shpreader.h \
    ../Additional/Libraries/LM/reader.h

FORMS    += maininterfacewindow.ui

LIBS += -lgdal -lGL -lGLU -lglut

INCLUDEPATH += ../Additional/Libraries/
