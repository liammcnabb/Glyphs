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

    initializeVariablePie();
    initalizeStarGlyph();
}

void LegendCanvas::paintGL()
{
    if( currentGlyphType() == GLYPH_VARIABLE_PIE )
        paintVariablePie();
    else if(currentGlyphType() == GLYPH_STAR )
        paintStarGlyph();
}

void LegendCanvas::initializeVariablePie()
{
    int seed = 0;
    srand(seed);
    PieChart p(QPointF(50,60),3,PieChart::NEUTRAL);
    QStringList samplePoints;
    for(int i =0; i < SAMPLE_POINTS; ++i)
        samplePoints.append(QString::number( (rand() % SAMPLE_POINTS) + 1 ) );
    p.initialize(samplePoints);

    setVariablePie(p);
    return;
}

void LegendCanvas::initalizeStarGlyph()
{
    int seed = 670;//13 //57
    srand(seed);
    StarGlyph s(QPointF(50,60),3,StarGlyph::NEUTRAL);
    QStringList samplePoints;
    QVector<float> mean;
    for( int i = 0; i < SAMPLE_POINTS; ++i )
    {
        samplePoints.append(QString::number( (rand() % 50) ) );
        mean.append(25);
    }
    s.initialize(samplePoints, mean);
    setStarGlyph(s);
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
    ColourManager cm(0,SAMPLE_POINTS);
    PieChart p = variablePie();
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
        color = cm.getColourFromIndex(i);
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
    }

    glColor3f(0,0,0);
    glPrintString(1,1,"Outline Thickness presents: Represented Areas");
    glPrintString(55,77.5,"1");
    glPrintString(65,60,"2");
    glPrintString(57,43,"3");
    glPrintString(41,43,"4");
    glPrintString(30,60,"5");
    glPrintString(44,77.5,"6");

    return;
}

void LegendCanvas::paintStarGlyph()
{
    ColourManager cm(-10, 10);
//    Colour color;
    changeColorMap(this->CATEGORICAL);
    double max = 40;
    int totalNooks = 11;
    int nook;
    int nookSegment = max / totalNooks;
    StarGlyph s = starGlyph();

    glColor4f( 0.8, 0.8, 0.8, 1 );
    glBegin( GL_TRIANGLE_FAN );
    glVertex2f( s.centroid().x(), s.centroid().y() );

    double size = 1;
    int x,y;
    //Fill
    float valueRotation = (2*M_PI) / s.points().size();
    for( float j = 0; j < s.points().size(); ++j )
    {
        nook = cm.getClassColourIndex(s.points().at(j));
        x = s.centroid().x() + sin( valueRotation * j ) *
                 ( nookSegment * ( 1+nook ) ) ;
        y = s.centroid().y() + cos( valueRotation * j ) *
                 ( nookSegment * ( 1+nook ) ) ;
        glVertex2f( x, y );
    }
    nook = cm.getClassColourIndex(s.points().at(0));
    x = s.centroid().x() + sin( 0 ) *
                ( nookSegment * ( 1+nook ) ) ;
    y = s.centroid().y() + cos( 0 ) *
                ( nookSegment * ( 1+nook) );
    glVertex2f( x, y );

    glEnd();

    //Lines at Points
    glColor4f( 0.105882353, 0.105882353, 0.105882353, 0.8);
    glBegin( GL_LINES );
    for( float j = 0; j < s.points().size(); ++j )
    {
        nook = cm.getClassColourIndex(s.points().at(j));
        glVertex2f( s.centroid().x(), s.centroid().y() );
        x = s.centroid().x() + sin( valueRotation * j ) *
                ( size  * ( nookSegment * ( 1+nook ) ) );
        y = s.centroid().y() + cos( valueRotation * j ) *
                ( size  * ( nookSegment * ( 1+nook ) ) );
        glVertex2f( x, y );
    }
    glEnd();

    //Outlines
    glBegin( GL_LINE_STRIP );
    glVertex2f( s.centroid().x(), s.centroid().y() );
    for( float j = 0; j < s.points().size(); ++j )
    {
        nook = cm.getClassColourIndex(s.points().at(j));
        x = s.centroid().x() + sin( valueRotation * j ) *
                ( size  * ( nookSegment * ( 1+nook ) ) );
        y = s.centroid().y() + cos( valueRotation * j ) *
                ( size  * ( nookSegment * ( 1+nook ) ) );
        glVertex2f( x, y );
    }
    nook = cm.getClassColourIndex(s.points().at(0));
    x = s.centroid().x() + sin( 0 ) *
                ( size  * ( nookSegment * ( 1+nook ) ) );
    y = s.centroid().y() + cos( 0 ) *
                ( size  * ( nookSegment * ( 1+nook ) ) );
    glVertex2f( x, y );

    glEnd();

    //Standard
    glColor4f( 1, 0.105882353, 0.105882353, 0.3);
    glBegin( GL_LINE_STRIP );
    glVertex2f( s.centroid().x(), s.centroid().y() );
    for( float j = 0; j < s.points().size(); ++j )
    {
        nook = cm.getClassColourIndex(0);
        x = s.centroid().x() + sin( valueRotation * j ) *
                ( size  * ( nookSegment * ( 1+nook ) ) );
        y = s.centroid().y() + cos( valueRotation * j ) *
                ( size  * ( nookSegment * ( 1+nook ) ) );
        glVertex2f( x, y );
    }
    nook = cm.getClassColourIndex(0);
    x = s.centroid().x() + sin( 0 ) *
                ( size  * ( nookSegment * ( 1+nook ) ) );
    y = s.centroid().y() + cos( 0 ) *
                ( size  * ( nookSegment * ( 1+nook ) ) );
    glVertex2f( x, y );

    glEnd();

    //Nooks
    glColor4f( 0.105882353, 0.105882353, 0.105882353, 0.8);
    glBegin( GL_LINES );
    for( float j = 0; j < s.points().size(); ++j )
    {
        for( float k = 0; k < totalNooks; ++k )
        {
            nook = cm.getClassColourIndex(s.points().at(k));
            glVertex2f( s.centroid().x(), s.centroid().y() );
            x = s.centroid().x() + sin( valueRotation * j ) *
                    ( size  * ( nookSegment * ( 1+nook ) ) );
            y = s.centroid().y() + cos( valueRotation * j ) *
                    ( size  * ( nookSegment * ( 1+nook ) ) );
            glVertex2f( x, y );

            x = x + sin( ( valueRotation * j ) + ( M_PI / 2 ) ) *
                        nookSegment;
            y = y + cos( ( valueRotation * j ) + ( M_PI / 2 ) ) *
                        nookSegment;
            glVertex2f( x, y );
            glEnd();
        }
    }

    glPrintString(1,1,"Red Line presents: Standard value per field");
    glPrintString(48.5,88,"1");
    glPrintString(80,80,"2");
    glPrintString(54,54,"3");
    glPrintString(48.5,37,"4");
    glPrintString(32,50,"5");
    glPrintString(15,76,"6");

}

StarGlyph LegendCanvas::starGlyph() const
{
    return m_starGlyph;
}

void LegendCanvas::setStarGlyph(const StarGlyph &starGlyph)
{
    m_starGlyph = starGlyph;
}

void LegendCanvas::glPrintString( float x, float y, std::string str )
{
    glRasterPos2f( x, y );

    glPrintString( GLUT_BITMAP_HELVETICA_12, str.c_str() );
}

void LegendCanvas::glPrintString( void* font, const char* str )
{
    int len, i;

    len = ( int )strlen( str );

    for ( i = 0; i < len; i++ )
        glutBitmapCharacter( font, str[i] );

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
