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
    ui->OpenGLWidget->setDataHeaders(valueHeaders);
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
    calculateStandardDeviation(map.getHierarchies());
    return;
}

void MainInterfaceWindow::calculateStandardDeviation( QVector<TreeNode> list )
{
    QVector<float> means;

    for( int i = 4; i < list.first().getValues().size(); ++i )
    {
        float currentMean = 0;
        for( int j = 0; j < list.size(); ++j )
        {
            currentMean += list.at(j).getValues().at(i).toFloat();
        }
        currentMean = currentMean / list.size();
        means.append(currentMean);
        qDebug() << means.last();
    }

    ui->OpenGLWidget->setMeans(means);
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

void MainInterfaceWindow::on_rdo_StarGlyph_released()
{
    ui->OpenGLWidget->changeColorMap(ui->OpenGLWidget->CATEGORICAL);
    ui->OpenGLWidget->setGlyphType(ui->OpenGLWidget->GLYPH_STAR);
    ui->OpenGLWidget->update();
}


void MainInterfaceWindow::on_virtualzoom_valueChanged(int value) ///Transition
{
    double minScreenSpace = double(value) / 100;
    QVector<TreeNode> visiblePolygons;
    visiblePolygons = declareVisiblePolygons(getFullHierarchies(), minScreenSpace);
    splitVisible(visiblePolygons);
    ui->OpenGLWidget->setGroomedPolygons( visiblePolygons );

     ui->OpenGLWidget->setTransitionState(true);

    float incrementer = ui->OpenGLWidget->getGlyphSize() / 25;
    for( int i = 0; i < 25; i+=2 )
    {
        ui->OpenGLWidget->setCurrentTransitionSize(incrementer*i);
        ui->OpenGLWidget->repaint();
        qApp->processEvents();
    }

//    QVector<TreeNode> visible;
//    visible.append(ui->OpenGLWidget->getTransitionNeutral());
//    visible.append(ui->OpenGLWidget->getTransitionAdd());
////    visible.append(ui->OpenGLWidget->getTransitionRemove());
//    ui->OpenGLWidget->setGroomedPolygons(visible);

     ui->OpenGLWidget->setTransitionState(false);
//    qDebug() << visiblePolygons.size();
    ui->OpenGLWidget->update();

}


void MainInterfaceWindow::splitVisible(QVector<TreeNode> list)
{
    if(ui->OpenGLWidget->getGroomedPolygons().isEmpty())
        return;

     QVector<TreeNode> transitionRemove, transitionAdd, transitionNeutral;

     for( int i = 0; i < list.size(); ++i )
         if( ui->OpenGLWidget->getGroomedPolygons().contains( list.at(i) ) )
             transitionNeutral.append( list.at(i) );
         else
             transitionAdd.append( list.at(i) );

     for( int i = 0; i < ui->OpenGLWidget->getGroomedPolygons().size(); ++i )
         if( !list.contains( ui->OpenGLWidget->getGroomedPolygons().at(i) ) )
             transitionRemove.append(
                         ui->OpenGLWidget->getGroomedPolygons().at(i) );

     ui->OpenGLWidget->setTransitionNeutral(transitionNeutral);
     ui->OpenGLWidget->setTransitionAdd(transitionAdd);
     ui->OpenGLWidget->setTransitionRemove(transitionRemove);
     ui->OpenGLWidget->setTransitionState(true);
     ui->OpenGLWidget->setCurrentTransitionSize(0.0f);

     return;
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

