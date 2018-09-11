#ifndef STARGLYPH_H
#define STARGLYPH_H

#include "glyph.h"

#include <QStringList>
#include <QVector>

class StarGlyph : public Glyph
{
public:
    StarGlyph();
    StarGlyph( QPointF centroid, float size, int state );
    void initialize(QStringList values, float upperBound, float lowerBound);
    void initialize(QStringList values, QVector<float> means);

    QVector<float> points() const;
    void setPoints(const QVector<float> &points);


private:
    QVector<float> m_points;
};

#endif // STARGLYPH_H
