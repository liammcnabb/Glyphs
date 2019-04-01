#ifndef CONTIGUOUSAREA_H
#define CONTIGUOUSAREA_H

//#include "global.h"
#include <QDebug>
#include "polygon.h"
#include "LM/IntersectTester/AABB.h"
#include <QVector>


class ContiguousArea
{
public:
    /**
     * @brief ContiguousArea empty constructor
     */
    ContiguousArea();
    /**
     * @brief ContiguousArea copy constructor
     * @param obj obj to copy information from
     */
    ContiguousArea( const ContiguousArea& obj );
    /**
     * @brief operator = assignment operator
     * @param other object to assign data from
     * @return this object
     */
    ContiguousArea& operator=( const ContiguousArea& other );
    ~ContiguousArea();

    /**
     * @brief polygons getter method for list of polygons held by this
     * contiguous area
     * @return vector of polygons
     */
    QVector<Polygon>& polygons() const;
    /**
     * @brief setPolygons setter method for list of polygons held by this
     * contiguous area
     * @param polygons new set of polygons held by this contiguous areas
     */
    void setPolygons( QVector<Polygon>* polygons );
    /**
     * @brief initPolygons initializes the list of polygons and calls other
     * setup methods
     * @param input list of polygons to save to object
     * @return true if intialized successfully
     */
    bool initPolygons( QVector<Polygon> input );

    /**
     * @brief polygons method to access polygon at index 'value'
     * @param value index of polygon to return
     * @return polygon referred to
     */
    const Polygon& polygons( int value ) const;

    /**
     * @brief sortedIndexes getter method for sorted indexes of contiguous
     * polygons (default by area)
     * @return list of sorted indexes
     */
    QVector<int>& sortedIndexes() const;
    /**
     * @brief setSortedIndexes setter method for sorted indexes of contiguous
     * polygons (default by area)
     * @param sortedIndexes new list of sorted indexes
     */
    void setSortedIndexes( QVector<int>* sortedIndexes );

    /**
     * @brief initSortedIndexes method to initialize list of sorted indexes by
     * area
     * @return true if successful
     */
    bool initSortedIndexes() const;
    /**
     * @brief sortedByArea sorting list by area size using qsort
     * @return true if successful
     */
    bool sortedByArea();

    /**
     * @brief getBoundingBox getter method for contiguousarea bounding box
     * @return cointiguousarea bounding box
     */
    AABB getBoundingBox() const;
    /**
     * @brief setBoundingBox setter method for contiguousarea bounding box
     * @param boundingBox new contiguousarea bounding box
     */
    void setBoundingBox(const AABB &boundingBox);

private:
    QVector<Polygon>* m_polygons = NULL;
    QVector<int>* m_sortedIndexes = NULL;
    AABB m_boundingBox;

    /**
     * @brief setupAABB method used to verify the extents of the contiguousarea.
     * used to reduce the amount of AABB-AABB checks in the algorithm
     * @param list list of current areas in contiguous region.
     */
    void setupAABB(QVector<Polygon> *list);
};

#endif // CONTIGUOUSAREA_H
