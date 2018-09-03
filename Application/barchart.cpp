#include "barchart.h"

BarChart::BarChart() : Glyph ( QPointF( 0.0f, 0.0f ), 0.0f, NEUTRAL )
{ }

BarChart::BarChart(QPointF centroid, float size, int state)
    : Glyph ( centroid, size, state )
{ }

void BarChart::initialize(QStringList list)
{
    QVector<float> floated;
    for( int i = 0; i < list.size(); ++i )
        floated.append( list.at(i).toFloat() );

    setValues(floated);
    return;
}



QVector<float> BarChart::values() const
{
    return m_values;
}

void BarChart::setValues(const QVector<float> &values)
{
    m_values = values;
}

