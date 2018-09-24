#include "canvas.h"


Canvas::Canvas( QWidget* parent ) : QOpenGLWidget( parent )
{

}

/**
 * @brief Canvas::initializeGL called when the OpenGL Widget is started.
 */
void Canvas::initializeGL()
{

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable( GL_BLEND ); // Required Blending for alpha blending
    glEnable( GL_ALPHA ); // Lets you add alpha values
    //    glEnable( GL_LINE_STIPPLE ); // Enables Dotted Line for use
    glEnable( GL_STENCIL ); //Rendering using stencil buffer (used to render concave polygons)
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
//    glClearColor( BACKGROUND_COL, BACKGROUND_COL, BACKGROUND_COL,
//                  1.0 );
    glClearColor(1,1,1,1);

    changeColorMap( this->DIVERGING );
    ColourManager::InvertColourMap();

    QWidget::setMouseTracking(true);


    //    connect( &timer, SIGNAL( timeout() ), this, SLOT( update() ) );
    //    timer.start( 1000 );
}
void Canvas::mouseMoveEvent( QMouseEvent *event )
{

    setMouse(QPointF( convertedX( float( event->x() ) ),
                      convertedY( float( event->y() ) ) ) );

    if(getGlyphType() == this->GLYPH_EQUAL_PIE ||
            getGlyphType() == GLYPH_VARIABLE_PIE)
    {
        setClickedIndex(findClickedIndex(getMouse(), getPieGlyphs()));
        fillToolTip(getClickedIndex());
    }
        update();



}

float Canvas::convertedX( float windowX )
{
    float newX;
    newX = (getCurrentWrapper().minimums.at(AABB::XDIM) - scaleModifier()) +
            ( ( windowX / this->width() ) *
              ( getLength() + (scaleModifier()*2) ) ) ;
    return newX;
}

float Canvas::convertedY( float windowY )
{
    float newY,reverseY;
    reverseY = -( windowY - 1 - this->height() );

    newY = (getCurrentWrapper().minimums.at(AABB::YDIM) - scaleModifier()) +
            ( ( reverseY / this->height() ) *
              ( getLength() + (scaleModifier()*2) ) );
    return newY;
}

int Canvas::findClickedIndex(QPointF coords, QVector<PieChart> list )
{
    if(DEBUG)
        qDebug() << "Canvas::findClickedIndex(QPointF coords, QVector<PieChart> list ) BEGIN";

    for(int i = 0; i < list.size(); i++)
    {
        QPointF c = list.at(i).centroid();
        if( IntersectTester::isIntersecting( Point( coords.x(),coords.y() ),
                                  Circle( Point( c.x(),c.y() ),
                                  ( getLength() / 100 ) * getGlyphSize() ) ) )
        {
            if(DEBUG)
                qDebug() << "Canvas::findClickedIndex(QPointF coords, QVector<PieChart> list ) END";

            return i;
        }
    }
    if(DEBUG)
        qDebug() << "Canvas::findClickedIndex(QPointF coords, QVector<PieChart> list ) END";

    return NEGATIVE_INDEX;
}

void Canvas::changeColorMap(int mapType)
{

    switch(mapType)
    {
    case this->SEQUENTIAL :
    {
        break;
    }
    case this->DIVERGING :
    {
        if( !ColourManager::InvertColourMapFlag() )
            ColourManager::InvertColourMap();
        ColourMap cMap = CMList::getMapList(CMClassification::DIVERGING)[COLORMAP_INDEX];
        ColourManager::setCurrentColourMap(cMap);

        break;
    }
    case this->CATEGORICAL :
    {
        if( ColourManager::InvertColourMapFlag() )
            ColourManager::InvertColourMap();
        ColourMap cMap = CMList::getMapList(CMClassification::QUALITATIVE)[0];
        ColourManager::setCurrentColourMap(cMap);
        break;
    }
    case this->OUTLINE :
    {
        if( ColourManager::InvertColourMapFlag() )
            ColourManager::InvertColourMap();
        ColourMap cMap = CMList::getMapList(CMClassification::QUALITATIVE)[1];
        ColourManager::setCurrentColourMap(cMap);
        break;
    }
    }
}

void Canvas::fillToolTip(int glyphIndex)
{
    if( glyphIndex <= NEGATIVE_INDEX )
    {
        QWidget::setToolTip(QString());
        return;
    }

    QString string;
    for( int i = 4; i < getGroomedPolygons().at(glyphIndex).getValues().size();
        ++i )
    {
        string.append(getDataHeaders().at(i)+": ");
        string.append(getGroomedPolygons().at(glyphIndex).getValues().at(i)+"%, \n");
    }
    string.remove(string.size()-3,3);
    QWidget::setToolTip(string);
    return;
}

QVector<TreeNode> Canvas::getGroomedPolygons() const
{
    return m_groomedPolygons;
}

void Canvas::setGroomedPolygons(const QVector<TreeNode> &groomedPolygons)
{
    m_groomedPolygons = groomedPolygons;
}

float Canvas::getGlyphSize() const
{
    return glyphSize;
}

void Canvas::setGlyphSize(float value)
{
    glyphSize = value;
}

QPointF Canvas::getMouse() const
{
    return mouse;
}

void Canvas::setMouse(const QPointF &value)
{
    mouse = value;
}

bool Canvas::debugMousePointer() const
{
    return m_debugMousePointer;
}

void Canvas::setDebugMousePointer(bool value)
{
    m_debugMousePointer = value;
}

int Canvas::getClickedIndex() const
{
    return m_clickedIndex;
}

void Canvas::setClickedIndex(int clickedIndex)
{
    m_clickedIndex = clickedIndex;
}

QStringList Canvas::getDataHeaders() const
{
    return dataHeaders;
}

void Canvas::setDataHeaders(const QStringList &value)
{
    dataHeaders = value;
}

QVector<StarGlyph> Canvas::getStarGlyphs() const
{
    return m_starGlyphs;
}

void Canvas::setStarGlyphs(const QVector<StarGlyph> &starGlyphs)
{
    m_starGlyphs = starGlyphs;
}

QVector<float> Canvas::getMeans() const
{
    return m_means;
}

void Canvas::setMeans(const QVector<float> &means)
{
    m_means = means;
}

bool Canvas::getTransitionState() const
{
    return m_transitionState;
}

void Canvas::setTransitionState(bool transitionState)
{
    m_transitionState = transitionState;
}

QVector<TreeNode> Canvas::getTransitionNeutral() const
{
    return m_transitionNeutral;
}

void Canvas::setTransitionNeutral(const QVector<TreeNode> &transitionNeutral)
{
    m_transitionNeutral = transitionNeutral;
}

QVector<TreeNode> Canvas::getTransitionAdd() const
{
    return m_transitionAdd;
}

void Canvas::setTransitionAdd(const QVector<TreeNode> &transitionAdd)
{
    m_transitionAdd = transitionAdd;
}

QVector<TreeNode> Canvas::getTransitionRemove() const
{
    return m_transitionRemove;
}

void Canvas::setTransitionRemove(const QVector<TreeNode> &transitionRemove)
{
    m_transitionRemove = transitionRemove;
}

float Canvas::getCurrentTransitionSize() const
{
    return currentTransitionSize;
}

void Canvas::setCurrentTransitionSize(float value)
{
    currentTransitionSize = value;
}

float Canvas::getAreaOpacity() const
{
    return m_areaOpacity;
}

void Canvas::setAreaOpacity(float areaOpacity)
{
    m_areaOpacity = areaOpacity;
}

QVector<WheelGlyph> Canvas::getWheelGlyphs() const
{
    return m_wheelGlyphs;
}

void Canvas::setWheelGlyphs(const QVector<WheelGlyph> &wheelGlyphs)
{
    m_wheelGlyphs = wheelGlyphs;
}

bool Canvas::getColorStarLines() const
{
    return m_colorStarLines;
}

