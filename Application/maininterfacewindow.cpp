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

    QString dataName = QFileDialog::getOpenFileName( this,
                                    tr( "Open Data File" ),
                                    "path/to/file",
                                    tr( "Comma Seperated Value (*.csv)" ) );

    CsvReader csvReader( dataName.toStdString() );
    csvReader.extract();
    QVector<QStringList> data = csvReader.getData();

    QStringList valueHeaders = data.at(0);
    for( int i = 0; i < ignoredValues; ++i )
        valueHeaders.removeFirst();
    ui->lstHeaders->addItems(valueHeaders);

    Map map( shpreader.getMapData(), data );
    ui->OpenGLWidget->setDefaultOrtho(map.getWrapper());
    ui->OpenGLWidget->setLoadedPolygons( map.getLoadedPolygons() );
    ui->OpenGLWidget->update();
    return;
}

void MainInterfaceWindow::on_lstHeaders_itemDoubleClicked(QListWidgetItem *item)
{
    ui->OpenGLWidget->VALUE_INDEX = ignoredValues +
            ui->lstHeaders->currentRow();
    ui->OpenGLWidget->update();
}
