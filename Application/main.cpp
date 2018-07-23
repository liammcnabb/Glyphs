#include "maininterfacewindow.h"
#include <QApplication>
#include <GL/glut.h>

#include <Spectrum/colourmanager.h>

int main(int argc, char *argv[])
{
    ColourManager::Init_ColourManager();
    QApplication a(argc, argv);
    MainInterfaceWindow w;
    glutInit( &argc, argv );
    w.show();

    return a.exec();
}
