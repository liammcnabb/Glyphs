#include "piechart.h"

PieChart::PieChart() : Glyph( QPointF( 0.0f,0.0f ) )
{
    setSize(2.5f);
}

PieChart::PieChart(QPointF centroid, float size) : Glyph( centroid )
{
    setSize( size );
}

void PieChart::initialize(QStringList values)
{
    switch(sliceType)
    {
        case EQUAL_SLICES :
        {
            createEqualSlices( values );
        }
        case FULL_SLICES :
        {

        }
    }

    return;
}

void PieChart::createEqualSlices( QStringList values )
{
    QVector<PieSegment> slices;
    float sliceAngle = (maxAngle())/ values.size();

    for( int i = 0; i < values.size(); ++i )
        slices.append( PieSegment( sliceAngle, values.at(i).toFloat() ) );

    setPieSlices(slices);
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

float PieChart::maxAngle() const
{
    return m_maxAngle;
}

void PieChart::setMaxAngle(float maxAngle)
{
    m_maxAngle = maxAngle;
}

QVector<PieSegment> PieChart::pieSlices() const
{
    return m_pieSlices;
}

void PieChart::setPieSlices(const QVector<PieSegment> &pieSlices)
{
    m_pieSlices = pieSlices;
}

float PieSegment::angle() const
{
    return m_angle;
}

void PieSegment::setAngle(float angle)
{
    m_angle = angle;
}

float PieSegment::value() const
{
    return m_value;
}

void PieSegment::setValue(float value)
{
    m_value = value;
}

PieSegment::PieSegment()
{
    setAngle(1.0f);
    setValue(0.0f);
}

PieSegment::PieSegment(float angle, float value)
{
    setAngle(angle);
    setValue(value);
}
