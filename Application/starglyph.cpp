#include "starglyph.h"

StarGlyph::StarGlyph() : Glyph ( QPointF( 0.0f, 0.0f ), 0.0f, NEUTRAL )
{}

StarGlyph::StarGlyph(QPointF centroid, float size, int state)
    : Glyph ( centroid, size, state )
{}


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

void StarGlyph::initialize(QStringList values)
{
    QVector<float> points;
    for( int i = 0; i < values.size(); ++i )
        points.append(values.at(i).toFloat());

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