void Canvas::setColorStarLines(bool colorStarLines)
{
    m_colorStarLines = colorStarLines;
}

int Canvas::getHiddenIndicator() const
{
    return m_hiddenIndicator;
}

void Canvas::setHiddenIndicator(int hiddenIndicator)
{
    m_hiddenIndicator = hiddenIndicator;
}

QVector<BarChart> Canvas::getBarCharts() const
{
    return m_barCharts;
}

void Canvas::setBarCharts(const QVector<BarChart> &barCharts)
{
    m_barCharts = barCharts;
}

float Canvas::getZoom() const
{
    return m_zoom;
}

void Canvas::setZoom(float zoom)
{
    m_zoom = zoom;
}

AABB Canvas::getCurrentWrapper() const
{
    return m_currentWrapper;
}

void Canvas::setCurrentWrapper(const AABB &currentWrapper)
{
    m_currentWrapper = currentWrapper;
}

QVector<float> Canvas::getMaxes() const
{
    return m_maxes;
}

void Canvas::setMaxes(const QVector<float> &maxes)
{
    m_maxes = maxes;
}

QVector<float> Canvas::getMins() const
{
    return m_mins;
}

void Canvas::setMins(const QVector<float> &mins)
{
    m_mins = mins;
}

int Canvas::getTransitionType() const
{
    return transitionType;
}

void Canvas::setTransitionType(int value)
{
    transitionType = value;
}

void Canvas::paintGL()
{
    if(getGroomedPolygons().size() > 0)
        redraw();

}

void Canvas::redraw()
{
    qDebug() << "drawing";
    prepareDraw();
    calculateValueBounds( getGroomedPolygons() );
    drawPolygons( loadedPolygons() );
    if(getTransitionNeutral().isEmpty())
        drawPolygons( getGroomedPolygons() );
    else
    {
        drawPolygons( getTransitionNeutral() );
        drawPolygons( getTransitionAdd() );
    }
    
    glLineWidth( 1 );
    /**Default*/
    switch( getGlyphType() )
    {
    case GLYPH_CENTROID :
    {
        calculateValueBounds( getGroomedPolygons() );
        changeColorMap(this->DIVERGING);
        ColourManager manager(getValueLower(), getValueUpper());
        drawCentroids( getGroomedPolygons(), manager );
        drawLegend( manager );
        break;
    }
    case GLYPH_EQUAL_PIE :
    {
        if(getTransitionState())
        {
            QVector<WheelGlyph> wheels;
            wheels.append( createWheelGlyphs( getTransitionNeutral(), 0) );
            wheels.append( createWheelGlyphs( getTransitionRemove(), -1) );
            wheels.append( createWheelGlyphs( getTransitionAdd(), 1) );
            setWheelGlyphs(wheels);
        }
        else
        {
            if(getTransitionNeutral().isEmpty())
            {
                setWheelGlyphs(createWheelGlyphs( getGroomedPolygons(), 0) );
            }
            else
            {
                QVector<WheelGlyph> wheels;
                wheels.append( createWheelGlyphs( getTransitionNeutral(), 0) );
                wheels.append( createWheelGlyphs( getTransitionAdd(), 0) );
                setWheelGlyphs(wheels);
            }
        }
        calculateValueBounds( getWheelGlyphs() );
        changeColorMap(this->DIVERGING);
        ColourManager manager(-2, 2);
        drawWheelGlyphs( getWheelGlyphs(), manager );
        drawLegend( manager );
        break;
    }
    case GLYPH_VARIABLE_PIE :
    {
        if(getTransitionState())
        {
            QVector<PieChart> pies;
            pies.append( createPieGlyphs( getTransitionNeutral(), GLYPH_VARIABLE_PIE, 0) );
            pies.append( createPieGlyphs( getTransitionRemove(), GLYPH_VARIABLE_PIE, -1) );
            pies.append( createPieGlyphs( getTransitionAdd(), GLYPH_VARIABLE_PIE, 1) );
            setPieGlyphs(pies);

        }
        else
        {
            if(getTransitionNeutral().isEmpty())
            {
                setPieGlyphs(createPieGlyphs( getGroomedPolygons(), GLYPH_VARIABLE_PIE, 0 ) );
            }
            else
            {
                    QVector<PieChart> pies;
                    pies.append( createPieGlyphs( getTransitionNeutral(), GLYPH_VARIABLE_PIE, 0) );
                    pies.append( createPieGlyphs( getTransitionAdd(), GLYPH_VARIABLE_PIE, 0) );
                    setPieGlyphs(pies);
            }

        }

        calculateValueBounds( getPieGlyphs() );
        changeColorMap(this->CATEGORICAL);
        ColourManager manager(getValueLower(), getValueUpper());
        drawPieGlyphs( getPieGlyphs(), manager);
        drawLegend( manager );
        break;
    }
    case GLYPH_STAR :
    {
        if( getTransitionState() )
        {
            QVector<StarGlyph> stars;
            stars.append( createStarGlyphs( getTransitionNeutral(), 0 ) );
            stars.append( createStarGlyphs( getTransitionRemove(), -1 ) );
            stars.append( createStarGlyphs( getTransitionAdd(), 1 ) );
            setStarGlyphs( stars );
        }
        else
        {
            if( getTransitionNeutral().isEmpty() )
            {
                setStarGlyphs(createStarGlyphs( getGroomedPolygons(), 0 ) );
            }
            else
            {
                QVector<StarGlyph> stars;
                stars.append( createStarGlyphs( getTransitionNeutral(), 0 ) );
                stars.append( createStarGlyphs( getTransitionAdd(), 0 ) );
                setStarGlyphs( stars );
            }
        }

        calculateValueBounds( getStarGlyphs() );
        changeColorMap(this->DIVERGING);
        ColourManager manager(-2, 2);
        drawStarGlyphs( getStarGlyphs(), manager );
        drawLegend( manager );
        break;
    }
    case GLYPH_BAR :
    {
        if( getTransitionState() )
        {
            QVector<BarChart> bars;
            bars.append(createBarCharts(getTransitionNeutral(), 0));
            bars.append(createBarCharts(getTransitionRemove(), -1));
            bars.append(createBarCharts(getTransitionAdd(), 1));
            setBarCharts(bars);
        }
        else if ( getTransitionNeutral().isEmpty() )
        {
            setBarCharts(createBarCharts(getGroomedPolygons(), 0) );
        }
        else
        {
            QVector<BarChart> bars;
            bars.append(createBarCharts(getTransitionNeutral(), 0));
            bars.append(createBarCharts(getTransitionAdd(), 0));
            setBarCharts(bars);
        }
        calculateValueBounds( getBarCharts() );
        changeColorMap(this->CATEGORICAL);
        ColourManager manager(getValueLower(), getValueUpper());
        drawBarCharts( getBarCharts(), manager);
        drawLegend( manager );
        break;
    }
    }

    if( getClickedIndex() > NEGATIVE_INDEX )
    {

        QVector<TreeNode> poly;
        if(getTransitionNeutral().isEmpty())
            poly.append(getGroomedPolygons());
        else
        {
            poly.append(getTransitionNeutral());
            poly.append(getTransitionAdd());
        }
        drawPolygon(poly.at(getClickedIndex()));
    }

    if( debugMousePointer() )
    {
        debugCircle( getMouse().x(),
                     getMouse().y(), Colour("FF0000"), 0.5f);
    }

    qDebug() << "drawn.";
}
void Canvas::calculateAbsoluteValueBounds( QVector<TreeNode> list )
{
    setValueLower(std::numeric_limits<float>::max());
    setValueUpper(-std::numeric_limits<float>::max());

    for(TreeNode p: list)
    {
        for( int i = 0; i < p.getValues().size(); ++i )
        {
            setValueLower( std::min( getValueLower(),
                                     p.getValues().at( i ).toFloat() ) ) ;
            setValueUpper( std::max( getValueUpper(),
                                     p.getValues().at( i ).toFloat() ) ) ;
        }
    }
}

