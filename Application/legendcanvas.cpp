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
    glClearColor(1,1,1,1);
}

void LegendCanvas::paintGL()
{

}

void LegendCanvas::paintVariablePie()
{

}
