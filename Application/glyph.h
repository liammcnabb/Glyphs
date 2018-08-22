#ifndef GLYPH_H
#define GLYPH_H

#include <QPointF>

class Glyph
{
public:
    static constexpr float SIZE_MODIFIER = 0.03;

    int NEUTRAL = 0;
    int REMOVE = -1;
    int ADD = 1;

    Glyph( QPointF centroid, int state );
    QPointF centroid() const;
    void setCentroid(const QPointF &centroid);

    int state() const;
    void setState(int state);

private:
    QPointF m_centroid;
    float m_size;
    int m_state;
};

#endif // GLYPH_H
