#include "maininterfacewindow.h"
#include "ui_maininterfacewindow.h"

MainInterfaceWindow::MainInterfaceWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainInterfaceWindow)
{
    ui->setupUi(this);
}

MainInterfaceWindow::~MainInterfaceWindow()
{
    delete ui;
}

void MainInterfaceWindow::on_actionEngland_Example_triggered()
{
    QString fileName = "/home/liam/Projects/Glyphs/Additional/Materials/CCG/CCG.shp";
    ShpReader shpreader( fileName );
    return;
}
