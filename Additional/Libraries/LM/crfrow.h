#ifndef LM_CRFROW_H
#define LM_CRFROW_H

#include <string>

class CrfRow
{
public:
    CrfRow();
    CrfRow( int neighbourIndex, int pOneStartIndex, int pOneEndIndex,
               int pTwoStartIndex, int pTwoEndIndex );

    int neighbourIndex() const;
    void setNeighbourIndex( int neighbourIndex );

    int pOneStartIndex() const;
    void setPOneStartIndex( int pOneStartIndex );

    int pOneEndIndex() const;
    void setPOneEndIndex( int pOneEndIndex );

    int pTwoStartIndex() const;
    void setPTwoStartIndex( int pTwoStartIndex );

    int pTwoEndIndex() const;
    void setPTwoEndIndex( int pTwoEndIndex );

    std::string toString();

private:
    int m_neighbourIndex = 0;
    int m_pOneStartIndex = 0;
    int m_pOneEndIndex = 0;
    int m_pTwoStartIndex = 0;
    int m_pTwoEndIndex = 0;
};

#endif // CSVROW_H
