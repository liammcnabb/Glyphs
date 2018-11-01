#include "starglyph.h"

StarGlyph::StarGlyph() :
    Glyph ( QPointF( 0.0f, 0.0f ), 0.0f, NEUTRAL, QPointF( 0.0f, 0.0f ) )
{}

StarGlyph::StarGlyph(QPointF centroid, float size, int state, QPointF parent)
    : Glyph ( centroid, size, state, parent )
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

void StarGlyph::initialize(QStringList values, QVector<bool> filter)
{
    QVector<float> points;
    for( int i = 0; i < values.size(); ++i )
    {
        QVector<float> p;
        if(filter.at(i))
            points.append(values.at(i).toFloat());
        else
            points.append(p);
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
