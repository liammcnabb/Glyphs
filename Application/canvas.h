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
#include <QMouseEvent>

#include "Spectrum/colourmanager.h"
#include "LM/IntersectTester/AABB.h"
#include "piechart.h"
#include "starglyph.h"
#include "SCZ/treenode.h"
#include "LM/IntersectTester/IntersectTester.h"

class Canvas : public QOpenGLWidget
{
public:
    static const int NEGATIVE_INDEX = -1;
    static const int COLORMAP_INDEX = 2;
    int VALUE_INDEX = 5;
    static const int GLYPH_CENTROID = 0;
    static const int GLYPH_EQUAL_PIE = 1;
    static const int GLYPH_VARIABLE_PIE = 2;
    static const int GLYPH_STAR = 3;

    static const int SEQUENTIAL = 0;
    static const int DIVERGING = 1;
    static const int CATEGORICAL = 2;
    static const int OUTLINE = 3;

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

    int getGlyphType() const;
    void setGlyphType(int value);

    void changeColorMap(int mapType);
    QVector<TreeNode> getGroomedPolygons() const;
    void setGroomedPolygons(const QVector<TreeNode> &groomedPolygons);

    float getGlyphSize() const;
    void setGlyphSize(float value);

    QPointF getMouse() const;
    void setMouse(const QPointF &value);

    bool debugMousePointer() const;
    void setDebugMousePointer(bool value);

    int getClickedIndex() const;
    void setClickedIndex(int clickedIndex);


    QStringList getDataHeaders() const;
    void setDataHeaders(const QStringList &value);

    QVector<StarGlyph> getStarGlyphs() const;
    void setStarGlyphs(const QVector<StarGlyph> &starGlyphs);

    QVector<float> getMeans() const;
    void setMeans(const QVector<float> &means);

    bool getTransitionState() const;
    void setTransitionState(bool transitionState);

    QVector<TreeNode> getTransitionNeutral() const;
    void setTransitionNeutral(const QVector<TreeNode> &transitionNeutral);

    QVector<TreeNode> getTransitionAdd() const;
    void setTransitionAdd(const QVector<TreeNode> &transitionAdd);

    QVector<TreeNode> getTransitionRemove() const;
    void setTransitionRemove(const QVector<TreeNode> &transitionRemove);

    float getCurrentTransitionSize() const;
    void setCurrentTransitionSize(float value);

private:
    bool m_debugMousePointer = false;

    bool m_transitionState = false;

    QVector<Polygon> m_loadedPolygons;
    QVector<TreeNode> m_groomedPolygons;
    QVector<PieChart> m_pieGlyphs;
    QVector<StarGlyph> m_starGlyphs;
    AABB wrapper;
    float length;
    float valueUpper;
    float valueLower;
    int glyphType = GLYPH_CENTROID;
    float glyphSize = 2.5f;

        QVector<TreeNode> m_transitionNeutral;
        QVector<TreeNode> m_transitionAdd;
        QVector<TreeNode> m_transitionRemove;
        float currentTransitionSize = 0.0f;


    QVector<float> m_means;

    int m_clickedIndex = NEGATIVE_INDEX;

    QStringList dataHeaders;

    QPointF mouse;

    void prepareDraw();
    void setOrtho();

    void redraw();
    void drawPolygons(QVector<Polygon> list);
    void drawPolygons(QVector<TreeNode> polyList);
    void drawCentroids(QVector<TreeNode> list, ColourManager cm);
    bool debugCircle(double centerX, double centerY, Colour color, double size);
    float scaleModifier();
    void calculateValueBounds(QVector<TreeNode> list);
    void calculateValueBounds(QVector<PieChart> list);
    void drawLegend(ColourManager cm);
    void glPrintString(float x, float y, std::string str);
    void glPrintString(void *font, const char *str);
    QVector<PieChart> createPieGlyphs(QVector<TreeNode> list, int pieType, int state);
    void drawPieGlyphs(QVector<PieChart> list, ColourManager cm);

    void mouseMoveEvent(QMouseEvent *event);
    float convertedX(float windowX);
    float convertedY(float windowY);
    int findClickedIndex(QPointF coords, QVector<PieChart> list);
    void drawPolygon(TreeNode polygon);
    void fillToolTip(int glyphIndex);
    void createStarGlyphs(QVector<TreeNode> list);
    void calculateAbsoluteValueBounds(QVector<TreeNode> list);
    void drawStarGlyphs(QVector<StarGlyph> list, ColourManager cm);
    void calculateValueBounds(QVector<StarGlyph> list);
};

#endif // CANVAS_H
