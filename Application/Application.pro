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
    map.cpp \
    personalerrors.cpp \
    glyph.cpp \
    piechart.cpp \
    starglyph.cpp \
    ../Additional/Libraries/LM/shpreader.cpp \
    ../Additional/Libraries/LM/reader.cpp \
    ../Additional/Libraries/SCZ/segment.cpp \
    ../Additional/Libraries/SCZ/mapextractor.cpp \
    ../Additional/Libraries/SCZ/polygon.cpp \
    ../Additional/Libraries/LM/boundingbox.cpp \
    ../Additional/Libraries/LM/csvreader.cpp \
    ../Additional/Libraries/SCZ/contiguitybuilder.cpp \
    ../Additional/Libraries/SCZ/contiguousarea.cpp \
    ../Additional/Libraries/SCZ/neighbourchecker.cpp \
    ../Additional/Libraries/SCZ/treenode.cpp \
    ../Additional/Libraries/SCZ/linkedlist.cpp \
    ../Additional/Libraries/SCZ/boundary.cpp \
    ../Additional/Libraries/SCZ/container.cpp \
    ../Additional/Libraries/SCZ/treebuilder.cpp \
    ../Additional/Libraries/LM/crfreader.cpp \
    ../Additional/Libraries/LM/crfwriter.cpp \
    ../Additional/Libraries/LM/crfrow.cpp \
    ../Additional/Libraries/LM/writer.cpp \
    ../Additional/Libraries/LM/IntersectTester/IntersectTester.cpp \
    ../Additional/Libraries/LM/IntersectTester/AABB.cpp \
    legendcanvas.cpp \
    wheelglyph.cpp \
    barchart.cpp

HEADERS  += maininterfacewindow.h \
    canvas.h \
    map.h \
    glyph.h \
    piechart.h \
    starglyph.h \
    ../Additional/Libraries/LM/shpreader.h \
    ../Additional/Libraries/LM/reader.h \
    ../Additional/Libraries/SCZ/segment.h \
    ../Additional/Libraries/SCZ/mapextractor.h \
    ../Additional/Libraries/SCZ/polygon.h \
    ../Additional/Libraries/LM/boundingbox.h \
    ../Additional/Libraries/LM/csvreader.h \
    ../Additional/Libraries/Spectrum/colourmanager.h \
    ../Additional/Libraries/SCZ/contiguitybuilder.h \
    ../Additional/Libraries/SCZ/contiguousarea.h \
    ../Additional/Libraries/SCZ/neighbourchecker.h \
    ../Additional/Libraries/SCZ/treenode.h \
    ../Additional/Libraries/SCZ/linkedlist.h \
    ../Additional/Libraries/SCZ/boundary.h \
    ../Additional/Libraries/SCZ/container.h \
    ../Additional/Libraries/SCZ/treebuilder.h \
    ../Additional/Libraries/LM/crfreader.h \
    ../Additional/Libraries/LM/crfwriter.h \
    ../Additional/Libraries/LM/crfrow.h \
    ../Additional/Libraries/LM/crfreader.h.autosave \
    ../Additional/Libraries/LM/writer.h \
    ../Additional/Libraries/LM/IntersectTester/IntersectTester.h \
    ../Additional/Libraries/LM/IntersectTester/AABB.h \
    legendcanvas.h \
    wheelglyph.h \
    barchart.h

FORMS    += maininterfacewindow.ui

LIBS += -lgdal -lGL -lGLU -lglut

INCLUDEPATH += ../Additional/Libraries/
