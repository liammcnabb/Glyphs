#include "piechart.h"

PieChart::PieChart() :
    Glyph( QPointF( 0.0f,0.0f ), 0.0f, 0, QPointF( 0.0f, 0.0f ) )
{
    setSize(1 * SIZE_MODIFIER);

}

PieChart::PieChart(QPointF centroid, float size, int state, QPointF parent) :
    Glyph( centroid, size,  state, parent )
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

void PieChart::initialize(QStringList values, QVector<bool> filters)
{
    createVariableSlices( values, filters );
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

void PieChart::createVariableSlices( QStringList values, QVector<bool> filters )
{
    QVector<PieSegment> slices;

    float sum = 0;
    for ( int i = 0; i < values.size(); ++i )
        if (filters.at(i))
            sum += values.at(i).toFloat();

    for( int i = 0; i < values.size(); ++i )
    {
        PieSegment p;
        p.setIndex(i);
        float percent = 0;
        if(filters.at(i))
        {
            percent = values.at(i).toFloat()/sum;
            p.setAngle(maxAngle()* percent);
            p.setValue(values.at(i).toFloat());

        }

        slices.append( p );
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

int PieSegment::getIndex() const
{
    return index;
}

void PieSegment::setIndex(int value)
{
    index = value;
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
