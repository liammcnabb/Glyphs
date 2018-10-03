#include "legendcanvas.h"



LegendCanvas::LegendCanvas(QWidget *parent) : QOpenGLWidget( parent )
{

}

void LegendCanvas::initializeGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable( GL_BLEND ); // Required Blending for alpha blending
    glEnable( GL_ALPHA ); // Lets you add alpha values
    //    glEnable( GL_LINE_STIPPLE ); // Enables Dotted Line for use
    glEnable( GL_STENCIL ); //Rendering using stencil buffer (used to render concave polygons)
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    //    glClearColor( BACKGROUND_COL, BACKGROUND_COL, BACKGROUND_COL,
    //                  1.0 );
    glClearColor(239.0f/255.0f,
                 235.0f/255.0f,
                 231.0f/255.0f,1);
    glOrtho(0,100,0,100,1,-1);


}

void LegendCanvas::paintGL()
{
    if( currentGlyphType() == GLYPH_VARIABLE_PIE )
        paintVariablePie();
    else if(currentGlyphType() == GLYPH_STAR )
        paintStarGlyph();
    else if (currentGlyphType() == GLYPH_EQUAL_PIE)
        paintWheelGlyph();
    else if (currentGlyphType() == GLYPH_BAR)
        paintBarChart();
}

void LegendCanvas::initializeLegend( QVector<float> averages )
{
    initializeVariablePie(averages);
    initalizeStarGlyph(averages);
    initalizeWheelGlyph(averages);
    initializeBarChart(averages);
}

void LegendCanvas::initializeVariablePie( QVector<float> averages )
{
    //    int seed = 0;
    //    srand(seed);
    PieChart p(QPointF(50,50),3,PieChart::NEUTRAL, QPointF( 0.0f, 0.0f ));
    QStringList samplePoints;
    for(int i =0; i < averages.size(); ++i)
        samplePoints.append(QString::number(averages.at(i)) );
    p.initialize(samplePoints);

    setVariablePie(p);
    return;
}

void LegendCanvas::initalizeStarGlyph( QVector<float> averages)
{
    //    int seed = 670;//13 //57
    //    srand(seed);
    StarGlyph s(QPointF(50,50),3,StarGlyph::NEUTRAL, QPointF( 0.0f, 0.0f ));
    QStringList samplePoints;
    for( int i = 0; i < averages.size(); ++i )
    {
        samplePoints.append(QString::number(averages.at(i)));
    }
    s.initialize(samplePoints);
    setStarGlyph(s);
    return;
}

void LegendCanvas::initalizeWheelGlyph(QVector<float> averages)
{
    //    int seed = 13;
    //    srand(seed);
    WheelGlyph s(QPointF(50,50),3,WheelGlyph::NEUTRAL, QPointF( 0.0f, 0.0f ));
    QStringList samplePoints;
    for( int i = 0; i < averages.size(); ++i )
    {
        samplePoints.append(QString::number(averages.at(i)) );
    }
    s.initialize(samplePoints);
    setWheelGlyph(s);
    return;
}

void LegendCanvas::initializeBarChart(QVector<float> averages)
{
    //    int seed = 0;
    //    srand(seed);
    BarChart b(QPointF(50,60),3,BarChart::NEUTRAL, QPointF( 0.0f, 0.0f ));
    QStringList samplePoints;
    for(int i =0; i < averages.size(); ++i)
        samplePoints.append(QString::number(averages.at(i)) );
    b.initialize(samplePoints);

    setBarChart(b);
    return;
}

void LegendCanvas::changeColorMap(int mapType)
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
        ColourMap cMap = CMList::getMapList(CMClassification::DIVERGING)[2];
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