void Canvas::calculateValueBounds( QVector<TreeNode> list )
{
    setValueLower(std::numeric_limits<float>::max());
    setValueUpper(-std::numeric_limits<float>::max());

    for(TreeNode p: list)
    {
        setValueLower( std::min( getValueLower(),
                                 p.getValues().at(VALUE_INDEX).toFloat() /**100*/ ) ) ;
        setValueUpper( std::max( getValueUpper(),
                                 p.getValues().at(VALUE_INDEX).toFloat() /**100*/ ) ) ;
    }
}



void Canvas::calculateValueBounds( QVector<PieChart> list )
{
    setValueLower(std::numeric_limits<float>::max());
    setValueUpper(-std::numeric_limits<float>::max());
    foreach( PieChart p, list )
        foreach( PieSegment ps, p.pieSlices() )
        {
            setValueLower( std::min( getValueLower(),
                                     ps.value() ) );
            setValueUpper( std::max( getValueUpper(),
                                     ps.value() ) );
        }
}

void Canvas::calculateValueBounds( QVector<BarChart> list )
{
    setValueLower(std::numeric_limits<float>::max());
    setValueUpper(-std::numeric_limits<float>::max());
    foreach( BarChart b, list )
        for( int i =0; i < b.values().size(); ++i )
        {
            setValueLower( std::min( getValueLower(),
                                     b.values().at(i) ) );
            setValueUpper( std::max( getValueUpper(),
                                     b.values().at(i) ) );
        }
}

void Canvas::calculateValueBounds( QVector<StarGlyph> list )
{
    setValueLower(std::numeric_limits<float>::max());
    setValueUpper(-std::numeric_limits<float>::max());
    foreach( StarGlyph p, list )
        foreach( float ps, p.points() )
        {
            setValueLower( std::min( getValueLower(),
                                     ps ) );
            setValueUpper( std::max( getValueUpper(),
                                     ps ) );
        }

}

void Canvas::calculateValueBounds( QVector<WheelGlyph> list )
{
    setValueLower(std::numeric_limits<float>::max());
    setValueUpper(-std::numeric_limits<float>::max());
    foreach( WheelGlyph p, list )
        foreach( float ps, p.getRads() )
        {
            setValueLower( std::min( getValueLower(),
                                     ps ) );
            setValueUpper( std::max( getValueUpper(),
                                     ps ) );
        }

}

void Canvas::drawPolygons(QVector<Polygon> list)
{
    for ( int i = 0; i < list.size(); ++i )
    {
        Polygon polygon = list.at( i );
        glLineWidth( 1 );
        glBegin( GL_LINE_STRIP );


        glColor4f( 0, 0, 0, 0.05 );

        for( QVector<QPointF>::const_iterator it =
                    polygon.getPoints().begin();
                it < polygon.getPoints().end(); ++it )
            glVertex2f( it->x(), it->y() );

        glEnd();
    }
}

void Canvas::drawPolygon(TreeNode polygon)
{
    glLineWidth( 3 );
    glBegin( GL_LINE_STRIP );


    glColor4f( 1, 0, 0, 0.5 );

    for( QVector<QPointF>::const_iterator it =
                polygon.getNonSharedBoundary()->getBoundary().begin();
            it < polygon.getNonSharedBoundary()->getBoundary().end(); ++it )
        glVertex2f( it->x(), it->y() );
    for( QVector<QPointF>::const_iterator it =
                polygon.getSharedBoundary()->getBoundary().begin();
            it < polygon.getSharedBoundary()->getBoundary().end(); ++it )
        glVertex2f( it->x(), it->y() );

    glEnd();
}

void Canvas::drawPolygons(QVector<TreeNode> list)
{
    ColourManager cm(getValueLower(),getValueUpper());

    if(getAreaOpacity() > 0.0f)
    {
        for( int i = 0; i < list.size(); ++i )
        {
            TreeNode polygon = list.at( i );
            QVector<QPointF> points = polygon.fullBoundary();
            Colour c = cm.getClassColour(polygon.getValues().at(VALUE_INDEX).toFloat());
            glColor4f( c.getR(), c.getG(), c.getB(), getAreaOpacity() );

            glEnable( GL_STENCIL_TEST );
            glColorMask( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE );
            glStencilOp( GL_KEEP, GL_KEEP, GL_INVERT );
            glStencilFunc( GL_ALWAYS, 0x1, 0x1 );
            glBegin( GL_TRIANGLES );

            for( int j = 1; j < points.size() - 1; ++j )
            {
                glVertex2f( points.at( 0 ).x(), points.at( 0 ).y() );
                glVertex2f( points.at( j ).x(), points.at( j ).y() );
                glVertex2f( points.at( j + 1 ).x(), points.at( j + 1 ).y() );
            }
            glEnd();

            // fill color buffer
            //      glColor3ub( 0, 128, 0 );
            glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );
            glStencilFunc( GL_EQUAL, 0x1, 0x1 );
            glBegin( GL_TRIANGLES );
            for( int j = 1; j < points.size() - 1; ++j )
            {
                glVertex2f( points.at( 0 ).x(), points.at( 0 ).y() );
                glVertex2f( points.at( j ).x(), points.at( j ).y() );
                glVertex2f( points.at( j + 1 ).x(), points.at( j + 1 ).y() );
            }
            glEnd();

            glDisable( GL_STENCIL_TEST );
        }
    }


    for ( int i = 0; i < list.size(); ++i )
    {
        TreeNode polygon = list.at( i );
        glLineWidth( 2 );
        glBegin( GL_LINE_STRIP );

        Colour c = cm.getClassColour(polygon.getValues().at(VALUE_INDEX).toFloat());
        glColor4f( c.darker().getR(), c.darker().getG(), c.darker().getB(), 0.8 );
//        glColor4f( 0, 0, 0, 0.5 );

        for( QVector<QPointF>::const_iterator it =
                    polygon.getNonSharedBoundary()->getBoundary().begin();
                it < polygon.getNonSharedBoundary()->getBoundary().end(); ++it )
            glVertex2f( it->x(), it->y() );
        for( QVector<QPointF>::const_iterator it =
                    polygon.getSharedBoundary()->getBoundary().begin();
                it < polygon.getSharedBoundary()->getBoundary().end(); ++it )
            glVertex2f( it->x(), it->y() );

        glEnd();
    }
}

void Canvas::drawCentroids(QVector<TreeNode> list, ColourManager cm)
{
    Colour col;
    for ( int i = 0; i < list.size(); ++i )
    {
        col = cm.getClassColour( list.at(i).getValues().at(VALUE_INDEX).toFloat()/**100*/ );
        debugCircle( list.at(i).centroid()->x(), list.at(i).centroid()->y(),
                     col, getGlyphSize());

    }
}

QVector<PieChart> Canvas::createPieGlyphs( QVector<TreeNode> list, int pieType,
                                           int state )
{
    QVector<PieChart> pies;

    foreach( TreeNode p, list)
    {
        if(p.getLevel() > -1)
        {
            QStringList values = p.getValues();
            for( int i = 0; i < 4; ++i )
                values.removeFirst();
            PieChart pie( *p.centroid(), p.getLevel(), state, p.getParentCentroid()  );
            if(pieType == GLYPH_EQUAL_PIE)
                pie.setSliceType(PieChart::EQUAL_SLICES);
            else
                pie.setSliceType(PieChart::FULL_SLICES);

            pie.initialize(values);
            pies.append(pie);
        }

    }

    return pies;
}

