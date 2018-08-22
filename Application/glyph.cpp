#include "glyph.h"

Glyph::Glyph(QPointF centroid , int state)
{
    setCentroid( centroid );
    setState( state );
}

QPointF Glyph::centroid() const
{
    return m_centroid;
}

void Glyph::setCentroid(const QPointF &centroid)
{
    m_centroid = centroid;
}

int Glyph::state() const
{
    return m_state;
}

void Glyph::setState(int state)
{
    m_state = state;
}
