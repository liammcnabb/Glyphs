#include "maininterfacewindow.h"
#include "ui_maininterfacewindow.h"

MainInterfaceWindow::MainInterfaceWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainInterfaceWindow)
{
    ui->setupUi(this);
    ui->virtualzoom->setEnabled(false);
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

    QString recipeLoc = QFileDialog::getOpenFileName( this,
                                    tr( "Recipe File" ),
                                    "path/to/file",
                                    tr( "Choropleth Recipe File (*.crf)" ) );


    CsvReader csvReader( dataName.toStdString() );
    csvReader.extract();
    QVector<QStringList> data = csvReader.getData();

    QStringList valueHeaders = data.at(0);
    for( int i = 0; i < ignoredValues; ++i )
        valueHeaders.removeFirst();
    ui->lstHeaders->addItems(valueHeaders);

    Map map( shpreader.getMapData(), data, recipeLoc );
    ui->virtualzoom->setEnabled(true);
    ui->OpenGLWidget->setDefaultOrtho(map.getWrapper());
    ui->OpenGLWidget->setLoadedPolygons( map.getLoadedPolygons() );
    setFullHierarchies( map.getHierarchies() );
    on_virtualzoom_valueChanged(0);
//    ui->OpenGLWidget->setGroomedPolygons( map.getHierarchies() );
    return;
}

void MainInterfaceWindow::on_lstHeaders_itemDoubleClicked(QListWidgetItem *item)
{
    ui->OpenGLWidget->VALUE_INDEX = ignoredValues +
            ui->lstHeaders->currentRow();
    ui->OpenGLWidget->update();
}

void MainInterfaceWindow::on_rdo_DebugCentroids_released()
{
    ui->OpenGLWidget->changeColorMap(ui->OpenGLWidget->DIVERGING);
    ui->OpenGLWidget->setGlyphType(ui->OpenGLWidget->GLYPH_CENTROID);
    ui->OpenGLWidget->update();
}

void MainInterfaceWindow::on_rdo_EqualSegmentPie_released()
{
    ui->OpenGLWidget->changeColorMap(ui->OpenGLWidget->DIVERGING);
    ui->OpenGLWidget->setGlyphType(ui->OpenGLWidget->GLYPH_EQUAL_PIE);
    ui->OpenGLWidget->update();
}

void MainInterfaceWindow::on_rdo_VariableSegmentPie_released()
{
    ui->OpenGLWidget->changeColorMap(ui->OpenGLWidget->CATEGORICAL);
    ui->OpenGLWidget->setGlyphType(ui->OpenGLWidget->GLYPH_VARIABLE_PIE);
    ui->OpenGLWidget->update();
}

void MainInterfaceWindow::on_virtualzoom_valueChanged(int value)
{
    double minScreenSpace = double(value) / 100;
    QVector<TreeNode> visiblePolygons;
    visiblePolygons = declareVisiblePolygons(getFullHierarchies(), minScreenSpace);
    ui->OpenGLWidget->setGroomedPolygons( visiblePolygons );
//    qDebug() << visiblePolygons.size();
    ui->OpenGLWidget->update();

}

QVector<TreeNode> MainInterfaceWindow::getFullHierarchies() const
{
    return m_fullHierarchies;
}

void MainInterfaceWindow::setFullHierarchies(const QVector<TreeNode> &fullHierarchies)
{
    m_fullHierarchies = fullHierarchies;
}

QVector<TreeNode> MainInterfaceWindow::declareVisiblePolygons(
        QVector<TreeNode> list,
        double minScreenSpace )
{
    QVector<TreeNode> visible,temp;
    double minArea = minScreenSpace * (
                ui->OpenGLWidget->getLength() * ui->OpenGLWidget->getLength() )
            / 100;

    for( int i = 0; i < list.size(); ++i )
    {
        temp = visibleNodes(minArea, list.at(i) );

        for( int j = 0; j < temp.size(); ++j )
            visible.append( temp.at(j) );
    }

    return visible;
}

QVector<TreeNode> MainInterfaceWindow::visibleNodes( double minScreenSpace,
                                     TreeNode node )
{
    QVector<TreeNode> currentList;
    visibleNodes( minScreenSpace, &node, &currentList );

    if ( currentList.size() == 0 )
        currentList.append( node );

    return currentList;
}

void MainInterfaceWindow::visibleNodes( double minScreenSpace, TreeNode* node,
                                        QVector<TreeNode>* currentList )
{
    if ( node->getArea() > minScreenSpace &&
                ( ( node->getLeftChild() == nullptr &&
                    node->getRightChild() == nullptr ) ||
                  ( node->getLeftChild()->getArea() < minScreenSpace ||
                    node->getRightChild()->getArea() < minScreenSpace ) ) )
        {
            currentList->append( node );
            return;
        }
        else
        {
            if ( node->getLeftChild() != nullptr )
                visibleNodes( minScreenSpace, node->getLeftChild(),
                              currentList );
            if ( node->getRightChild() != nullptr )
                visibleNodes( minScreenSpace, node->getRightChild(),
                              currentList );
            return;
        }

        return;
}

void MainInterfaceWindow::on_GlyphSize_valueChanged(int value)
{
    ui->OpenGLWidget->setGlyphSize(float(value)/2);
    ui->OpenGLWidget->update();
}

void MainInterfaceWindow::on_actionDebugMousePointer_toggled(bool arg1)
{
    ui->OpenGLWidget->setDebugMousePointer(arg1);
    ui->OpenGLWidget->update();
}
