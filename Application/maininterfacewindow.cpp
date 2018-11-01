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
//    ui->lstHeaders->addItems(valueHeaders);
    setValueHeaders(valueHeaders);
    ui->GlLegend->setValueHeaders(valueHeaders);
    QVector<bool> valueF;
    for(int i = 0; i < valueHeaders.size(); ++i )
        valueF.append(true);

    setValueFilters(valueF);
    ui->GlLegend->setValueFilters(valueF);
    ui->OpenGLWidget->setValueFilters(valueF);

    initializeTable(valueHeaders);

    Map map( shpreader.getMapData(), data, recipeLoc );
    ui->virtualzoom->setEnabled(true);
    ui->OpenGLWidget->setDefaultOrtho(map.getWrapper());
    ui->OpenGLWidget->setLoadedPolygons( map.getLoadedPolygons() );
    setFullHierarchies( map.getHierarchies() );
    on_virtualzoom_valueChanged(0);
//    ui->OpenGLWidget->setGroomedPolygons( map.getHierarchies() );
    calculateStandardDeviation(ui->OpenGLWidget->getGroomedPolygons());

    return;
}

void MainInterfaceWindow::calculateStandardDeviation( QVector<TreeNode> list )
{

    QVector<float> means;
    QVector<float> maxes;
    QVector<float> mins;

    for( int i = 4; i < list.first().getValues().size(); ++i )
    {
        float max = -std::numeric_limits<float>::max();
        float min = std::numeric_limits<float>::max();
        float currentMean = 0;
        for( int j = 0; j < list.size(); ++j )
        {
            max = std::max( max, list.at(j).getValues().at(i).toFloat() );
            min = std::min( min, list.at(j).getValues().at(i).toFloat() );
            currentMean += list.at(j).getValues().at(i).toFloat();
        }
        currentMean = currentMean / list.size();
        means.append(currentMean);
        maxes.append(max);
        mins.append(min);
    }

    if(!getSaved())
    {
        setLeafMaxes(maxes);
        setLeafMins(mins);
        setSaved(true);
    }

    ui->OpenGLWidget->setMeans(means);
    ui->OpenGLWidget->setMaxes(maxes);
    ui->OpenGLWidget->setMins(mins);

    ui->GlLegend->setMeans(means);
    ui->GlLegend->setMaxes(maxes);
    ui->GlLegend->setMins(mins);

    ui->GlLegend->initializeLegend(means);

    return;
}


void MainInterfaceWindow::on_lstHeaders_doubleClicked(const QModelIndex &index)
{
        ui->OpenGLWidget->VALUE_INDEX = ignoredValues + index.row();
        ui->OpenGLWidget->update();
}


//void MainInterfaceWindow::on_lstHeaders_itemDoubleClicked(QListWidgetItem *item)
//{
//    ui->OpenGLWidget->VALUE_INDEX = ignoredValues +
//            ui->lstHeaders->currentRow();
//    ui->OpenGLWidget->update();
//}

void MainInterfaceWindow::on_rdo_DebugCentroids_released()
{
    ui->OpenGLWidget->changeColorMap(ui->OpenGLWidget->DIVERGING);
    ui->OpenGLWidget->setGlyphType(ui->OpenGLWidget->GLYPH_CENTROID);
    ui->GlLegend->setCurrentGlyphType(ui->GlLegend->GLYPH_CENTROID);
    ui->OpenGLWidget->update();
    ui->GlLegend->update();
}

void MainInterfaceWindow::on_rdo_EqualSegmentPie_released()
{
    ui->OpenGLWidget->changeColorMap(ui->OpenGLWidget->DIVERGING);
    ui->OpenGLWidget->setGlyphType(ui->OpenGLWidget->GLYPH_EQUAL_PIE);
    ui->GlLegend->setCurrentGlyphType(ui->GlLegend->GLYPH_EQUAL_PIE);
    ui->OpenGLWidget->update();
    ui->GlLegend->update();
}

void MainInterfaceWindow::on_rdo_VariableSegmentPie_released()
{
    ui->OpenGLWidget->changeColorMap(ui->OpenGLWidget->CATEGORICAL);
    ui->OpenGLWidget->setGlyphType(ui->OpenGLWidget->GLYPH_VARIABLE_PIE);
        ui->GlLegend->setCurrentGlyphType(ui->GlLegend->GLYPH_VARIABLE_PIE);
    ui->OpenGLWidget->update();
    ui->GlLegend->update();
}

