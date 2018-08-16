#ifndef STARGLYPH_H
#define STARGLYPH_H

#include "glyph.h"

#include <QStringList>
#include <QVector>

class StarGlyph : public Glyph
{
public:
    StarGlyph();
    StarGlyph( QPointF centroid, float size );
    void initialize(QStringList values, float upperBound, float lowerBound);

    QVector<float> points() const;
    void setPoints(const QVector<float> &points);

    float size() const;
    void setSize(float size);

private:
    QVector<float> m_points;
    float m_size = 0.0f;
};

#endif // STARGLYPH_H
