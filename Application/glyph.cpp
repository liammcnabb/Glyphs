#include "glyph.h"

Glyph::Glyph( QPointF centroid )
{
    setCentroid( centroid );
}

QPointF Glyph::centroid() const
{
    return m_centroid;
}

void Glyph::setCentroid(const QPointF &centroid)
{
    m_centroid = centroid;
}
