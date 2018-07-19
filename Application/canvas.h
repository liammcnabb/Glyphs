#ifndef CANVAS_H
#define CANVAS_H

#include <QOpenGLWidget>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class Canvas : public QOpenGLWidget
{
public:
    Canvas(QWidget *parent);
    void initializeGL();
    void paintGL();
    void resizeGL( int w, int h );
};

#endif // CANVAS_H
