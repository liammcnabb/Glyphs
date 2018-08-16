#ifndef GLYPH_H
#define GLYPH_H

#include <QPointF>

class Glyph
{
public:
    static constexpr float SIZE_MODIFIER = 0.03;
    Glyph( QPointF centroid );
    QPointF centroid() const;
    void setCentroid(const QPointF &centroid);


private:
    QPointF m_centroid;
    float m_size;
};

#endif // GLYPH_H
