#include "glyph.h"

Glyph::Glyph(QPointF centroid , float size, int state)
{
    setCentroid( centroid );
    setState( state );
    setSize(size * SIZE_MODIFIER);
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

float Glyph::size() const
{
    return m_size;
}

void Glyph::setSize(float size)
{
    m_size = size;
}
