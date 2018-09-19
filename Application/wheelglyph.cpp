#include "wheelglyph.h"

WheelGlyph::WheelGlyph() :
    Glyph( QPointF( 0.0f, 0.0f ), 0.0f, NEUTRAL, QPointF( 0.0f, 0.0f ) )
{ }

WheelGlyph::WheelGlyph(QPointF centroid, float size, int state, QPointF origin) :
    Glyph( centroid, size, state, origin )
{ }

float WheelGlyph::size() const
{
    return m_size;
}

void WheelGlyph::setSize(float size)
{
    m_size = size;
}

void WheelGlyph::initialize(QStringList values, QVector<float> means)
{
    QVector<float> points;
    float point;
    for( int i = 0; i < values.size(); ++i )
    {
        point = values.at(i).toFloat() - means.at(i);
        points.append(point);
    }
    setRads(points);
}

void WheelGlyph::initialize(QStringList values)
{
    QVector<float> points;
    float point;
    for( int i = 0; i < values.size(); ++i )
    {
        point = values.at(i).toFloat();
        points.append(point);
    }
    setRads(points);
}

QVector<float> WheelGlyph::getRads() const
{
    return rads;
}

void WheelGlyph::setRads(const QVector<float> &value)
{
    rads = value;
}