QVector<StarGlyph> Canvas::createStarGlyphs( QVector<TreeNode> list, int state )
{
    QVector<StarGlyph> stars;
    foreach( TreeNode p, list )
    {
        if(p.getLevel() > -1)
        {
            QStringList values = p.getValues();
            for( int i = 0; i < 4; ++i )
                values.removeFirst();
            StarGlyph star( *p.centroid(), p.getLevel(), state, p.getParentCentroid()  );
            star.initialize(values);
            stars.append(star);
        }
    }

    return stars;
}

QVector<WheelGlyph> Canvas::createWheelGlyphs( QVector<TreeNode> list, int state )
{
    QVector<WheelGlyph> wheels;
    foreach( TreeNode p, list )
    {
        if(p.getLevel() > -1)
        {
            QStringList values = p.getValues();
            for( int i = 0; i < 4; ++i )
                values.removeFirst();
            WheelGlyph w( *p.centroid(), p.getLevel(), state, p.getParentCentroid() );
            w.initialize(values);
            wheels.append(w);
        }
    }

    return wheels;
}

QVector<BarChart> Canvas::createBarCharts(QVector<TreeNode> list, int state)
{
    QVector<BarChart> bars;
    foreach( TreeNode p, list)
    {
        if(p.getLevel() > -1)
        {
            QStringList values = p.getValues();
            for( int i = 0; i < 4; ++i )
                values.removeFirst();
            BarChart bar( *p.centroid(), p.getLevel(), state, p.getParentCentroid()  );
            bar.initialize(values);
            bars.append(bar);
        }
    }

    return bars;
}

void Canvas::drawStarGlyphs( QVector<StarGlyph> list, ColourManager cm)
{
    Colour color;
    changeColorMap(this->CATEGORICAL);
    float transitionMod = 1.0f/12.0f;
    double value, max = getLength() / 70;
    int totalNooks = 7;
    int nook;
    int nookSegment = max / totalNooks;
    double indicate = 0;
    float currentOpacity = 1;

    float x,y;
    for( int i = 0; i < list.size(); ++ i )
    {
        StarGlyph s = list.at(i);
        QPointF currentCentroid;
        float valueRotation = (2*M_PI) / s.points().size();

        double size = getGlyphSize();
        if( s.state() == s.ADD )
        {
//            size = ( getCurrentTransitionSize() );
            currentOpacity = float(getCurrentTransitionSize())*float(transitionMod);
            if(getTransitionType() == TRANSITION_IN)
            {
                currentCentroid = s.centroid();
            }
            else /** getTransitionType() == TRANSITION_OUT */
            {
                currentCentroid.setX(s.parent().x() - ((s.parent().x() - s.centroid().x()) * (getCurrentTransitionSize()*transitionMod)));
                currentCentroid.setY(s.parent().y() - ((s.parent().y() - s.centroid().y()) * (getCurrentTransitionSize()*transitionMod)));
            }
        }
        else if (s.state() == s.REMOVE )
        {
//            size = ( getGlyphSize() ) - (getCurrentTransitionSize()*1.5);
            currentOpacity = 1.0f-float(getCurrentTransitionSize()*transitionMod);
            if(getTransitionType() == TRANSITION_IN)
            {
                currentCentroid.setX(s.centroid().x() + (s.parent().x() - s.centroid().x()) * (getCurrentTransitionSize()*transitionMod));
                currentCentroid.setY(s.centroid().y() + (s.parent().y() - s.centroid().y()) * (getCurrentTransitionSize()*transitionMod));
            }
            else /** getTransitionType() == TRANSITION_OUT */
            {
                currentCentroid = s.centroid();
            }
        }
        else /** if p.state() == p.NEUTRAL */
        {
//            size = (getGlyphSize());
            currentCentroid = s.centroid();
            currentOpacity=1;
        }

        /** Outline (Standard) */
        if( getHiddenIndicator() == HIDDEN_OUTLINE ||
                getHiddenIndicator() == HIDDEN_SIZE ||
                getHiddenIndicator() == HIDDEN_SIZEOUTLINE )
        {
            if(getHiddenIndicator() == HIDDEN_OUTLINE ||
                    getHiddenIndicator() == HIDDEN_SIZE )
            {
                indicate = 1+s.size();

            }
            else if( getHiddenIndicator() == HIDDEN_SIZEOUTLINE )
            {
                indicate = (1+s.size())*1.5;
            }
            glColor4f( 0.105882353, 0.105882353, 0.105882353, currentOpacity);
            glBegin( GL_TRIANGLE_FAN );
            glVertex2f( currentCentroid.x(), currentCentroid.y() );
            for( float j = 0; j < s.points().size(); ++j )
            {
                value = (s.points().at(j) - getMins().at(j)) /
                        (getMaxes().at(j) - getMins().at(j) );

                qDebug() << value << getMins().at(j) << getMaxes().at(j);
                if(value < 0.125)
                    value = 0.125;
                x = (currentCentroid.x() + sin( valueRotation * j ) *
                         max * value * size * indicate) ;
                y = (currentCentroid.y() + cos( valueRotation * j ) *
                         max * value * size * indicate ) ;
                glVertex2f( x, y );
            }
            value = (s.points().at(0) - getMins().at(0)) /
                    (getMaxes().at(0) - getMins().at(0) );
            if(value < 0.125)
                value = 0.125;
            x = (currentCentroid.x() + sin( 0 ) *
                     max * value * size * indicate);
            y = (currentCentroid.y() + cos( 0 ) *
                     max * value * size * indicate);
            glVertex2f( x, y );

            glEnd();
        }
        else /** Halos */
        {
            glColor4f( 0.105882353, 0.105882353, 0.105882353, currentOpacity);
            glLineWidth(2);
            int rings = floor(s.size() / ((s.SIZE_MODIFIER) * 4) );
            for( int k = 1; k <= rings; ++k )
            {
                glBegin( GL_TRIANGLE_FAN );
                glVertex2f( currentCentroid.x(), currentCentroid.y() );
                for( float j = 0; j < s.points().size(); ++j )
                {
                    nook = cm.getClassColourIndex(s.points().at(j))/2;
                    x = currentCentroid.x() + sin( valueRotation * j ) *
                            ( size  * (1+k*s.SIZE_MODIFIER*rings) * ( nookSegment * ( 1+nook ) ) );
                    y = currentCentroid.y() + cos( valueRotation * j ) *
                            ( size  * (1+k*s.SIZE_MODIFIER*rings) * ( nookSegment * ( 1+nook ) ) );
                    glVertex2f( x, y );
                }
                nook = cm.getClassColourIndex(s.points().at(0))/2;
                x = currentCentroid.x() + sin( 0 ) *
                        ( size  * (1+k*s.SIZE_MODIFIER*rings) * ( nookSegment * ( 1+nook ) ) );
                y = currentCentroid.y() + cos( 0 ) *
                        ( size  * (1+k*s.SIZE_MODIFIER*rings) * ( nookSegment * ( 1+nook ) ) );
                glVertex2f( x, y );
                glEnd();
            }
            glLineWidth(1);
        }

        indicate = 1;
        if( getHiddenIndicator() == HIDDEN_SIZE ||
                getHiddenIndicator() == HIDDEN_SIZEOUTLINE )
        {
            indicate = 1+s.size();
        }
        glColor4f( 0.8, 0.8, 0.8, currentOpacity );

        //Fill
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f( currentCentroid.x(), currentCentroid.y() );
        for( float j = 0; j < s.points().size(); ++j )
        {
            value = (s.points().at(j) - getMins().at(j)) /
                    (getMaxes().at(j) - getMins().at(j) );
            if(value < 0.125)
                value = 0.125;
            x = currentCentroid.x() + sin( valueRotation * j ) *
                     max * value * size * indicate ;
            y = currentCentroid.y() + cos( valueRotation * j ) *
                     max * value * size * indicate ;
            glVertex2f( x, y );
        }
        value = (s.points().at(0) - getMins().at(0)) /
                (getMaxes().at(0) - getMins().at(0) );
        if(value < 0.125)
            value = 0.125;
        x = currentCentroid.x() + sin( 0 ) *
                 max * value * size * indicate ;
        y = currentCentroid.y() + cos( 0 ) *
                 max * value * size * indicate ;
        glVertex2f( x, y );

        glEnd();

        glColor4f( 0.105882353, 0.105882353, 0.105882353, currentOpacity);

        //Lines at Points
        for( float j = 0; j < s.points().size(); ++j )
        {
            if( getColorStarLines() )
            {
                color = cm.getColourFromIndex(j);
                glColor4f(color.getR(),color.getG(),color.getB(),currentOpacity);
            }
            else
                glColor4f( 0.105882353, 0.105882353, 0.105882353, currentOpacity);

            glBegin( GL_LINES );
            value = (s.points().at(j) - getMins().at(j)) /
                    (getMaxes().at(j) - getMins().at(j) );
            if(value <= 0.125)
                value = 0.125;
            x = currentCentroid.x() + sin( valueRotation * j ) *
                     max * value * size * indicate ;
            y = currentCentroid.y() + cos( valueRotation * j ) *
                     max * value * size * indicate ;
            glVertex2f(currentCentroid.x(), currentCentroid.y());
            glVertex2f( x, y );
            glEnd();
        }
        glEnd();

//        //Standard
//        glColor4f( 1, 0.105882353, 0.105882353, 0.3);
//        glBegin( GL_LINE_STRIP );
////        glVertex2f( currentCentroid.x(), currentCentroid.y() );
//        for( float j = 0; j < s.points().size(); ++j )
//        {
//            nook = cm.getClassColourIndex(0)/2;
//            x = currentCentroid.x() + sin( valueRotation * j ) *
//                    ( size  * ( nookSegment * ( 1+nook ) ) );
//            y = currentCentroid.y() + cos( valueRotation * j ) *
//                    ( size  * ( nookSegment * ( 1+nook ) ) );
//            glVertex2f( x, y );
//        }
//        nook = cm.getClassColourIndex(0)/2;
//        x = currentCentroid.x() + sin( 0 ) *
//                    ( size  * indicate * ( nookSegment * ( 1+nook ) ) );
//        y = currentCentroid.y() + cos( 0 ) *
//                    ( size  * indicate * ( nookSegment * ( 1+nook ) ) );
//        glVertex2f( x, y );

        glEnd();
    }
}

