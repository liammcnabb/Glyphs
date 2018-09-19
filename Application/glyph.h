#ifndef GLYPH_H
#define GLYPH_H

#include <QPointF>

class Glyph
{
public:
    static constexpr float SIZE_MODIFIER = 0.03;

    static const int NEUTRAL = 0;
    int REMOVE = -1;
    int ADD = 1;

    Glyph( QPointF centroid, float size, int state, QPointF origin );
    QPointF centroid() const;
    void setCentroid(const QPointF &centroid);

    int state() const;
    void setState(int state);

    float size() const;
    void setSize(float size);

    QPointF parent() const;
    void setParent(const QPointF &parent);

private:
    QPointF m_centroid;
    QPointF m_parent;
    float m_size = 0.0f;
    int m_state;

};

#endif // GLYPH_H
