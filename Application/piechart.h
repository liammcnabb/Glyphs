#ifndef PIECHART_H
#define PIECHART_H

#include <QPointF>
#include <QStringList>
#include <QVector>
#include <cmath>

#include "glyph.h"

class PieSegment
{

public:
    PieSegment();
    PieSegment(float angle, float value);
    float angle() const;
    void setAngle(float angle);

    float value() const;
    void setValue(float value);\

private:
    float m_angle = 1.0f;
    float m_value = 0.0f;
};

class PieChart : public Glyph
{
public:
    static constexpr float SIZE_MODIFIER = 0.03;
    static const int FULL_SLICES = 0;
    static const int EQUAL_SLICES = 1;

    PieChart();
    PieChart(QPointF centroid, float size);
    void initialize(QStringList values);
    float size() const;
    void setSize(float size);

    float maxAngle() const;
    void setMaxAngle(float maxAngle);

    QVector<PieSegment> pieSlices() const;
    void setPieSlices(const QVector<PieSegment> &pieSlices);

    int getSliceType() const;
    void setSliceType(int value);

private:


    float m_size = 0.0f;
    float m_maxAngle = 2*M_PI;
    int sliceType = FULL_SLICES;

    QVector<PieSegment> m_pieSlices;

    void createEqualSlices(QStringList values);
    void createVariableSlices(QStringList values);
};

#endif // PIECHART_H
