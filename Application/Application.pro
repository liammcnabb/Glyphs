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
    ../Additional/Libraries/LM/reader.cpp \
    map.cpp \
    ../Additional/Libraries/SCZ/segment.cpp \
    ../Additional/Libraries/SCZ/mapextractor.cpp \
    ../Additional/Libraries/SCZ/polygon.cpp \
    ../Additional/Libraries/LM/aabb.cpp \
    ../Additional/Libraries/LM/boundingbox.cpp \
    ../Additional/Libraries/LM/csvreader.cpp \
    personalerrors.cpp \
    glyph.cpp \
    piechart.cpp

HEADERS  += maininterfacewindow.h \
    canvas.h \
    ../Additional/Libraries/LM/shpreader.h \
    ../Additional/Libraries/LM/reader.h \
    map.h \
    ../Additional/Libraries/SCZ/segment.h \
    ../Additional/Libraries/SCZ/mapextractor.h \
    ../Additional/Libraries/SCZ/polygon.h \
    ../Additional/Libraries/LM/aabb.h \
    ../Additional/Libraries/LM/boundingbox.h \
    ../Additional/Libraries/LM/csvreader.h \
    ../Additional/Libraries/Spectrum/colourmanager.h \
    glyph.h \
    piechart.h

FORMS    += maininterfacewindow.ui

LIBS += -lgdal -lGL -lGLU -lglut

INCLUDEPATH += ../Additional/Libraries/