void LegendCanvas::paintVariablePie()
{
    PieChart p = variablePie();
    ColourManager cm(0,p.pieSlices().size());
    Colour color;
    /* Outline */
    glColor4f( 0.105882353, 0.105882353, 0.105882353, 0.8 );
    glBegin( GL_TRIANGLE_FAN );
    glVertex2f( p.centroid().x(), p.centroid().y() );
    double size = 1;
    double rad = 22.5;

    for ( float angle = 0; angle <= (2*M_PI)+0.1; angle += 0.01 )
    {
        float x = p.centroid().x() + sin( angle ) *
                ( size * ( rad * ( 1 + p.size() ) ) );
        float y = p.centroid().y() + cos( angle ) *
                ( size * ( rad * ( 1 + p.size() ) ) );

        glVertex3f( x, y, 0.5 );
    }
    glEnd();

    changeColorMap(this->CATEGORICAL);
    float currentAngle = 0;
    for( int i = 0; i < p.pieSlices().size(); ++i )
    {
        PieSegment ps = p.pieSlices().at(i);
        if( valueFilters().at(i) )
            color = cm.getColourFromIndex(i);
        else
            color = Colour(0.7,0.7,0.7,1);
        /* Fill */
        glColor4f( color.getR(), color.getG(), color.getB(), 1 );
        glBegin( GL_TRIANGLE_FAN );
        glVertex2f( p.centroid().x(), p.centroid().y() );

        for( float angle = 0; angle <
             ps.angle(); angle+=0.01 )
        {
            float x = p.centroid().x() + sin( currentAngle + angle ) *
                    ( size * ( ( rad ) ) );

            float y = p.centroid().y() + cos( currentAngle + angle ) *
                    ( size * ( ( rad ) ) );
            glVertex3f( x, y, 0.5 );
        }
        glVertex2f( p.centroid().x(), p.centroid().y() );
        glEnd();
        currentAngle += ps.angle();
    }
    /* Outline */
    currentAngle = 0;
    for( int i = 0; i < p.pieSlices().size(); ++i )
    {
        PieSegment ps = p.pieSlices().at(i);
        glColor4f( 0.105882353, 0.105882353, 0.105882353, 0.6 );
        glBegin( GL_LINE_STRIP );
        glVertex2f( p.centroid().x(), p.centroid().y() );

        for( float angle = currentAngle; angle <=
             currentAngle+ps.angle(); angle+=0.001 )
        {
            float x = p.centroid().x() + sin( angle ) *
                    ( size * ( ( rad ) ) );

            float y = p.centroid().y() + cos( angle ) *
                    ( size * ( ( rad ) ) );
            glVertex3f( x, y, 0.5 );
        }
        glVertex2f( p.centroid().x(), p.centroid().y() );
        glEnd();
        currentAngle += ps.angle();
        //        qDebug() << currentAngle;
        float a = p.centroid().x() + sin( currentAngle - (ps.angle()/2) ) *
                ( size * ( ( rad ) ) * 1.7 );
        float b = p.centroid().y() + cos( currentAngle - (ps.angle()/2) ) *
                ( size * ( ( rad ) ) * 1.6 );
        std::string s = valueHeaders().at(i).toStdString().substr(0,9) + "...";
        glPrintString(a,b,s);
    }

    glColor3f(0,0,0);

    glPrintString(46,1,"Outline Thickness presents: Represented Areas");

    return;
}

QVector<bool> LegendCanvas::valueFilters() const
{
    return m_valueFilters;
}

void LegendCanvas::setValueFilters(const QVector<bool> &valueFilters)
{
    m_valueFilters = valueFilters;
}

QStringList LegendCanvas::valueHeaders() const
{
    return m_valueHeaders;
}

void LegendCanvas::setValueHeaders(const QStringList &valueHeaders)
{
    m_valueHeaders = valueHeaders;
}

QVector<float> LegendCanvas::mins() const
{
    return m_mins;
}

void LegendCanvas::setMins(const QVector<float> &mins)
{
    m_mins = mins;
}

QVector<float> LegendCanvas::maxes() const
{
    return m_maxes;
}

void LegendCanvas::setMaxes(const QVector<float> &maxes)
{
    m_maxes = maxes;
}

QVector<float> LegendCanvas::means() const
{
    return m_means;
}

void LegendCanvas::setMeans(const QVector<float> &means)
{
    m_means = means;
}

BarChart LegendCanvas::barChart() const
{
    return m_barChart;
}

void LegendCanvas::setBarChart(const BarChart &barChart)
{
    m_barChart = barChart;
}

bool LegendCanvas::colorStarLines() const
{
    return m_colorStarLines;
}

void LegendCanvas::setColorStarLines(bool colorStarLines)
{
    m_colorStarLines = colorStarLines;
}

