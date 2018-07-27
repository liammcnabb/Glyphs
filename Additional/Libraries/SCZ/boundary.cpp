#include "boundary.h"

Boundary::Boundary()
{
    this->setStartIndex( DEFAULT_INDEX );
    this->setEndIndex( DEFAULT_INDEX );
    m_Boundary = new QVector<QPointF>();
}

Boundary::Boundary( const Boundary& boundary )
{
    this->setStartIndex( boundary.getStartIndex() );
    this->setEndIndex( boundary.getEndIndex() );
    m_Boundary = new QVector<QPointF>( boundary.getBoundary() );
}

Boundary::Boundary( QVector<QPointF> points )
{
    this->setStartIndex( DEFAULT_INDEX );
    this->setEndIndex( DEFAULT_INDEX );
    m_Boundary = new QVector<QPointF>( points );
}

Boundary::~Boundary()
{
    delete m_Boundary;
}

Boundary& Boundary::operator=( const Boundary& b )
{
    if ( this == &b )
        return *this;

    this->setStartIndex( b.getStartIndex() );
    this->setEndIndex( b.getEndIndex() );

    m_Boundary->resize( b.getBoundary().size() );
    std::copy( b.getBoundary().begin(), b.getBoundary().end(),
               m_Boundary->begin() );

    return *this;
}

int Boundary::boundarySize()
{
    return getBoundary().size();
}

int Boundary::getStartIndex() const
{
    return startIndex;
}

void Boundary::setStartIndex( int value )
{
    startIndex = value;
}

int Boundary::getEndIndex() const
{
    return endIndex;
}

void Boundary::setEndIndex( int value )
{
    endIndex = value;
}

QVector<QPointF>& Boundary::getBoundary() const
{
    return *m_Boundary;
}

void Boundary::setBoundary( QVector<QPointF>* boundary )
{
    m_Boundary = boundary;
}

int Boundary::previous( int index )
{
    if ( index - 1 < 0 )
        return boundarySize() - 1;
    else
        return index - 1;
}

int Boundary::next( int index )
{
    if ( index + 1 >= boundarySize() )
        return 0;
    else
        return index + 1;
}