void Canvas::drawWheelGlyphs( QVector<WheelGlyph> list, ColourManager cm)
{
    float transitionMod = 1.0f/12.0f;
    Colour color;
    changeColorMap(this->CATEGORICAL);
    double value, max = getLength() / 70;
    double indicate = 1;
    float currentOpacity = 1;
    double size= getGlyphSize();

    float x,y;
    for( int i = 0; i < list.size(); ++ i )
    {

        WheelGlyph s = list.at(i);
        QPointF currentCentroid;

        if( s.state() == s.ADD )
        {
//            size = (getCurrentTransitionSize());
            currentOpacity = float(getCurrentTransitionSize())*float(transitionMod);
            if(getTransitionType() == TRANSITION_IN)
            {
                currentCentroid = s.centroid();
            }
            else /** getTransitionType() == TRANSITION_OUT */
            {
                currentCentroid.setX(s.parent().x() - ((s.parent().x() - s.centroid().x()) * (getCurrentTransitionSize()*transitionMod)));
                currentCentroid.setY(s.parent().y() - ((s.parent().y() - s.centroid().y()) * (getCurrentTransitionSize()*transitionMod)));
            }
        }
        else if (s.state() == s.REMOVE )
        {
//            size = (getGlyphSize()) - (getCurrentTransitionSize()*1.5);
            currentOpacity = 1.0f-float(getCurrentTransitionSize()*transitionMod);
            if(getTransitionType() == TRANSITION_IN)
            {
                currentCentroid.setX(s.centroid().x() + ((s.parent().x() - s.centroid().x()) * (getCurrentTransitionSize()*transitionMod)));
                currentCentroid.setY(s.centroid().y() + ((s.parent().y() - s.centroid().y()) * (getCurrentTransitionSize()*transitionMod)));
            }
            else /** getTransitionType() == TRANSITION_OUT */
            {
                currentCentroid = s.centroid();
            }
        }
        else /** if p.state() == p.NEUTRAL */
        {
//            size = (getGlyphSize());
            currentCentroid = s.centroid();
            currentOpacity = 1.0f;
        }

        int sliceNo = -1;
        float valueRotation = (2*M_PI) / s.getRads().size();
        //Outlines
        /** Outline (Standard) */
        if( getHiddenIndicator() == HIDDEN_OUTLINE ||
                getHiddenIndicator() == HIDDEN_SIZE ||
                getHiddenIndicator() == HIDDEN_SIZEOUTLINE )
        {
            if(getHiddenIndicator() == HIDDEN_OUTLINE ||
                    getHiddenIndicator() == HIDDEN_SIZE )
            {
                indicate = 1+s.size();
            }
            else if( getHiddenIndicator() == HIDDEN_SIZEOUTLINE )
            {
                indicate = (1+s.size())*1.5;
            }
            glColor4f(0.105882353, 0.105882353, 0.105882353, currentOpacity);
            glBegin( GL_TRIANGLE_FAN );
            for( float angle = 0; angle <= 2*M_PI; angle += 0.01 )
            {
                if(sliceNo < s.getRads().size()-1 &&
                        int(angle*100) % int(roundf(valueRotation)*100) == 0)
                {
                    glVertex2f( currentCentroid.x(), currentCentroid.y() );
                    glEnd();
                    sliceNo++;
                    glBegin(GL_TRIANGLE_FAN);
                    glVertex2f( currentCentroid.x(), currentCentroid.y() );
                }
                value = ( s.getRads().at(sliceNo) - getMins().at(sliceNo) ) /
                        ( getMaxes().at(sliceNo) - getMins().at(sliceNo) );
                x = currentCentroid.x() + sin( angle ) *
                        max  * value * size * indicate;
                y = currentCentroid.y() + cos( angle ) *
                        max  * value * size * indicate;
                glVertex2f( x, y );
            }
            x = currentCentroid.x() + sin( 0 ) *
                    max  * value * size * indicate;
            y = currentCentroid.y() + cos( 0 ) *
                    max  * value * size * indicate;
            glVertex2f(x,y);
            glVertex2f( currentCentroid.x(), currentCentroid.y() );
            glEnd();
        }

        indicate = 1;
        if( getHiddenIndicator() == HIDDEN_SIZE ||
                getHiddenIndicator() == HIDDEN_SIZEOUTLINE )
        {
            indicate = 1+s.size();
        }
        glLineWidth(1);
        //Fill
        sliceNo = -1;
        for( float angle = 0; angle < 2*M_PI; angle += 0.01 )
        {
            if(sliceNo < s.getRads().size()-1 &&
                    int(angle*100) % int(roundf(valueRotation)*100) == 0)
            {
                glVertex2f( currentCentroid.x(), currentCentroid.y() );
                glEnd();
                sliceNo++;
                glBegin(GL_TRIANGLE_FAN);
                color = cm.getColourFromIndex(sliceNo);
                glColor3f(color.getR(), color.getG(), color.getB() );
                glVertex2f( currentCentroid.x(), currentCentroid.y() );
            }
            value = ( s.getRads().at(sliceNo) - getMins().at(sliceNo) ) /
                    ( getMaxes().at(sliceNo) - getMins().at(sliceNo) ) ;
            color = cm.getColourFromIndex(sliceNo);
            glColor4f(color.getR(), color.getG(), color.getB(), currentOpacity );
            x = currentCentroid.x() + sin( angle ) *
                     max  * value * size * indicate;
            y = currentCentroid.y() + cos( angle ) *
                     max  * value * size * indicate;
            glVertex2f( x, y );
        }
        x = currentCentroid.x() + sin( 0 ) *
                max  * value * size * indicate;
        y = currentCentroid.y() + cos( 0 ) *
               max  * value * size * indicate;
        glVertex2f(x,y);
        glVertex2f( currentCentroid.x(), currentCentroid.y() );

        glEnd();

        sliceNo = -1;
        glLineWidth(1);
        glColor4f(0.105882353, 0.105882353, 0.105882353, currentOpacity);
        glBegin( GL_LINE_STRIP );
        for( float angle = 0; angle <= 2*M_PI; angle += 0.01 )
        {
            if(sliceNo < s.getRads().size()-1 &&
                    int(angle*100) % int(roundf(valueRotation)*100) == 0)
            {
                glVertex2f( currentCentroid.x(), currentCentroid.y() );
                glEnd();
                sliceNo++;
                glBegin(GL_LINE_STRIP);
                glVertex2f( currentCentroid.x(), currentCentroid.y() );
            }
            value = ( s.getRads().at(sliceNo) - getMins().at(sliceNo) ) /
                    ( getMaxes().at(sliceNo) - getMins().at(sliceNo) );
            x = currentCentroid.x() + sin( angle ) *
                    max  * value * size * indicate;
            y = currentCentroid.y() + cos( angle ) *
                    max  * value * size * indicate;
            glVertex2f( x, y );
        }
        x = currentCentroid.x() + sin( 0 ) *
                max  * value * size * indicate;
        y = currentCentroid.y() + cos( 0 ) *
                max  * value * size * indicate;
        glVertex2f(x,y);
        glVertex2f( currentCentroid.x(), currentCentroid.y() );
        glEnd();
    }



    return;
}



