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
#include <algorithm>
#include <cmath>

#include "Spectrum/colourmanager.h"
#include "LM/aabb.h"
#include "piechart.h"

class Canvas : public QOpenGLWidget
{
public:
    int COLORMAP_INDEX = 2;
    int VALUE_INDEX = 5;
    Canvas(QWidget *parent);
    void initializeGL();
    void paintGL();
    void resizeGL( int w, int h );

    QVector<Polygon> loadedPolygons() const;
    void setLoadedPolygons(const QVector<Polygon> &loadedPolygons);

    void setDefaultOrtho(OGREnvelope wrapper);

    AABB getWrapper() const;
    void setWrapper(const AABB &value);

    float getLength() const;
    void setLength(float value);

    float getValueUpper() const;
    void setValueUpper(float value);

    float getValueLower() const;
    void setValueLower(float value);

    QVector<PieChart> getPieGlyphs() const;
    void setPieGlyphs(const QVector<PieChart> &pieGlyphs);

private:
    QVector<Polygon> m_loadedPolygons;
    QVector<PieChart> m_pieGlyphs;
    AABB wrapper;
    float length;
    float valueUpper;
    float valueLower;

    void prepareDraw();
    void setOrtho();

    void redraw();
    void drawPolygons(QVector<Polygon> polyList);
    void drawCentroids(QVector<Polygon> list, ColourManager cm);
    bool debugCircle(double centerX, double centerY, Colour color, double size);
    float scaleModifier();
    void calculateValueBounds(QVector<Polygon> list);
    void calculateValueBounds(QVector<PieChart> list);
    void drawLegend(ColourManager cm);
    void glPrintString(float x, float y, std::string str);
    void glPrintString(void *font, const char *str);
    void createPieGlyphs(QVector<Polygon> list);
    void drawPieGlyphs(QVector<PieChart> list, ColourManager cm);
};

#endif // CANVAS_H
