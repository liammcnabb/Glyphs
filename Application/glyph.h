#ifndef GLYPH_H
#define GLYPH_H

#include <QPointF>

class Glyph
{
public:
    Glyph(QPointF centroid);
    QPointF centroid() const;
    void setCentroid(const QPointF &centroid);
private:
    QPointF m_centroid;
};

#endif // GLYPH_H