WheelGlyph LegendCanvas::wheelGlyph() const
{
    return m_wheelGlyph;
}

void LegendCanvas::setWheelGlyph(const WheelGlyph &wheelGlyph)
{
    m_wheelGlyph = wheelGlyph;
}

void LegendCanvas::paintStarGlyph()
{
    Colour color;
    ColourManager cm(-10, 10);
    //    Colour color;
    changeColorMap(this->CATEGORICAL);
    double max = 50;
    int totalNooks = 11;
    int nook;
    int nookSegment = max / totalNooks;
    StarGlyph s = starGlyph();

    glColor4f( 0.8, 0.8, 0.8, 1 );
    glBegin( GL_TRIANGLE_FAN );
    glVertex2f( s.centroid().x(), s.centroid().y() );

    double value, size = 1;
    int x,y;
    //Fill
    float valueRotation = (2*M_PI) / s.points().size();
    for( float j = 0; j < s.points().size(); ++j )
    {
        //        ColourManager cm(mins().at(j), maxes().at(j));
        value = (s.points().at(j) - mins().at(j)) /
                (maxes().at(j) - mins().at(j) );
        x = s.centroid().x() + sin( valueRotation * j ) *
                max * value ;
        y = s.centroid().y() + cos( valueRotation * j ) *
                max * value ;
        glVertex2f( x, y );
    }
    value = (s.points().at(0) - mins().at(0)) /
            (maxes().at(0) - mins().at(0) );
    x = s.centroid().x() + sin( 0 ) *
            max * value ;
    y = s.centroid().y() + cos( 0 ) *
            max * value ;
    glVertex2f( x, y );

    glEnd();
    glColor4f( 0.105882353, 0.105882353, 0.105882353, 0.8);
    //Outlines
    glBegin( GL_LINE_STRIP );
    glVertex2f( s.centroid().x(), s.centroid().y() );
    for( float j = 0; j < s.points().size(); ++j )
    {
        value = (s.points().at(j) - mins().at(j)) /
                (maxes().at(j) - mins().at(j) );
        x = s.centroid().x() + sin( valueRotation * j ) *
                max * value ;
        y = s.centroid().y() + cos( valueRotation * j ) *
                max * value ;
        glVertex2f( x, y );
    }
    value = (s.points().at(0) - mins().at(0)) /
            (maxes().at(0) - mins().at(0) );
    x = s.centroid().x() + sin( 0 ) *
            max * value ;
    y = s.centroid().y() + cos( 0 ) *
            max * value ;
    glVertex2f( x, y );

    glEnd();

    //Lines at Points


    for( float j = 0; j < s.points().size(); ++j )
    {
        if( colorStarLines() )
        {
            color = cm.getColourFromIndex(j);
            glColor3f(color.getR(),color.getG(),color.getB());
        }
        else
            glColor4f( 0.105882353, 0.105882353, 0.105882353, 0.8);

        glBegin( GL_LINES );
        value = (s.points().at(j) - mins().at(j)) /
                (maxes().at(j) - mins().at(j) );
        x = s.centroid().x() + sin( valueRotation * j ) *
                max * value ;
        y = s.centroid().y() + cos( valueRotation * j ) *
                max * value ;
        glVertex2f(s.centroid().x(), s.centroid().y());
        glVertex2f( x, y );
        glEnd();

        float a = s.centroid().x() + sin( valueRotation * j ) *
                max * value  * 1.6 ;
        float b = s.centroid().y() + cos( valueRotation * j ) *
                max * value * 1.6;
        std::string s = valueHeaders().at(j).toStdString().substr(0,9) + "...";
        glPrintString(a,b,s);

    }


    //    //Standard
    //    glColor4f( 1, 0.105882353, 0.105882353, 0.3);
    //    glBegin( GL_LINE_STRIP );
    ////    glVertex2f( s.centroid().x(), s.centroid().y() );
    //    for( float j = 0; j < s.points().size(); ++j )
    //    {
    //        nook = cm.getClassColourIndex(0);
    //        x = s.centroid().x() + sin( valueRotation * j ) *
    //                ( size  * ( nookSegment * ( 1+nook ) ) );
    //        y = s.centroid().y() + cos( valueRotation * j ) *
    //                ( size  * ( nookSegment * ( 1+nook ) ) );
    //        glVertex2f( x, y );
    //    }
    //    nook = cm.getClassColourIndex(0);
    //    x = s.centroid().x() + sin( 0 ) *
    //                ( size  * ( nookSegment * ( 1+nook ) ) );
    //    y = s.centroid().y() + cos( 0 ) *
    //                ( size  * ( nookSegment * ( 1+nook ) ) );
    //    glVertex2f( x, y );

    //    glEnd();

    glColor4f( 0.105882353, 0.105882353, 0.105882353, 0.8);
    //    glPrintString(1,1,"Red Line presents: Standard value per field");
    //    glPrintString(48.5,88,"1");
    //    glPrintString(80,80,"2");
    //    glPrintString(54,54,"3");
    //    glPrintString(48.5,37,"4");
    //    glPrintString(32,50,"5");
    //    glPrintString(15,76,"6");

}

