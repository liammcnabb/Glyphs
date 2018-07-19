#ifndef CANVAS_H
#define CANVAS_H

#include <QOpenGLWidget>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <QVector>
#include <SCZ/polygon.h>
#include <gdal/ogr_core.h>
#include <QDebug>

#include "LM/aabb.h"

class Canvas : public QOpenGLWidget
{
public:
    Canvas(QWidget *parent);
    void initializeGL();
    void paintGL();
    void resizeGL( int w, int h );

    QVector<Polygon> loadedPolygons() const;
    void setLoadedPolygons(const QVector<Polygon> &loadedPolygons);

    void setDefaultOrtho(OGREnvelope wrapper);

    AABB getWrapper() const;
    void setWrapper(const AABB &value);

private:
    QVector<Polygon> m_loadedPolygons;
    AABB wrapper;

    void prepareDraw();
    void setOrtho();

    void redraw();
    void drawPolygons(QVector<Polygon> polyList);
};

#endif // CANVAS_H
