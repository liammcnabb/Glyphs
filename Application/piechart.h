#ifndef PIECHART_H
#define PIECHART_H

#include <QPointF>
#include <QStringList>
#include "glyph.h"


class PieChart : public Glyph
{
public:
    PieChart(QPointF centroid, float size);
    void initialize(QStringList values);
    float size() const;
    void setSize(float size);

private:
    float m_size = 0.0f;
};

class PieSegment
{

public:
    float angle() const;
    void setAngle(float angle);
private:
    float m_angle = 1.0f;
};

#endif // PIECHART_H