void LegendCanvas::paintWheelGlyph()
{
    ColourManager cm(-10, 10);
    Colour color;
    changeColorMap(this->CATEGORICAL);
    double value, max = 40;

    float x,y;
    WheelGlyph s = wheelGlyph();
    float valueRotation = (2*M_PI) / s.getRads().size();
    //Extents
    glColor4f( 0.105882353, 0.105882353, 0.105882353, 0.3);
    glBegin( GL_LINES );
    //        glVertex2f( s.centroid().x(), s.centroid().y() );

    for(float angle = 0; angle < 2*M_PI; angle += 0.01)
    {
        x = s.centroid().x() + sin( angle ) *
                max;
        y = s.centroid().y() + cos( angle ) *
                max;
        glVertex2f(x,y);
    }
    glEnd();

    //        glColor4f( 0.8, 0.8, 0.8, 1 );
    cm = ColourManager(mins().at(0), maxes().at(0));
    color = cm.getColourFromIndex(0);

    float currentAngle = 0;

    for ( int i = 0; i < s.getRads().size(); ++i )
    {
        cm = ColourManager(mins().at(i), maxes().at(i));
        color = cm.getColourFromIndex(i);
        glColor3f(color.getR(), color.getG(), color.getB() );
        glBegin( GL_TRIANGLE_FAN );
        glVertex2f( s.centroid().x(), s.centroid().y() );
        value = ( s.getRads().at(i) - mins().at(i) ) /
                ( maxes().at(i) - mins().at(i) ) ;
        //            qDebug() << value;
        for( float angle = currentAngle;
             angle < currentAngle + valueRotation; angle += 0.01)
        {
            x = s.centroid().x() + sin( angle ) *
                    max  * value;
            y = s.centroid().y() + cos( angle ) *
                    max  * value;
            glVertex2f( x, y );
        }
        glEnd( );
        currentAngle += valueRotation;
    }

    currentAngle = 0;
    glColor4f( 0.105882353, 0.105882353, 0.105882353, 1);

    for ( int i = 0; i < s.getRads().size(); ++i )
    {
        value = ( s.getRads().at(i) - mins().at(i) ) /
                ( maxes().at(i) - mins().at(i) ) ;
        float a = s.centroid().x() + sin( currentAngle + (valueRotation/2) ) *
                max  * ( value + 0.4 ) ;
        float b = s.centroid().y() + cos( currentAngle + (valueRotation/2) ) *
                max  * ( value + 0.3 ) ;
        std::string str = valueHeaders().at(i).toStdString().substr(0,9) + "...";
        glPrintString(a,b,str);


        glBegin( GL_LINE_STRIP );
        glVertex2f( s.centroid().x(), s.centroid().y() );
        for( float angle = currentAngle;
             angle < currentAngle + valueRotation; angle += 0.01)
        {
            x = s.centroid().x() + sin( angle ) *
                    max  * value;
            y = s.centroid().y() + cos( angle ) *
                    max  * value;
            glVertex2f( x, y );
        }
        glVertex2f( s.centroid().x(), s.centroid().y() );
        glEnd( );
        currentAngle += valueRotation;
    }




    //        int sliceNo = -1;
    //        //Fill

    //        for( float angle = 0; angle < 2*M_PI; angle += 0.01 )
    //        {
    //            if(sliceNo < s.getRads().size()-1 &&
    //                    int(angle*100) % int(roundf(valueRotation)*100) == 0)
    //            {
    //                glVertex2f( s.centroid().x(), s.centroid().y() );
    //                glEnd();
    //                sliceNo++;
    //                cm = ColourManager(mins().at(sliceNo), maxes().at(sliceNo));
    //                color = cm.getColourFromIndex(sliceNo);
    //                glColor3f(0.105882353, 0.105882353, 0.105882353 );
    //                value = ( s.getRads().at(sliceNo) - mins().at(sliceNo) ) /
    //                        ( maxes().at(sliceNo) - mins().at(sliceNo) ) ;
    //                float a = s.centroid().x() + sin( angle + (valueRotation/2) ) *
    //                         max  * value * 1.7 ;
    //                float b = s.centroid().y() + cos( angle + (valueRotation/2) ) *
    //                         max  * value * 1.6 ;
    //                std::string str = valueHeaders().at(sliceNo).toStdString().substr(0,9) + "...";
    //                glPrintString(a,b,str);
    //                glBegin(GL_TRIANGLE_FAN);
    //                color = cm.getColourFromIndex(sliceNo);
    //                glColor3f(color.getR(), color.getG(), color.getB() );
    //                glVertex2f( s.centroid().x(), s.centroid().y() );
    //            }
    //            color = cm.getColourFromIndex(sliceNo);
    //            glColor3f(color.getR(), color.getG(), color.getB() );
    //            nook = cm.getClassColourIndex( ( s.getRads().at(sliceNo) - mins().at(sliceNo) ) /
    //                                          ( maxes().at(sliceNo) - mins().at(sliceNo) ) );
    //            x = s.centroid().x() + sin( angle ) *
    //                     max  * value;
    //            y = s.centroid().y() + cos( angle ) *
    //                     max  * value ;
    //            glVertex2f( x, y );
    //        }
    //        x = s.centroid().x() + sin( 0 ) *
    //                 max  * value;
    //        y = s.centroid().y() + cos( 0 ) *
    //                 max  * value ;
    //        glVertex2f(x,y);
    //        glVertex2f( s.centroid().x(), s.centroid().y() );

    //        glEnd();

    //        sliceNo = -1;
    //        //Outlines
    //        glColor4f(0.105882353, 0.105882353, 0.105882353, 0.8);
    //        glBegin( GL_LINE_STRIP );
    //        for( float angle = 0; angle <= 2*M_PI; angle += 0.01 )
    //        {
    //            if(sliceNo < s.getRads().size()-1 &&
    //                    int(angle*100) % int(roundf(valueRotation)*100) == 0)
    //            {
    //                sliceNo++;
    ////                cm = ColourManager(mins().at(sliceNo), maxes().at(sliceNo));
    //                glVertex2f( s.centroid().x(), s.centroid().y() );
    //            }
    //            value = ( s.getRads().at(sliceNo) - mins().at(sliceNo) ) /
    //                    ( maxes().at(sliceNo) - mins().at(sliceNo) );
    //            x = s.centroid().x() + sin( angle ) *
    //                    max  * value;
    //            y = s.centroid().y() + cos( angle ) *
    //                    max  * value;
    //            glVertex2f( x, y );
    //        }
    //        x = s.centroid().x() + sin( 0 ) *
    //                max  * value;
    //        y = s.centroid().y() + cos( 0 ) *
    //                max  * value;
    //        glVertex2f(x,y);
    //        glVertex2f( s.centroid().x(), s.centroid().y() );
    //        glEnd();

    return;
}

