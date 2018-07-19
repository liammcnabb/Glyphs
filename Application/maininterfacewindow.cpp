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
    QString fileName = QFileDialog::getOpenFileName( this,
                                                     tr( "Open Shape File" ),
                                                     "path/to/file",
                                                     tr( "ESRI Shape Files (*.shp)" ) );
    ShpReader shpreader( fileName );
    Map map(shpreader.getMapData());
    return;
}
