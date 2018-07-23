#ifndef PIECHART_H
#define PIECHART_H

#include <QPointF>
#include <QStringList>
#include "glyph.h"


class PieChart : public Glyph
{
public:
    PieChart(QPointF centroid);
    void initialize(QStringList values);
};

#endif // PIECHART_H
