#ifndef WHEELGLYPH_H
#define WHEELGLYPH_H

#include <QStringList>
#include <QVector>

#include "glyph.h"

class WheelGlyph : public Glyph
{
public:
    WheelGlyph();
    WheelGlyph( QPointF centroid, float size, int state );

    float size() const;
    void setSize(float size);

    void initialize(QStringList values);

    QVector<float> getRads() const;
    void setRads(const QVector<float> &value);

    void initialize(QStringList values, QVector<float> means);
private:
    float m_size = 0.0f;
    QVector<float> rads;
};

#endif // WHEELGLYPH_H