void LegendCanvas::paintBarChart()
{

    Colour color;
    changeColorMap(this->CATEGORICAL);
    double max = 60;
    int bars = barChart().values().size();
    BarChart b = barChart();
    ColourManager cm(0, b.values().size());

    glColor4f( 0.8, 0.8, 0.8, 1 );

    //        glVertex2f( s.centroid().x(), s.centroid().y() );

    double size = 1;

    int barWidth = (max / bars) * (size * 0.7);
    //Fill
    float minX, width, minY, height;
    for( int j = 0; j < bars; ++j )
    {
        minX = ( b.centroid().x() - ((max/3) * size) ) + (barWidth*j);
        width = barWidth;
        minY = ( b.centroid().y() - ((max/3) * size) );
        //        qDebug() << b.values().at(j) << maxes().at(j) << mins().at(j);
        height = ( (b.values().at(j)-mins().at(j)) /
                   (maxes().at(j)-mins().at(j)) )  * (max *size);
        color = cm.getColourFromIndex(j);
        glColor3f(color.getR(), color.getG(), color.getB());

        glBegin( GL_QUADS );
        glVertex2f(minX, minY);
        glVertex2f(minX, minY+height);
        glVertex2f(minX+width, minY+height);
        glVertex2f(minX+width,minY);
        //            glVertex2f(minX, minY);
        glEnd();
    }

    //        //Outlines
    glColor4f( 0.105882353, 0.105882353, 0.105882353, 0.8);
    for( int j = 0; j < bars; ++j )
    {
        minX = ( b.centroid().x() - ((max/3) * size) ) + (barWidth*j);
        width = barWidth;
        minY = ( b.centroid().y() - ((max/3) * size) );
        height = ( (b.values().at(j)-mins().at(j)) /
                   (maxes().at(j)-mins().at(j)) )  * (max *size);

        glBegin( GL_LINE_STRIP );
        glVertex2f(minX, minY);
        glVertex2f(minX, minY+height);
        glVertex2f(minX+width, minY+height);
        glVertex2f(minX+width,minY);
        glVertex2f(minX, minY);
        glEnd();

        std::string s = valueHeaders().at(j).toStdString().substr(0,9) + "...";

        //        glBegin( GL_LINES );
        //        glVertex2f(minX+(width/2),35);
        //        glVertex2f(minX+(width/2),37-(3.6*j)-2);
        //        glEnd();
        glPrintString(minX+(width/2),35-(5*j),s);
    }

    glColor4f( 0.105882353, 0.105882353, 0.105882353, 0.8);
    //    glPrintString(1,1,"Red Line presents: Standard value per field");

}

