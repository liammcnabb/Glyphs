#include "piechart.h"

PieChart::PieChart() : Glyph( QPointF( 0.0f,0.0f ) )
{
    setSize(1 * SIZE_MODIFIER);

}

PieChart::PieChart(QPointF centroid, float size) : Glyph( centroid )
{
    setSize( size * SIZE_MODIFIER );
}

void PieChart::initialize(QStringList values)
{
    switch(sliceType)
    {
        case EQUAL_SLICES :
        {
            createEqualSlices( values );
            break;
        }
        case FULL_SLICES :
        {
            createVariableSlices( values );
            break;
        }
    }

    return;
}

void PieChart::createVariableSlices( QStringList values )
{
    QVector<PieSegment> slices;

    float sum = 0;
    for ( int i = 0; i < values.size(); ++i )
        sum += values.at(i).toFloat();

    for( int i = 0; i < values.size(); ++i )
    {
        float percent = values.at(i).toFloat()/sum;
        float sliceAngle = (maxAngle())* percent;
        slices.append( PieSegment( sliceAngle, values.at(i).toFloat() ) );
    }

    setPieSlices(slices);
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

int PieChart::getSliceType() const
{
    return sliceType;
}

void PieChart::setSliceType(int value)
{
    sliceType = value;
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
