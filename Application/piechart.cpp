#include "piechart.h"

PieChart::PieChart(QPointF centroid, float size) : Glyph( centroid )
{
    setSize( size );
}

void PieChart::initialize(QStringList values)
{
    int slices = values.size();
    return;
}

float PieChart::size() const
{
    return m_size;
}

void PieChart::setSize(float size)
{
    m_size = size;
}

float PieSegment::angle() const
{
    return m_angle;
}

void PieSegment::setAngle(float angle)
{
    m_angle = angle;
}
