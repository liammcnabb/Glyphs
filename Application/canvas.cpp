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

    setClickedIndex(findClickedIndex(getMouse(), getPieGlyphs()));
//    qDebug() << getClickedIndex();
//    if(debugMousePointer() || getClickedIndex() > NEGATIVE_INDEX )
    fillToolTip(getClickedIndex());

        update();



}

float Canvas::convertedX( float windowX )
{
    float newX;
    newX = (getWrapper().minimums.at(AABB::XDIM) - scaleModifier()) +
            ( ( windowX / this->width() ) *
              ( getLength() + (scaleModifier()*2) ) ) ;
    return newX;
}

float Canvas::convertedY( float windowY )
{
    float newY,reverseY;
    reverseY = -( windowY - 1 - this->height() );

    newY = (getWrapper().minimums.at(AABB::YDIM) - scaleModifier()) +
            ( ( reverseY / this->height() ) *
              ( getLength() + (scaleModifier()*2) ) );
    return newY;
}

int Canvas::findClickedIndex(QPointF coords, QVector<PieChart> list )
{
    for(int i = 0; i < list.size(); i++)
    {
        QPointF c = list.at(i).centroid();
        if( IntersectTester::isIntersecting( Point( coords.x(),coords.y() ),
                                  Circle( Point( c.x(),c.y() ),
                                  ( getLength() / 100 ) * getGlyphSize() ) ) )
            return i;
    }

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

void Canvas::paintGL()
{
    if(getGroomedPolygons().size() > 0)
        redraw();

}

void Canvas::redraw()
{
    qDebug() << "drawing";
    prepareDraw();
    
    drawPolygons( loadedPolygons() );
    drawPolygons( getGroomedPolygons() );
    
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
        createPieGlyphs( getGroomedPolygons(), GLYPH_EQUAL_PIE );
        calculateValueBounds( getPieGlyphs() );
        changeColorMap(this->DIVERGING);
        ColourManager manager(getValueLower(), getValueUpper());
        drawPieGlyphs( getPieGlyphs(), manager);
        drawLegend( manager );
        break;
    }
    case GLYPH_VARIABLE_PIE :
    {
        createPieGlyphs( getGroomedPolygons(), GLYPH_VARIABLE_PIE );
        calculateValueBounds( getPieGlyphs() );
        changeColorMap(this->CATEGORICAL);
        ColourManager manager(getValueLower(), getValueUpper());
        drawPieGlyphs( getPieGlyphs(), manager);
        drawLegend( manager );
        break;
    }
    case GLYPH_STAR :
    {

        calculateAbsoluteValueBounds( getGroomedPolygons() );
        setValueLower(0.2);
        setValueUpper(10.7);
        createStarGlyphs( getGroomedPolygons() );
        changeColorMap(this->CATEGORICAL);
        ColourManager manager(getValueLower(), getValueUpper());
        drawStarGlyphs( getStarGlyphs(), manager );
        drawLegend( manager );
        break;
    }
    }

    if( getClickedIndex() > NEGATIVE_INDEX )
    {
        drawPolygon(getGroomedPolygons().at(getClickedIndex()));
    }

    if( debugMousePointer() )
    {
        debugCircle( getMouse().x(),
                     getMouse().y(), Colour("FF0000"), 0.5f);
    }

    qDebug() << "drawn.";
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
    changeColorMap(this->OUTLINE);
    ColourManager outline(0,list.size());
    for ( int i = 0; i < list.size(); ++i )
    {
        TreeNode polygon = list.at( i );
        glLineWidth( 2 );
        glBegin( GL_LINE_STRIP );

        Colour c = outline.getInterpolatedColour(i);
        glColor4f( c.getR(), c.getG(), c.getB(), 0.8 );
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

void Canvas::createPieGlyphs( QVector<TreeNode> list, int pieType )
{
    QVector<PieChart> pies;
    foreach( TreeNode p, list)
    {
        if(p.getLevel() > -1)
        {
            QStringList values = p.getValues();
            for( int i = 0; i < 4; ++i )
                values.removeFirst();
            PieChart pie( *p.centroid(), p.getLevel() );
            if(pieType == GLYPH_EQUAL_PIE)
                pie.setSliceType(PieChart::EQUAL_SLICES);
            else
                pie.setSliceType(PieChart::FULL_SLICES);

            pie.initialize(values);
            pies.append(pie);
        }

    }

    setPieGlyphs(pies);
    return;
}

void Canvas::createStarGlyphs( QVector<TreeNode> list )
{
    QVector<StarGlyph> stars;
    foreach( TreeNode p, list )
    {
        if(p.getLevel() > -1)
        {
            QStringList values = p.getValues();
            for( int i = 0; i < 4; ++i )
                values.removeFirst();
            StarGlyph star( *p.centroid(), p.getLevel() );
            star.initialize(values, getValueUpper(), getValueLower());
            stars.append(star);
        }
    }

    setStarGlyphs(stars);
}

void Canvas::drawStarGlyphs( QVector<StarGlyph> list, ColourManager cm)
{
    Colour color;
    for( int i = 0; i < list.size(); ++ i )
    {
        StarGlyph s = list.at(i);
        glColor4f( 0.8, 0.8, 0.8, 0.8 );
        glBegin( GL_TRIANGLE_FAN );
        glVertex2f( s.centroid().x(), s.centroid().y() );
        double max = getLength() / 100;
        float valueRotation = (2*M_PI) / s.points().size();
        for( float j = 0; j < s.points().size(); ++j )
        {
            float x = s.centroid().x() + sin( valueRotation * j ) *
                    (( getGlyphSize()*2) * ( max * s.points().at(j) ) );
            float y = s.centroid().y() + cos( valueRotation * j ) *
                    (( getGlyphSize()*2)* ( max * s.points().at(j) ) );
            glVertex2f( x, y );
        }
        float x = s.centroid().x() + sin( valueRotation ) *
                (( getGlyphSize()*2) * ( max * s.points().at(0) ) );
        float y = s.centroid().y() + cos( valueRotation ) *
                (( getGlyphSize()*2)* ( max * s.points().at(0) ) );
        glVertex2f( x, y );

        glEnd();

        glColor4f( 0.105882353, 0.105882353, 0.105882353, 0.8);
        glBegin( GL_LINES );
        for( float j = 0; j < s.points().size(); ++j )
        {
            glVertex2f( s.centroid().x(), s.centroid().y() );
            float x = s.centroid().x() + sin( valueRotation * j ) *
                    (( getGlyphSize()*2) * ( max * s.points().at(j) ) );
            float y = s.centroid().y() + cos( valueRotation * j ) *
                    (( getGlyphSize()*2)* ( max * s.points().at(j) ) );
            glVertex2f( x, y );
        }
        glEnd();
    }
}

void Canvas::drawPieGlyphs( QVector<PieChart> list, ColourManager cm)
{
    Colour color;
    for( int j = 0; j < list.size(); ++j )
    {
        PieChart p = list.at(j);
//        Colour c = outline.getInterpolatedColour(j);
//        /* Outline */
        glColor4f( 0.105882353, 0.105882353, 0.105882353, 0.8 );
        glBegin( GL_TRIANGLE_FAN );
        glVertex2f( p.centroid().x(), p.centroid().y() );
//        double size = 1;
       double rad = getLength() /*+ scaleModifier()*/ / 100;

        for ( float angle = 0; angle <= (2*M_PI)+0.1; angle += 0.1 )
        {
            float x = p.centroid().x() + sin( angle ) *
                      ( getGlyphSize() * ( rad * ( 1 + p.size()/*0.03*/ ) ) );
            float y = p.centroid().y() + cos( angle ) *
                      ( getGlyphSize() * ( rad * ( 1 + p.size()/*+0.03*/ ) ) );

            glVertex3f( x, y, 0.5 );
        }
        glEnd();

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
            glColor4f( color.getR(), color.getG(), color.getB(), 1 );
            glBegin( GL_TRIANGLE_FAN );
            glVertex2f( p.centroid().x(), p.centroid().y() );

            for( float angle = currentAngle; angle <=
                 currentAngle+ps.angle()+0.05; angle+=0.1 )
            {
                float x = p.centroid().x() + sin( angle ) *
                          ( getGlyphSize() * ( ( rad ) ) );

                float y = p.centroid().y() + cos( angle ) *
                          ( getGlyphSize() * ( ( rad ) ) );
                glVertex3f( x, y, 0.5 );
            }
            glVertex2f( p.centroid().x(), p.centroid().y() );
            glEnd();
            currentAngle += ps.angle();
//            color = cm.getColourFromSeed(int(currentAngle));
        }
        for( int i = 0; i < p.pieSlices().size(); ++i )
        {
            PieSegment ps = p.pieSlices().at(i);
            glColor4f( 0.105882353, 0.105882353, 0.105882353, 0.6 );
            glBegin( GL_LINE_STRIP );
            glVertex2f( p.centroid().x(), p.centroid().y() );

            for( float angle = currentAngle; angle <=
                 currentAngle+ps.angle()+0.05; angle+=0.1 )
            {
                float x = p.centroid().x() + sin( angle ) *
                          ( getGlyphSize() * ( ( rad ) ) );

                float y = p.centroid().y() + cos( angle ) *
                          ( getGlyphSize() * ( ( rad ) ) );
                glVertex3f( x, y, 0.5 );
            }
            glVertex2f( p.centroid().x(), p.centroid().y() );
            glEnd();
            currentAngle += ps.angle();
        }

    }

    return;
}