void Canvas::drawPieGlyphs( QVector<PieChart> list, ColourManager cm)
{
    Colour color;
    double transitionMod = 1.0f/12.0f;
    float currentOpacity = 1;

    for( int j = 0; j < list.size(); ++j )
    {
        PieChart p = list.at(j);
        double indicate = 1;
        double size = getGlyphSize();
        double rad = getLength() / 100;
        QPointF currentCentroid;


        if( p.state() == p.ADD )
        {
//            size = getCurrentTransitionSize();
            currentOpacity = float(getCurrentTransitionSize())*float(transitionMod);
            if(getTransitionType() == TRANSITION_IN)
            {
                currentCentroid = p.centroid();
            }
            else /** getTransitionType() == TRANSITION_OUT */
            {
                currentCentroid.setX(p.parent().x() - ((p.parent().x() - p.centroid().x()) * (getCurrentTransitionSize()*transitionMod)));
                currentCentroid.setY(p.parent().y() - ((p.parent().y() - p.centroid().y()) * (getCurrentTransitionSize()*transitionMod)));
            }
        }
        else if (p.state() == p.REMOVE )
        {
//            size = getGlyphSize() - getCurrentTransitionSize();
            currentOpacity = 1-(float(getCurrentTransitionSize())*float(transitionMod));
            if(getTransitionType() == TRANSITION_IN)
            {
                currentCentroid.setX(p.centroid().x() + (p.parent().x() - p.centroid().x()) * (getCurrentTransitionSize()*transitionMod));
                currentCentroid.setY(p.centroid().y() + (p.parent().y() - p.centroid().y()) * (getCurrentTransitionSize()*transitionMod));
            }
            else /** getTransitionType() == TRANSITION_OUT */
            {
                currentCentroid = p.centroid();
            }
        }
        else /** if p.state() == p.NEUTRAL */
        {
//            size = getGlyphSize();
            currentCentroid = p.centroid();
            currentOpacity=1;
        }

//        Colour c = outline.getInterpolatedColour(j);
        if(getHiddenIndicator() == HIDDEN_OUTLINE ||
                getHiddenIndicator() == HIDDEN_SIZE ||
                getHiddenIndicator() == HIDDEN_SIZEOUTLINE )
        {
            /* Outline (STANDARD) */
            glColor4f( 0.105882353, 0.105882353, 0.105882353, currentOpacity );
            glBegin( GL_TRIANGLE_FAN );
            glVertex2f( currentCentroid.x(), currentCentroid.y() );
            if(getHiddenIndicator() == HIDDEN_OUTLINE ||
                    getHiddenIndicator() == HIDDEN_SIZE )
            {
                indicate = 1+p.size();
            }
            else if( getHiddenIndicator() == HIDDEN_SIZEOUTLINE )
            {
                indicate = (1+p.size())*1.5;
            }
            for ( float angle = 0; angle <= (2*M_PI); angle += 0.01 )
            {
                float x = currentCentroid.x() + sin( angle ) *
                          ( size * ( ( rad * indicate  ) ) );

                float y = currentCentroid.y() + cos( angle ) *
                          ( size * ( ( rad * indicate ) ) );

                glVertex2f( x, y );
            }
            float x = currentCentroid.x() + sin( 0 ) *
                      ( size * ( ( rad * indicate  ) ) );

            float y = currentCentroid.y() + cos( 0 ) *
                      ( size * ( ( rad * indicate ) ) );

            glVertex2f( x, y );
            glEnd();
        }
        else
        {
            /* Outline (STEPS) */
            glColor4f( 0.105882353, 0.105882353, 0.105882353, 0.2 );
            glLineWidth(3);
            int rings = floor(p.size() / ((p.SIZE_MODIFIER)* 4) );
            for ( int i = 1; i <= rings; ++i )
            {
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(currentCentroid.x(),currentCentroid.y());
                for ( float angle = 0; angle <= (2*M_PI); angle += 0.1 )
                {
                    float x = currentCentroid.x() + sin( angle ) *
                            ( size * ( rad * ( 1 + (i*p.SIZE_MODIFIER*rings) ) ) );
                    float y = currentCentroid.y() + cos( angle ) *
                            ( size * ( rad * ( 1 + (i*p.SIZE_MODIFIER*rings) ) ) );
                    glVertex3f( x, y, 0.5 );
                }

                float x = currentCentroid.x() + sin( 0 ) *
                        ( size * ( rad * ( 1 + (i*p.SIZE_MODIFIER*5) ) ) );
                float y = currentCentroid.y() + cos( 0 ) *
                        ( size * ( rad * ( 1 + (i*p.SIZE_MODIFIER*5) ) ) );
                glVertex3f( x, y, 0.5 );
                glEnd();

//                /* Outline (RING) */
//                glColor4f( 0.105882353, 0.105882353, 0.105882353, 0.8 );
//                glLineWidth(3);
//                int rings = floor(p.size() / ((p.SIZE_MODIFIER)* 2) );
//                for ( int i = 1; i <= rings; ++i )
//                {
//                    glBegin(GL_LINE_STRIP);
//                    for ( float angle = 0; angle <= (2*M_PI); angle += 0.1 )
//                    {
//                        float x = currentCentroid.x() + sin( angle ) *
//                                ( size * ( rad * ( 1 + (i*p.SIZE_MODIFIER*5) ) ) );
//                        float y = currentCentroid.y() + cos( angle ) *
//                                ( size * ( rad * ( 1 + (i*p.SIZE_MODIFIER*5) ) ) );
//                        glVertex3f( x, y, 0.5 );
//                    }

//                    float x = currentCentroid.x() + sin( 0 ) *
//                            ( size * ( rad * ( 1 + (i*p.SIZE_MODIFIER*5) ) ) );
//                    float y = currentCentroid.y() + cos( 0 ) *
//                            ( size * ( rad * ( 1 + (i*p.SIZE_MODIFIER*5) ) ) );
//                    glVertex3f( x, y, 0.5 );
//                    glEnd();
            }
        }
        glLineWidth(1);


        indicate = 1;
        if( getHiddenIndicator() == HIDDEN_SIZE ||
                getHiddenIndicator() == HIDDEN_SIZEOUTLINE )
        {
            indicate = 1+p.size();
        }
        changeColorMap(this->CATEGORICAL);
        float currentAngle = 0;
//        color = Colour(1,0,0,1,"");
        for( int i = 0; i < p.pieSlices().size(); ++i )
        {
            PieSegment ps = p.pieSlices().at(i);
            if(getGlyphType() == GLYPH_EQUAL_PIE)
                color = cm.getInterpolatedColour( ps.value() );
            else if(getGlyphType() == GLYPH_VARIABLE_PIE)
                color = cm.getColourFromIndex(i);
            /* Fill */
            glColor4f( color.getR(), color.getG(), color.getB(), currentOpacity );
            glBegin( GL_TRIANGLE_FAN );
            glVertex2f( currentCentroid.x(), currentCentroid.y() );

            for( float angle = currentAngle; angle <=
                 currentAngle+ps.angle()+0.05; angle+=0.1 )
            {
                float x = currentCentroid.x() + sin( angle ) *
                          ( size * ( ( rad * indicate  ) ) );

                float y = currentCentroid.y() + cos( angle ) *
                          ( size * ( ( rad * indicate ) ) );
                glVertex3f( x, y, 0.5 );
            }
            glVertex2f( currentCentroid.x(), currentCentroid.y() );
            glEnd();
            currentAngle += ps.angle();
//            color = cm.getColourFromSeed(int(currentAngle));
        }
        for( int i = 0; i < p.pieSlices().size(); ++i )
        {
            PieSegment ps = p.pieSlices().at(i);
            glColor4f( 0.105882353, 0.105882353, 0.105882353, currentOpacity );
            glBegin( GL_LINE_STRIP );
            glVertex2f( currentCentroid.x(), currentCentroid.y() );

            for( float angle = currentAngle; angle <=
                 currentAngle+ps.angle()+0.05; angle+=0.1 )
            {
                float x = currentCentroid.x() + sin( angle ) *
                          ( size * ( ( rad * ( indicate )) ) );

                float y = currentCentroid.y() + cos( angle ) *
                          ( size * ( ( rad * ( indicate )) ) );
                glVertex3f( x, y, 0.5 );
            }
            glVertex2f( currentCentroid.x(), currentCentroid.y() );
            glEnd();
            currentAngle += ps.angle();
        }
    }
    return;
}

