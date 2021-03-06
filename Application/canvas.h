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
#include "wheelglyph.h"
#include "barchart.h"
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
    static const int GLYPH_BAR = 4;

    static const int HIDDEN_OUTLINE = 0;
    static const int HIDDEN_SIZE = 1;
    static const int HIDDEN_RINGS = 2;
    static const int HIDDEN_SIZEOUTLINE = 3;


    static const int SEQUENTIAL = 0;
    static const int DIVERGING = 1;
    static const int CATEGORICAL = 2;
    static const int OUTLINE = 3;

    static const int TRANSITION_IN = 1;
    static const int TRANSITION_OUT = -1;

    static const int ADV_FILTER_NA = 0;
    static const int ADV_FILTER_ABOVE = 1;
    static const int ADV_FILTER_BELOW = 2;

    static const bool DEBUG = false;

    Canvas(QWidget *parent);
    void initializeGL();
    void paintGL();
    void resizeGL( int w, int h );

    QVector<Polygon> loadedPolygons() const;
    void setLoadedPolygons(const QVector<Polygon> &loadedPolygons);

    void setDefaultOrtho(OGREnvelope wrapper);

    AABB getOriginalWrapper() const;
    void setOriginalWrapper(const AABB &value);

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

    float getAreaOpacity() const;
    void setAreaOpacity(float areaOpacity);

    QVector<WheelGlyph> getWheelGlyphs() const;
    void setWheelGlyphs(const QVector<WheelGlyph> &wheelGlyphs);

    bool getColorStarLines() const;
    void setColorStarLines(bool colorStarLines);

    int getHiddenIndicator() const;
    void setHiddenIndicator(int hiddenIndicator);

    QVector<BarChart> getBarCharts() const;
    void setBarCharts(const QVector<BarChart> &barCharts);

    float getZoom() const;
    void setZoom(float zoom);

    AABB getCurrentWrapper() const;
    void setCurrentWrapper(const AABB &currentWrapper);

    QVector<float> getMaxes() const;
    void setMaxes(const QVector<float> &maxes);

    QVector<float> getMins() const;
    void setMins(const QVector<float> &mins);

    int getTransitionType() const;
    void setTransitionType(int value);

    bool getExtents() const;
    void setExtents(bool extents);

    QVector<bool> getValueFilters() const;
    void setValueFilters(const QVector<bool> &valueFilters);

    int getColorMap() const;
    void setColorMap(int colorMap);

    bool getIndicatorMatches() const;
    void setIndicatorMatches(bool indicatorMatches);

    int getFocusContextType() const;
    void setFocusContextType(int focusContextType);

    float getCurrentScale() const;
    void setCurrentScale(float currentScale);

    float getTranslationX() const;
    void setTranslationX(float value);

    float getTranslationY() const;
    void setTranslationY(float value);

    bool getGrid() const;
    void setGrid(bool grid);

    QVector<TreeNode> getGridStructure() const;
    void setGridStructure(const QVector<TreeNode> &gridStructure);

    void drawBox(AABB box);
    int getAdvFilter() const;
    void setAdvFilter(int advFilter);

private:
    float outline_r = 0.388235294f;
    float outline_g = 0.388235294f;
    float outline_b = 0.388235294f;
    bool m_debugMousePointer = false;
    bool m_transitionState = false;
    bool m_colorStarLines = false;
    bool m_extents = false;
    bool m_grid = false;

    QVector<Polygon> m_loadedPolygons;
    QVector<TreeNode> m_groomedPolygons;
    QVector<PieChart> m_pieGlyphs;
    QVector<StarGlyph> m_starGlyphs;
    QVector<WheelGlyph> m_wheelGlyphs;
    QVector<BarChart> m_barCharts;

    AABB m_originalWrapper;
    AABB m_currentWrapper;
    float length;
    float valueUpper;
    float valueLower;
    int glyphType = GLYPH_CENTROID;
    float glyphSize = 2.5f;

    QVector<TreeNode> m_transitionNeutral;
    QVector<TreeNode> m_transitionAdd;
    QVector<TreeNode> m_transitionRemove;
    QVector<TreeNode> m_gridStructure;
    QVector<bool> m_valueFilters;
    float currentTransitionSize = 0.0f;
    int transitionType = 1;
    float m_areaOpacity = 0.0f;
    float m_zoom = 0.0f;
    float m_currentScale = 0.0f;
    float translationX = 0.0f;
    float translationY = 0.0f;

    int m_hiddenIndicator = 0;
    bool m_indicatorMatches = false;

    int m_colorMap = 0;
    int m_advFilter = 0;

    QVector<float> m_means, m_maxes, m_mins;

    int m_clickedIndex = NEGATIVE_INDEX;

    int m_focusContextType = 0;

    QStringList dataHeaders;

    QPointF mouse;

    void prepareDraw();
    void setOrtho();

    void redraw();
    void drawPolygons(QVector<Polygon> list);
    void drawPolygons(QVector<TreeNode> *polyList);
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
    int findClickedIndex(QPointF coords, QVector<WheelGlyph> list);
    int findClickedIndex(QPointF coords, QVector<StarGlyph> list);
    int findClickedIndex(QPointF coords, QVector<BarChart> list);
    void drawPolygon(TreeNode polygon);
    void fillToolTip(int glyphIndex);
    QVector<StarGlyph> createStarGlyphs(QVector<TreeNode> list, int state);
    void calculateAbsoluteValueBounds(QVector<TreeNode> list);
    void drawStarGlyphs(QVector<StarGlyph> list, ColourManager cm);
    void calculateValueBounds(QVector<StarGlyph> list);
    QVector<WheelGlyph> createWheelGlyphs(QVector<TreeNode> list, int state);
    void calculateValueBounds(QVector<WheelGlyph> list);
    void drawWheelGlyphs(QVector<WheelGlyph> list, ColourManager cm);
    QVector<BarChart> createBarCharts(QVector<TreeNode> list, int state);
    void calculateValueBounds(QVector<BarChart> list);
    void drawBarCharts(QVector<BarChart> list, ColourManager cm);



};

#endif // CANVAS_H