void MainInterfaceWindow::on_rdo_StarGlyph_released()
{
    ui->OpenGLWidget->changeColorMap(ui->OpenGLWidget->CATEGORICAL);
    ui->OpenGLWidget->setGlyphType(ui->OpenGLWidget->GLYPH_STAR);
    ui->GlLegend->setCurrentGlyphType(ui->GlLegend->GLYPH_STAR);
    ui->OpenGLWidget->update();
    ui->GlLegend->update();
}

void MainInterfaceWindow::on_radioButton_released()
{
    ui->OpenGLWidget->changeColorMap(ui->OpenGLWidget->CATEGORICAL);
    ui->OpenGLWidget->setGlyphType(ui->OpenGLWidget->GLYPH_BAR);
    ui->GlLegend->setCurrentGlyphType(ui->GlLegend->GLYPH_BAR);
    ui->OpenGLWidget->update();
    ui->GlLegend->update();
}

void MainInterfaceWindow::calculateNewlyVisible(int screenSpaceValue)
{
    ui->verticalSlider->setEnabled(false);
    ui->virtualzoom->setEnabled(false);
    double transitionFrames = 12;
    double frameSkip = 1;
    double minScreenSpace = double(screenSpaceValue) / 100;
    QVector<TreeNode> visiblePolygons;
    visiblePolygons = declareVisiblePolygons(getFullHierarchies(), minScreenSpace);
    splitVisible(visiblePolygons);
    ui->OpenGLWidget->setGroomedPolygons( visiblePolygons );

//    calculateStandardDeviation(ui->OpenGLWidget->getGroomedPolygons());

    if(visiblePolygons.size() != ui->OpenGLWidget->getTransitionNeutral().size())
    {
        ui->OpenGLWidget->setTransitionState(true);
//        float incrementer = ui->OpenGLWidget->getGlyphSize() / transitionFrames;
        for( int i = 0; i < transitionFrames; i+=frameSkip )
        {
            ui->OpenGLWidget->setCurrentTransitionSize(i);
            ui->OpenGLWidget->repaint();
            qApp->processEvents();
        }

        ui->OpenGLWidget->setTransitionState(false);
    }
    ui->virtualzoom->setEnabled(true);
    ui->verticalSlider->setEnabled(true);
    ui->virtualzoom->setFocus();

    if(getRangeBreadth() == RANGE_SHOWN)
        calculateStandardDeviation(ui->OpenGLWidget->getGroomedPolygons());

    if(getRangeDepth() == RANGE_OVERALL)
        calculateOverallRange( ui->OpenGLWidget->getMins(),
                               ui->OpenGLWidget->getMaxes() );
    ui->OpenGLWidget->update();
}

QVector<bool> MainInterfaceWindow::getValueFilters() const
{
    return m_valueFilters;
}

void MainInterfaceWindow::setValueFilters(const QVector<bool> &valueFilters)
{
    m_valueFilters = valueFilters;
}

void MainInterfaceWindow::calculateOverallRange(QVector<float> mins, QVector<float> maxes)
{
    float max = -std::numeric_limits<float>::max();
    float min = std::numeric_limits<float>::max();

    QVector<float> newMins = mins;
    QVector<float> newMaxes = maxes;

    for( int i = 0; i < mins.size(); ++i )
    {
        max = std::max( max, maxes.at(i) );
        min = std::min( min, mins.at(i) );
    }

    for( int i = 0; i < mins.size(); ++i )
    {
        newMins[i] = min;
        newMaxes[i] = max;
    }

    ui->OpenGLWidget->setMaxes(newMaxes);
    ui->OpenGLWidget->setMins(newMins);

    ui->GlLegend->setMaxes(newMaxes);
    ui->GlLegend->setMins(newMins);
}

bool MainInterfaceWindow::getSaved() const
{
    return m_saved;
}

void MainInterfaceWindow::setSaved(bool saved)
{
    m_saved = saved;
}

int MainInterfaceWindow::getRangeDepth() const
{
    return m_rangeDepth;
}

void MainInterfaceWindow::setRangeDepth(int rangeDepth)
{
    m_rangeDepth = rangeDepth;
}

int MainInterfaceWindow::getRangeBreadth() const
{
    return m_rangeBreadth;
}

void MainInterfaceWindow::setRangeBreadth(int rangeBreadth)
{
    m_rangeBreadth = rangeBreadth;
}

QVector<float> MainInterfaceWindow::getLeafMaxes() const
{
    return m_leafMaxes;
}

void MainInterfaceWindow::setLeafMaxes(const QVector<float> &leafMaxes)
{
    m_leafMaxes = leafMaxes;
}

QVector<float> MainInterfaceWindow::getLeafMins() const
{
    return m_leafMins;
}

void MainInterfaceWindow::setLeafMins(const QVector<float> &leafMins)
{
    m_leafMins = leafMins;
}