void Canvas::drawBarCharts(QVector<BarChart> list, ColourManager cm)
{
    double movingTransition = 2.4 /*25/getGlyphSize()*/;
    Colour color;
    changeColorMap(this->CATEGORICAL);
    double max = getLength() / 50;
    int bars = list.first().values().size();
    double indicateNeg = 1, indicatePos = 1;
    float minX, width, minY, height;
    float value;


    for( int i = 0; i < list.size(); ++ i )
    {

        BarChart b = list.at(i);
        QPointF currentCentroid;
        glColor4f( 0.8, 0.8, 0.8, 1 );

//        glVertex2f( s.centroid().x(), s.centroid().y() );

        double size;
        if( b.state() == b.ADD )
        {
            size = (getCurrentTransitionSize()*1.5);
            if(getTransitionType() == TRANSITION_IN)
            {
                currentCentroid = b.centroid();
            }
            else /** getTransitionType() == TRANSITION_OUT */
            {
                currentCentroid.setX(b.parent().x() - ((b.parent().x() - b.centroid().x()) * (getCurrentTransitionSize()/movingTransition)));
                currentCentroid.setY(b.parent().y() - ((b.parent().y() - b.centroid().y()) * (getCurrentTransitionSize()/movingTransition)));
            }
        }
        else if (b.state() == b.REMOVE )
        {
            size = (getGlyphSize()*1.5) - (getCurrentTransitionSize()*1.5);
            if(getTransitionType() == TRANSITION_IN)
            {
                currentCentroid.setX(b.centroid().x() + (b.parent().x() - b.centroid().x()) * (getCurrentTransitionSize()/movingTransition));
                currentCentroid.setY(b.centroid().y() + (b.parent().y() - b.centroid().y()) * (getCurrentTransitionSize()/movingTransition));
            }
            else /** getTransitionType() == TRANSITION_OUT */
            {
                currentCentroid = b.centroid();
            }
        }
        else /** if b.state() == b.NEUTRAL */
        {
            size = (getGlyphSize()*1.5);
            currentCentroid = b.centroid();
        }

        int barWidth = (max / bars) * (size * 0.4);


        //Outlines
        if( getHiddenIndicator() == HIDDEN_OUTLINE ||
                getHiddenIndicator() == HIDDEN_SIZE ||
                getHiddenIndicator() == HIDDEN_SIZEOUTLINE )
        {
            if(getHiddenIndicator() == HIDDEN_OUTLINE ||
                    getHiddenIndicator() == HIDDEN_SIZE )
            {
                indicatePos = 1+b.size();
                indicateNeg = 1-b.size();
            }
            else if( getHiddenIndicator() == HIDDEN_SIZEOUTLINE )
            {
                indicatePos = (1+b.size())*1.5;
                indicateNeg = (1-b.size())*1.5;
            }
            barWidth = (max / bars) * (size * 0.4) * indicatePos;
            glColor4f( 0.105882353, 0.105882353, 0.105882353, 0.8);
            for( int j = 0; j < bars; ++j )
            {
                value = ( (b.values().at(j)-getMins().at(j)) /
                                (getMaxes().at(j)-getMins().at(j)) );
                if( value < 0.1)
                    value = 0.1;

                minX = ( currentCentroid.x() - ((max/5) * size) ) + (barWidth*j);
                width = barWidth;
                minY = currentCentroid.y();
                height = value  * (max *size) * indicatePos;

                glBegin( GL_QUADS );
                glVertex2f(minX, minY);
                glVertex2f(minX, minY+height);
                glVertex2f(minX+width, minY+height);
                glVertex2f(minX+width,minY);
                glEnd();
            }
        }

        indicatePos = 1;
        indicateNeg = 1;
        if( getHiddenIndicator() == HIDDEN_SIZE ||
                getHiddenIndicator() == HIDDEN_SIZEOUTLINE )
        {
            indicatePos = 1+b.size();
            indicateNeg = 1-b.size();
            barWidth = (max / bars) * (size * 0.4);
        }
        //Fill
        for( int j = 0; j < bars; ++j )
        {
            value = ( (b.values().at(j)-getMins().at(j)) /
                            (getMaxes().at(j)-getMins().at(j)) );
            if( value < 0.1)
                value = 0.1;

            minX = ( currentCentroid.x() - ((max/5) * size) ) + (barWidth*j);
            width = barWidth *indicatePos;
            minY =  currentCentroid.y();
            height = value * (max *size) * indicatePos;
            color = cm.getColourFromIndex(j);
            glColor3f(color.getR(), color.getG(), color.getB());

            glBegin( GL_QUADS );
            glVertex2f(minX, minY);
            glVertex2f(minX, minY+height);
            glVertex2f(minX+width, minY+height);
            glVertex2f(minX+width,minY);
            glEnd();
        }



//        // Extents
//        glColor4f( 0.105882353, 0.105882353, 0.105882353, 0.2);
//        minX = ( b.centroid().x() - ((max/4) * size) );
//        minY = ( b.centroid().y() - ((max/4) * size) );
//        int maxX = ( b.centroid().x() - ((max/4) * size) ) + (barWidth*bars);
//        int maxY = minY + (max*size);

//        glBegin( GL_LINE_STRIP );
//        glVertex2f(minX, minY);
//        glVertex2f(minX, maxY);
//        glVertex2f(maxX, maxY);
//        glVertex2f(maxX,minY);
//        glEnd();
    }

    return;
}


