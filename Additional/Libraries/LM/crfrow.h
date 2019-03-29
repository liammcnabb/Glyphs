#ifndef LM_CRFROW_H
#define LM_CRFROW_H

#include <string>

class CrfRow
{
public:
    /**
     * @brief CrfRow Default Constructor
     */
    CrfRow();
    /**
     * @brief CrfRow full constructor to initialize all values in CrfRow
     * @param neighbourIndex Index of neighbor of merge candidate
     * @param pOneStartIndex start index of shared boundary for polygon one
     * @param pOneEndIndex end index of shared boundary for polygon one
     * @param pTwoStartIndex start index of shared boundary for polygon two
     * @param pTwoEndIndex end index of shared boundary for polygon two
     */
    CrfRow( int neighbourIndex, int pOneStartIndex, int pOneEndIndex,
               int pTwoStartIndex, int pTwoEndIndex );

    /**
     * @brief neighbourIndex getter method for neighbour index
     * @see CrfRow::CrfRow( int neighbourIndex, int pOneStartIndex, int pOneEndIndex,int pTwoStartIndex, int pTwoEndIndex );
     * @return neighbour's index
     */
    int neighbourIndex() const;
    /**
     * @brief setNeighbourIndex setter method for neighbour index
     * @see CrfRow::CrfRow( int neighbourIndex, int pOneStartIndex, int pOneEndIndex,int pTwoStartIndex, int pTwoEndIndex );
     * @param neighbourIndex new value for neighbour index
     */
    void setNeighbourIndex( int neighbourIndex );

    /**
     * @brief pOneStartIndex getter method for shared boundary's start index
     * in polygon one
     * @see CrfRow::CrfRow( int neighbourIndex, int pOneStartIndex, int pOneEndIndex,int pTwoStartIndex, int pTwoEndIndex );
     * @return start index for shared boundary in polygon one
     */
    int pOneStartIndex() const;
    /**
     * @brief setPOneStartIndex setter method for shared boundary's start index
     * in polygon one
     * @see CrfRow::CrfRow( int neighbourIndex, int pOneStartIndex, int pOneEndIndex,int pTwoStartIndex, int pTwoEndIndex );
     * @param pOneStartIndex
     */
    void setPOneStartIndex( int pOneStartIndex );

    /**
     * @brief pOneEndIndex getter method of shared boundary's end index in
     * polygon one
     * @see CrfRow::CrfRow( int neighbourIndex, int pOneStartIndex, int pOneEndIndex,int pTwoStartIndex, int pTwoEndIndex );
     * @return shared boundary's end index in polygon one
     */
    int pOneEndIndex() const;
    /**
     * @brief setPOneEndIndex setter method of shared boundary's end index in
     * polygon one
     * @see CrfRow::CrfRow( int neighbourIndex, int pOneStartIndex, int pOneEndIndex,int pTwoStartIndex, int pTwoEndIndex );
     * @param pOneEndIndex new value of shared boundary's end index in
     * polygon one
     */
    void setPOneEndIndex( int pOneEndIndex );

    /**
     * @brief pOneStartIndex getter method for shared boundary's start index
     * in polygon two
     * @see CrfRow::CrfRow( int neighbourIndex, int pOneStartIndex, int pOneEndIndex,int pTwoStartIndex, int pTwoEndIndex );
     * @return start index for shared boundary in polygon two
     */
    int pTwoStartIndex() const;
    /**
     * @brief setPOneStartIndex setter method for shared boundary's start index
     * in polygon two
     * @see CrfRow::CrfRow( int neighbourIndex, int pOneStartIndex, int pOneEndIndex,int pTwoStartIndex, int pTwoEndIndex );
     * @param pOneStartIndex
     */
    void setPTwoStartIndex( int pTwoStartIndex );

    /**
     * @brief pOneEndIndex getter method of shared boundary's end index in
     * polygon two
     * @see CrfRow::CrfRow( int neighbourIndex, int pOneStartIndex, int pOneEndIndex,int pTwoStartIndex, int pTwoEndIndex );
     * @return shared boundary's end index in polygon two
     */
    int pTwoEndIndex() const;
    /**
     * @brief setPOneEndIndex setter method of shared boundary's end index in
     * polygon two
     * @see CrfRow::CrfRow( int neighbourIndex, int pOneStartIndex, int pOneEndIndex,int pTwoStartIndex, int pTwoEndIndex );
     * @param pOneEndIndex new value of shared boundary's end index in
     * polygon two
     */
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
