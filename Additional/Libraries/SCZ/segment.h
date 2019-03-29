#ifndef SEGMENT_H
#define SEGMENT_H

class Segment
{
public:
    /**
     * @brief Segment Default Constructor. A segment of the dynamic choropleth
     * map algorithm. The method held more value in early construction, but was
     * left in order to ease redundancy
     */
    Segment();
    /**
     * @brief Segment constructor initializing default search type
     * @param searchType
     */
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
