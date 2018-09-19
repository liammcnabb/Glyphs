#ifndef LEGENDCANVAS_H
#define LEGENDCANVAS_H

#include <QOpenGLWidget>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

#include "Spectrum/colourmanager.h"
#include "piechart.h"
#include "starglyph.h"
#include "wheelglyph.h"
#include "barchart.h"


class LegendCanvas : public QOpenGLWidget
{
public:
    static const int SAMPLE_POINTS = 6;
    static const int SEQUENTIAL = 0;
    static const int DIVERGING = 1;
    static const int CATEGORICAL = 2;
    static const int OUTLINE = 3;

    static const int GLYPH_CENTROID = 0;
    static const int GLYPH_EQUAL_PIE = 1;
    static const int GLYPH_VARIABLE_PIE = 2;
    static const int GLYPH_STAR = 3;
    static const int GLYPH_BAR = 4;

    LegendCanvas(QWidget *parent);
    void initializeGL();
    void paintGL();

    PieChart variablePie() const;
    void setVariablePie(const PieChart &VariablePie);

    void changeColorMap(int mapType);
    int currentGlyphType() const;
    void setCurrentGlyphType(int currentGlyphType);

    StarGlyph starGlyph() const;
    void setStarGlyph(const StarGlyph &starGlyph);

    WheelGlyph wheelGlyph() const;
    void setWheelGlyph(const WheelGlyph &wheelGlyph);

    bool colorStarLines() const;
    void setColorStarLines(bool colorStarLines);

    BarChart barChart() const;
    void setBarChart(const BarChart &barChart);

    QVector<float> means() const;
    void setMeans(const QVector<float> &means);

    QVector<float> maxes() const;
    void setMaxes(const QVector<float> &maxes);

    QVector<float> mins() const;
    void setMins(const QVector<float> &mins);

    void initializeLegend(QVector<float> averages);
    QStringList valueHeaders() const;
    void setValueHeaders(const QStringList &valueHeaders);

    void glPrintVerticalString(void *font, const char *str, float x, float y);
    void glPrintVerticalString(float x, float y, std::string str);
private:
    void initializeVariablePie(QVector<float> averages);
        void initializeBarChart(QVector<float> averages);
    void paintVariablePie();
    PieChart m_variablePie;
    StarGlyph m_starGlyph;
    WheelGlyph m_wheelGlyph;
    BarChart m_barChart;
    int m_currentGlyphType = 0;
    bool m_colorStarLines = false;

    QStringList m_valueHeaders;
    QVector<float> m_means, m_maxes, m_mins;

    void glPrintString(float x, float y, std::string str);
    void glPrintString(void *font, const char *str, float x, float y);
    void paintStarGlyph();
    void initalizeStarGlyph( QVector<float> averages);
    void paintWheelGlyph();
    void initalizeWheelGlyph(QVector<float> averages);
    void paintBarChart();
};

#endif // LEGENDCANVAS_H
