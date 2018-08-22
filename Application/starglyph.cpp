#include "starglyph.h"

StarGlyph::StarGlyph() : Glyph ( QPointF( 0.0f, 0.0f ), NEUTRAL )
{
    setSize( 1 * SIZE_MODIFIER);
}

StarGlyph::StarGlyph(QPointF centroid, float size) : Glyph ( centroid, NEUTRAL )
{
    setSize( size * SIZE_MODIFIER);
}


void StarGlyph::initialize(QStringList values, float upperBound,
                           float lowerBound)
{
    QVector<float> points;
    float valueBound = upperBound - lowerBound;
    float point;
    for( int i = 0; i < values.size(); ++i )
    {
        point = (values.at(i).toFloat() -lowerBound) / valueBound  ;
        points.append(point);
    }
    setPoints(points);
}

void StarGlyph::initialize(QStringList values, QVector<float> means)
{
    QVector<float> points;
    float point;
    for( int i = 0; i < values.size(); ++i )
    {
        point = values.at(i).toFloat() - means.at(i);
        points.append(point);
    }
    setPoints(points);
}

QVector<float> StarGlyph::points() const
{
    return m_points;
}

void StarGlyph::setPoints(const QVector<float> &points)
{
    m_points = points;
}

float StarGlyph::size() const
{
    return m_size;
}

void StarGlyph::setSize(float size)
{
    m_size = size;
}
