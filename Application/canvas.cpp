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


    //    connect( &timer, SIGNAL( timeout() ), this, SLOT( update() ) );
    //    timer.start( 1000 );
}

void Canvas::paintGL()
{
    if(loadedPolygons().size() > 0)
        redraw();
}

void Canvas::redraw()
{
    prepareDraw();
    glLineWidth( 1 );
    drawPolygons( loadedPolygons() );
    qDebug() << "drawn.";
}

void Canvas::drawPolygons(QVector<Polygon> list)
{
    for ( int i = 0; i < list.size(); ++i )
    {
        Polygon polygon = list.at( i );
        glLineWidth( 1 );
        glBegin( GL_LINE_STRIP );


        glColor4f( 0, 0, 0, 0.5 );

        for( QVector<QPointF>::const_iterator it =
                    polygon.getPoints().begin();
                it < polygon.getPoints().end(); ++it )
            glVertex2f( it->x(), it->y() );

        glEnd();
    }
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

    float length = std::max( wrapper.length( AABB::XDIM ),
                             wrapper.length( AABB::YDIM ) );
    glOrtho( wrapper.minimums.at(AABB::XDIM),
             wrapper.minimums.at(AABB::XDIM)+length,
             wrapper.minimums.at(AABB::YDIM),
             wrapper.minimums.at(AABB::YDIM)+length,
             -1.0, 1.0 );


    glClear( GL_COLOR_BUFFER_BIT );
    return;
}
