#include "crfrow.h"

CrfRow::CrfRow()
{

}

CrfRow::CrfRow( int neighbourIndex, int pOneStartIndex,
                      int pOneEndIndex, int pTwoStartIndex,
                      int pTwoEndIndex )
{
    setNeighbourIndex( neighbourIndex );
    setPOneStartIndex( pOneStartIndex );
    setPOneEndIndex( pOneEndIndex );
    setPTwoStartIndex( pTwoStartIndex );
    setPTwoEndIndex( pTwoEndIndex );
}

int CrfRow::neighbourIndex() const
{
    return m_neighbourIndex;
}

void CrfRow::setNeighbourIndex( int neighbourIndex )
{
    m_neighbourIndex = neighbourIndex;
}

int CrfRow::pOneStartIndex() const
{
    return m_pOneStartIndex;
}

void CrfRow::setPOneStartIndex( int pOneStartIndex )
{
    m_pOneStartIndex = pOneStartIndex;
}

int CrfRow::pOneEndIndex() const
{
    return m_pOneEndIndex;
}

void CrfRow::setPOneEndIndex( int pOneEndIndex )
{
    m_pOneEndIndex = pOneEndIndex;
}

int CrfRow::pTwoStartIndex() const
{
    return m_pTwoStartIndex;
}

void CrfRow::setPTwoStartIndex( int pTwoStartIndex )
{
    m_pTwoStartIndex = pTwoStartIndex;
}

int CrfRow::pTwoEndIndex() const
{
    return m_pTwoEndIndex;
}

void CrfRow::setPTwoEndIndex( int pTwoEndIndex )
{
    m_pTwoEndIndex = pTwoEndIndex;
}

std::string CrfRow::toString()
{
    return "NI=" + std::to_string( neighbourIndex() ) + " P1S=" +
           std::to_string( pOneStartIndex() ) + " P1E=" +
           std::to_string( pOneEndIndex() ) + " P2S=" +
           std::to_string( pTwoStartIndex() ) + " P2E=" +
           std::to_string( pTwoEndIndex() ) + "\n";
}
