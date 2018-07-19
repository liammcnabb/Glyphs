#include "segment.h"

Segment::Segment()
{

}

Segment::Segment( int searchType)
{
    setSearchType( searchType );

}

int Segment::searchType() const
{
    return m_searchType;
}

void Segment::setSearchType( int searchType )
{
    m_searchType = searchType;
}
