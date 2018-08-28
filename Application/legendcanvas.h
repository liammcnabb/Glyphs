#ifndef LEGENDCANVAS_H
#define LEGENDCANVAS_H

#include <QOpenGLWidget>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class LegendCanvas : public QOpenGLWidget
{
public:
    LegendCanvas(QWidget *parent);
    void initializeGL();
    void paintGL();
};

#endif // LEGENDCANVAS_H
