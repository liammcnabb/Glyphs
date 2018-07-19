#include "maininterfacewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainInterfaceWindow w;
    w.show();

    return a.exec();
}
