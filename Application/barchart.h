#ifndef BARCHART_H
#define BARCHART_H

#include <QVector>
#include <QPointF>
#include <QStringList>
#include <QDebug>

#include "glyph.h"

class BarChart : public Glyph
{
public:
    BarChart();
    BarChart(QPointF centroid, float size, int state, QPointF parent);
    void initialize(QStringList list);

    QVector<float> values() const;
    void setValues(const QVector<float> &values);

private:
    QVector<float> m_values;
};

#endif // BARCHART_H