StarGlyph LegendCanvas::starGlyph() const
{
    return m_starGlyph;
}

void LegendCanvas::setStarGlyph(const StarGlyph &starGlyph)
{
    m_starGlyph = starGlyph;
}

void LegendCanvas::glPrintString(float x, float y, std::string str)
{
    glPrintString( GLUT_BITMAP_HELVETICA_12, str.c_str(), x, y );
}



void LegendCanvas::glPrintString( void* font, const char* str, float x, float y)
{

    //    glRasterPos2f( x, y );
    int len, i, strWidth;

    len = ( int )strlen( str );

    //    for( i = 0; i < len; ++i )
    //        strWidth += glutBitmapWidth(GLUT_BITMAP_HELVETICA_12, str[i]);

    //    qDebug() << strWidth;
    glRasterPos2f( x-(len), y );

    for ( i = 0; i < len; ++i )
        glutBitmapCharacter( font, str[i] );

    glEnd();
}

void LegendCanvas::glPrintVerticalString(float x, float y, std::string str)
{
    glPrintVerticalString( GLUT_BITMAP_HELVETICA_12, str.c_str(), x, y );
}

void LegendCanvas::glPrintVerticalString( void* font, const char* str, float x, float y)
{

    //    glRasterPos2f( x, y );
    int len, i, strWidth;

    len = ( int )strlen( str );

    //    for( i = 0; i < len; ++i )
    //        strWidth += glutBitmapWidth(GLUT_BITMAP_HELVETICA_12, str[i]);

    //    qDebug() << strWidth;

    for ( i = 0; i < len; ++i )
    {
        glRasterPos2f( x, y-(i*3.6) );
        glutBitmapCharacter( font, str[i] );
    }

    glEnd();
}

int LegendCanvas::currentGlyphType() const
{
    return m_currentGlyphType;
}

void LegendCanvas::setCurrentGlyphType(int currentGlyphType)
{
    m_currentGlyphType = currentGlyphType;
}

PieChart LegendCanvas::variablePie() const
{
    return m_variablePie;
}

void LegendCanvas::setVariablePie(const PieChart &VariablePie)
{
    m_variablePie = VariablePie;
}
