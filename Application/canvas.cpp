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
    prepareDraw();
}

void Canvas::resizeGL( int w, int h )
{
    //qDebug() <<w<<h; //Remove warnings
    update();
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

    glOrtho( 100, 100,
             100, 100,
             -1.0, 1.0 );


    glClear( GL_COLOR_BUFFER_BIT );
    return;
}