void MainInterfaceWindow::on_virtualzoom_valueChanged(int value) ///Transition
{
    if(getPreviousVirtualZoomValue() < value)
        ui->OpenGLWidget->setTransitionType(ui->OpenGLWidget->TRANSITION_IN);
    else
        ui->OpenGLWidget->setTransitionType(ui->OpenGLWidget->TRANSITION_OUT);

    setPreviousVirtualZoomValue(value);
    calculateNewlyVisible(value);
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

void MainInterfaceWindow::initializeTable(QStringList list)
{
    QStandardItemModel* model = new QStandardItemModel();
//    int lineIndex =0;

    QStringList headers;
    headers.append("Shown");
    headers.append("ValueHeader");


    model->setHorizontalHeaderLabels(headers);
    ui->lstHeaders->resizeColumnsToContents();
    ui->lstHeaders->horizontalHeader()->setStretchLastSection(true);

    for( int i = 0; i < list.size(); ++i )
    {
        QStandardItem* checkbox, *title;
//        id = new QStandardItem(QString::number(i));
        title = new QStandardItem(list.at(i));
        checkbox = new QStandardItem(true);
        checkbox->setCheckable(true);
        checkbox->setCheckState(Qt::Checked);
//        model->setItem(i,0,id);
        model->setItem(i,1,title);
        model->setItem(i,0,checkbox);
    }
    ui->lstHeaders->setModel(model);
    ui->lstHeaders->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->lstHeaders->show();

}


QVector<TreeNode> MainInterfaceWindow::getFullHierarchies() const
{
    return m_fullHierarchies;
}

void MainInterfaceWindow::setFullHierarchies(const QVector<TreeNode> &fullHierarchies)
{
    m_fullHierarchies = fullHierarchies;
}

QStringList MainInterfaceWindow::getValueHeaders() const
{
    return m_valueHeaders;
}

void MainInterfaceWindow::setValueHeaders(const QStringList &valueHeaders)
{
    m_valueHeaders = valueHeaders;
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

void MainInterfaceWindow::on_AreaOpacity_valueChanged(int value)
{

    ui->OpenGLWidget->setAreaOpacity(float(value)/100.0f);
    ui->OpenGLWidget->update();
}

void MainInterfaceWindow::on_chkColoredStarLines_toggled(bool checked)
{
    ui->OpenGLWidget->setColorStarLines(checked);
    ui->GlLegend->setColorStarLines(checked);
    ui->OpenGLWidget->update();
    ui->GlLegend->update();
}


void MainInterfaceWindow::on_rdoOutline_released()
{
    ui->OpenGLWidget->setHiddenIndicator(ui->OpenGLWidget->HIDDEN_OUTLINE);
    ui->OpenGLWidget->update();
}

void MainInterfaceWindow::on_rdoSize_released()
{
    ui->OpenGLWidget->setHiddenIndicator(ui->OpenGLWidget->HIDDEN_SIZE);
    ui->OpenGLWidget->update();
}

void MainInterfaceWindow::on_rdoRings_released()
{
    ui->OpenGLWidget->setHiddenIndicator(ui->OpenGLWidget->HIDDEN_RINGS);
    ui->OpenGLWidget->update();
}

void MainInterfaceWindow::on_rdoOutlineSize_released()
{
    ui->OpenGLWidget->setHiddenIndicator(ui->OpenGLWidget->HIDDEN_SIZEOUTLINE);
    ui->OpenGLWidget->update();
}


void MainInterfaceWindow::on_verticalSlider_valueChanged(int value)
{
    float pos = float( value ) / 100;
        if( value == float( -100 ) )
            ui->OpenGLWidget->setZoom( float( -0.99 ) );
        else if ( value == float( 100 ) )
            ui->OpenGLWidget->setZoom( float( 0.99 ) );
        else
            ui->OpenGLWidget->setZoom( pos );

//        ui->OpenGLWidget->setOrtho();
        if(pos < 0)
            ui->OpenGLWidget->setTransitionType(ui->OpenGLWidget->TRANSITION_OUT);
        else
            ui->OpenGLWidget->setTransitionType(ui->OpenGLWidget->TRANSITION_OUT);

        calculateNewlyVisible(ui->virtualzoom->value());
        ui->verticalSlider->setFocus();
        ui->OpenGLWidget->update();
}

int MainInterfaceWindow::getPreviousVirtualZoomValue() const
{
    return previousVirtualZoomValue;
}

void MainInterfaceWindow::setPreviousVirtualZoomValue(int value)
{
    previousVirtualZoomValue = value;
}

void MainInterfaceWindow::on_btnAutomatic_released()
{
    double glyphSize = ui->OpenGLWidget->getGlyphSize()*10;

    ui->virtualzoom->setValue(glyphSize);
//    on_virtualzoom_valueChanged(glyphSize);
}

void MainInterfaceWindow::on_actionShow_Extents_toggled(bool arg1)
{
    ui->OpenGLWidget->setExtents(arg1);
    ui->OpenGLWidget->update();
}

void MainInterfaceWindow::on_rdoRangebyLeaf_released()
{
    setRangeBreadth(RANGE_LEAF);
    ui->OpenGLWidget->setMaxes(getLeafMaxes());
    ui->OpenGLWidget->setMins(getLeafMins());

    ui->GlLegend->setMaxes(getLeafMaxes());
    ui->GlLegend->setMins(getLeafMins());
    if(getRangeDepth() == RANGE_OVERALL)
        calculateOverallRange( getLeafMins(), getLeafMaxes() );

    ui->OpenGLWidget->update();
}

void MainInterfaceWindow::on_rdoRangeOfShown_released()
{
    setRangeBreadth(RANGE_SHOWN);
    calculateNewlyVisible(ui->virtualzoom->value());

    ui->OpenGLWidget->update();
}

void MainInterfaceWindow::on_rdoCalcPerValue_released()
{
    setRangeDepth(RANGE_PER_VALUE);
    if(getRangeBreadth() == RANGE_LEAF)
        on_rdoRangebyLeaf_released();
    else
        calculateNewlyVisible(ui->virtualzoom->value());

    ui->OpenGLWidget->update();
}

void MainInterfaceWindow::on_rdoCalcOverall_released()
{
    setRangeDepth(RANGE_OVERALL);
    if(getRangeBreadth() == RANGE_LEAF)
        on_rdoRangebyLeaf_released();
    else
        calculateNewlyVisible(ui->virtualzoom->value());

    ui->OpenGLWidget->update();
}

void MainInterfaceWindow::on_lstHeaders_clicked(const QModelIndex &index)
{
    m_valueFilters[index.row()] =  index.data(Qt::CheckStateRole).toBool();
    ui->OpenGLWidget->setValueFilters(getValueFilters());
    ui->GlLegend->setValueFilters(getValueFilters());
    ui->OpenGLWidget->update();
    ui->GlLegend->update();
//    qDebug() << index.column() << index.row() << index.data(Qt::CheckStateRole).toBool();
}

void MainInterfaceWindow::on_chkMatchingLines_toggled(bool checked)
{
    ui->OpenGLWidget->setIndicatorMatches(checked);
    ui->OpenGLWidget->update();
}

void MainInterfaceWindow::on_toolButton_released()
{
    ui->OpenGLWidget->setColorMap(0);
    ui->GlLegend->setColorMap(0);
    ui->OpenGLWidget->update();
    ui->GlLegend->update();
}

void MainInterfaceWindow::on_toolButton_2_released()
{
    ui->OpenGLWidget->setColorMap(1);
    ui->GlLegend->setColorMap(1);
    ui->OpenGLWidget->update();
    ui->GlLegend->update();
}

void MainInterfaceWindow::on_toolButton_3_released()
{
    ui->OpenGLWidget->setColorMap(3);
    ui->GlLegend->setColorMap(3);
    ui->OpenGLWidget->update();
    ui->GlLegend->update();
}

void MainInterfaceWindow::on_toolButton_4_released()
{
    ui->OpenGLWidget->setColorMap(2);
    ui->GlLegend->setColorMap(2);
    ui->OpenGLWidget->update();
    ui->GlLegend->update();
}

void MainInterfaceWindow::on_toolButton_5_released()
{
    ui->OpenGLWidget->setColorMap(5);
    ui->GlLegend->setColorMap(5);
    ui->OpenGLWidget->update();
    ui->GlLegend->update();
}



void MainInterfaceWindow::on_pushButton_6_released()
{
    ui->OpenGLWidget->setColorMap(6);
    ui->GlLegend->setColorMap(6);
    ui->OpenGLWidget->update();
    ui->GlLegend->update();
}

void MainInterfaceWindow::on_pushButton_7_released()
{
    ui->OpenGLWidget->setColorMap(7);
    ui->GlLegend->setColorMap(7);
    ui->OpenGLWidget->update();
    ui->GlLegend->update();
}

void MainInterfaceWindow::on_rdoFC1_released()
{
    //Do not map (Default)
    ui->OpenGLWidget->setFocusContextType(0);
    ui->OpenGLWidget->update();
}

void MainInterfaceWindow::on_rdoFC2_released()
{
    ui->OpenGLWidget->setFocusContextType(1);
    ui->OpenGLWidget->update();
    // GreyScale
}