void Canvas::drawLegend( ColourManager cm )
{
//    double scaleModifier = getLength() / 20;
    QPointF legendBL, legendBR, legendTL, legendTR;
    legendBL.setX( getWrapper().minimums.at(AABB::XDIM) - scaleModifier()/1.4);
    legendBL.setY( getWrapper().maximums.at(AABB::YDIM) + scaleModifier()/2.8);

    legendTL.setX( getWrapper().minimums.at(AABB::XDIM) - scaleModifier()/1.4);
    legendTL.setY( getWrapper().maximums.at(AABB::YDIM) + (scaleModifier()/1.4));

    legendBR.setX( getWrapper().minimums.at(AABB::XDIM) + scaleModifier()*5 );
    legendBR.setY( getWrapper().maximums.at(AABB::YDIM) + scaleModifier()/2.8);

    legendTR.setX( getWrapper().minimums.at(AABB::XDIM) + scaleModifier()*5);
    legendTR.setY( getWrapper().maximums.at(AABB::YDIM) + (scaleModifier()/1.4));

    double lRange = legendTR.x() - legendTL.x();
    double colorRange = cm.getUpperRange() - cm.getLowerRange();
    double slices = cm.getCurrentColourMap().classCount();
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
                   color.getB(), color.getAlpha() );

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

    glPrintString( getWrapper().minimums.at(AABB::XDIM) - (scaleModifier()/10),
                   legendBR.y() - (scaleModifier()/2.8) , lower );
    glPrintString( getWrapper().minimums.at(AABB::XDIM) + (scaleModifier()*5.1) ,
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
    setWrapper( AABB( wrapper.MinX,wrapper.MaxX,
                                  wrapper.MinY,wrapper.MaxY ) );
}

AABB Canvas::getWrapper() const
{
    return wrapper;
}

void Canvas::setWrapper(const AABB &value)
{
    wrapper = value;
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

    setLength( std::max( wrapper.length( AABB::XDIM ),
                             wrapper.length( AABB::YDIM ) ) );

    glOrtho( wrapper.minimums.at(AABB::XDIM) - scaleModifier(),
             wrapper.minimums.at(AABB::XDIM)+ getLength() + scaleModifier(),
             wrapper.minimums.at(AABB::YDIM) - scaleModifier(),
             wrapper.minimums.at(AABB::YDIM)+ getLength() + scaleModifier(),
             -1.0, 1.0 );

    glClear( GL_COLOR_BUFFER_BIT );
    return;
}

float Canvas::scaleModifier()
{
    return getLength() * 0.05;
}
