#include "glyph.h"

Glyph::Glyph(QPointF centroid , float size, int state, QPointF origin)
{
    setCentroid( centroid );
    setState( state );
    setSize(size);
    setParent( origin );
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

QPointF Glyph::parent() const
{
    return m_parent;
}

void Glyph::setParent(const QPointF &parent)
{
    m_parent = parent;
}

float Glyph::r() const
{
    return m_r;
}

void Glyph::setR(float r)
{
    m_r = r;
}

float Glyph::g() const
{
    return m_g;
}

void Glyph::setG(float g)
{
    m_g = g;
}

float Glyph::b() const
{
    return m_b;
}

void Glyph::setB(float b)
{
    m_b = b;
}