void Canvas::drawLegend( ColourManager cm )
{
//    double scaleModifier = getLength() / 20;
    QPointF legendBL, legendBR, legendTL, legendTR;
    legendBL.setX( getCurrentWrapper().minimums.at(AABB::XDIM) - scaleModifier()/1.4);
    legendBL.setY( getCurrentWrapper().maximums.at(AABB::YDIM) + scaleModifier()/2.8);

    legendTL.setX( getCurrentWrapper().minimums.at(AABB::XDIM) - scaleModifier()/1.4);
    legendTL.setY( getCurrentWrapper().maximums.at(AABB::YDIM) + (scaleModifier()/1.4));

    legendBR.setX( getCurrentWrapper().minimums.at(AABB::XDIM) + scaleModifier()*5 );
    legendBR.setY( getCurrentWrapper().maximums.at(AABB::YDIM) + scaleModifier()/2.8);

    legendTR.setX( getCurrentWrapper().minimums.at(AABB::XDIM) + scaleModifier()*5);
    legendTR.setY( getCurrentWrapper().maximums.at(AABB::YDIM) + (scaleModifier()/1.4));

    double lRange = legendTR.x() - legendTL.x();
    double colorRange = cm.getUpperRange() - cm.getLowerRange();
    double slices = cm.getCurrentColourMap().getColourList().size();
    double canvasSlice = ( lRange / slices );
    double colourSlice = colorRange / slices;

    double sliceCenter = colourSlice / 2;
    glLineWidth( 20 );

    glBegin( GL_QUADS );

    for ( int i = 0; i < slices; ++i )
    {
        Colour color = cm.getClassColour(
                              cm.getLowerRange() + ( colourSlice * i ) + sliceCenter );
        glColor4f( color.getR(), color.getG(),
                   color.getB(), 1 );

        glVertex2f( legendBL.x()  + ( canvasSlice * ( i + 1.0 ) ) ,
                    legendBL.y() );
        glVertex2f( legendTL.x()  + ( canvasSlice * ( i + 1.0 ) ),
                    legendTL.y() );
        glVertex2f( legendTL.x()  + ( canvasSlice * ( i + 2.0 ) ) ,
                    legendTL.y());
        glVertex2f( legendBL.x() + ( canvasSlice * ( i + 2.0 ) ),
                    legendBL.y() );
    }

    glEnd();
    glColor4f( 0.0f, 0.0f, 0.0f, 1.0f );
    std::string upper = QString::number( cm.getUpperRange(), 'f',
                                         1 ).toUtf8().constData();
    std::string lower = QString::number( cm.getLowerRange(), 'f',
                                         1 ).toUtf8().constData();

    glPrintString( getCurrentWrapper().minimums.at(AABB::XDIM) - (scaleModifier()/10),
                   legendBR.y() - (scaleModifier()/2.8) , lower );
    glPrintString( getCurrentWrapper().minimums.at(AABB::XDIM) + (scaleModifier()*5.1) ,
                   legendBR.y()- (scaleModifier()/2.8) , upper ) ;

    return;
}

bool Canvas:: debugCircle( double centerX, double centerY,
                           Colour color, double size )
{
    /* Outline */
    glColor4f( 0, 0, 0, 1 );
    glBegin( GL_TRIANGLE_FAN );
    glVertex2f( centerX, centerY );
    //double size = 1;
    double rad = getLength() /*+ scaleModifier()*/ / 100;

    for ( float angle = 1.0f; angle < 361.0f; angle += 0.2 )
    {
        float x = centerX + sin( angle ) *
                  ( size * ( rad ) );

        float y = centerY + cos( angle ) *
                  ( size * ( rad ) );

        glVertex3f( x, y, 0.5 );
    }
    glEnd();
    /* Fill */
    glColor4f( color.getR(), color.getG(), color.getB(), 0.25 );
    glBegin( GL_TRIANGLE_FAN );
    glVertex2f( centerX, centerY );

    for ( float angle = 1.0f; angle < 361.0f; angle += 0.2 )
    {
        float x = centerX + sin( angle ) *
                  ( size * ( ( rad * 0.9 ) ) );

        float y = centerY + cos( angle ) *
                  ( size * ( ( rad * 0.9 ) ) );
        glVertex3f( x, y, 0.5 );
    }

    glEnd();
    return true;
}

void Canvas::glPrintString( float x, float y, std::string str )
{
    glRasterPos2f( x, y );

    glPrintString( GLUT_BITMAP_HELVETICA_12, str.c_str() );
}

void Canvas::glPrintString( void* font, const char* str )
{
    int len, i;

    len = ( int )strlen( str );

    for ( i = 0; i < len; i++ )
        glutBitmapCharacter( font, str[i] );

    glEnd();
}

void Canvas::resizeGL( int w, int h )
{
    //qDebug() <<w<<h; //Remove warnings
    update();
}

QVector<Polygon> Canvas::loadedPolygons() const
{
    return m_loadedPolygons;
}

void Canvas::setLoadedPolygons(const QVector<Polygon> &loadedPolygons)
{
    m_loadedPolygons = loadedPolygons;
}

void Canvas::setDefaultOrtho(OGREnvelope wrapper)
{
    setOriginalWrapper( AABB( wrapper.MinX,wrapper.MaxX,
                                  wrapper.MinY,wrapper.MaxY ) );
}

AABB Canvas::getOriginalWrapper() const
{
    return m_originalWrapper;
}

void Canvas::setOriginalWrapper(const AABB &value)
{
    m_originalWrapper = value;
}

float Canvas::getLength() const
{
    return length;
}

void Canvas::setLength(float value)
{
    length = value;
}

float Canvas::getValueUpper() const
{
    return valueUpper;
}

void Canvas::setValueUpper(float value)
{
    valueUpper = value;
}

float Canvas::getValueLower() const
{
    return valueLower;
}

void Canvas::setValueLower(float value)
{
    valueLower = value;
}

QVector<PieChart> Canvas::getPieGlyphs() const
{
    return m_pieGlyphs;
}

void Canvas::setPieGlyphs(const QVector<PieChart> &pieGlyphs)
{
    m_pieGlyphs = pieGlyphs;
}

int Canvas::getGlyphType() const
{
    return glyphType;
}

void Canvas::setGlyphType(int value)
{
    glyphType = value;
}

/**
 * @brief Canvas::prepareDraw called before window is redrawn.
 */
void Canvas::prepareDraw()
{
    glPointSize( 1 );
    setOrtho( );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    return;
}

void Canvas::setOrtho()
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glClearColor( 1,
                  1,
                  1, 1.0 );

    setLength( std::max( getOriginalWrapper().length( AABB::XDIM ),
                         getOriginalWrapper().length( AABB::YDIM ) ) );

    double currentScale = ( getZoom() * getLength() ) / 2;

    setCurrentWrapper( AABB(getOriginalWrapper().minimums.at(AABB::XDIM) + currentScale - scaleModifier(),
                            getOriginalWrapper().minimums.at(AABB::XDIM)+ getLength() - currentScale + scaleModifier(),
                            getOriginalWrapper().minimums.at(AABB::YDIM) + currentScale - scaleModifier(),
                            getOriginalWrapper().minimums.at(AABB::YDIM) + getLength() - currentScale + scaleModifier()));

    glOrtho( getOriginalWrapper().minimums.at(AABB::XDIM) + currentScale - scaleModifier(),
             getOriginalWrapper().minimums.at(AABB::XDIM)+ getLength() - currentScale + scaleModifier(),
             getOriginalWrapper().minimums.at(AABB::YDIM) + currentScale - scaleModifier(),
             getOriginalWrapper().minimums.at(AABB::YDIM) + getLength() - currentScale + scaleModifier(),
             -1.0, 1.0 );

    setLength( getCurrentWrapper().length( AABB::XDIM )) ;
    glClear( GL_COLOR_BUFFER_BIT );
    return;
}

float Canvas::scaleModifier()
{
    return getLength() * 0.05;
}
