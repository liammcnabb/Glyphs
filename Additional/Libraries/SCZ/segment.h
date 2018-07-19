#ifndef SEGMENT_H
#define SEGMENT_H

class Segment
{
public:
    Segment();
    Segment( int searchType );

    /**
     * @brief searchType refers to the search type to be initiated during a
     * commonVertices check. Refer to NeighbourChecker::isNeighbour( Polygon pone, Polygon pTwo, int searchType).
     * @return returns search type indicator
     */
    int searchType() const;

    /**
     * @brief setSearchType used to set a new search type indicator
     * @param searchType new searchType indicator
     */
    void setSearchType( int searchType );


private:
    int m_searchType = 0;
};

#endif // SEGMENT_H
