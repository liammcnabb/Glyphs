    #ifndef BOUNDARY_H
#define BOUNDARY_H

//#include "global.h"
#include <QVector>
#include <QPointF>


class Boundary
{
public:
    static const int DEFAULT_INDEX = -1;
    /**
     * @brief Boundary Default Constructor
     * Default parameters set both the start and end indexes of the boundary
     * (if taken from a larger boundary) to -1, and an empty vector of QPointF
     */
    Boundary();
    /**
     * @brief Boundary A constructor when only the boundary is relevent
     * Default parameters set both the start and end indexes of the boundary
     * (if taken from a larger boundary) to -1
     * @param points points representing the boundary
     */
    Boundary( QVector<QPointF> points );
    /**
     * @brief Boundary Copy constructor for boundary
     * @param boundary boundary to replicate.
     */
    Boundary( const Boundary& boundary );
    /** Destructor
      *
      */
    ~Boundary();
    /**
     * @brief operator = assignment of boundary
     * @param b Boundary to assign
     * @return the assigned boundary
     */
    Boundary& operator=( const Boundary& b );
    /**
     * @brief getStartIndex getter method for start index refers where a
     * boundary sits in the contexts of a larger boundary. Useful when
     * splitting a boundary to hold important detail
     * @return int value representing start index of a pre-existing boundary
     */
    int getStartIndex() const;
    /**
     * @brief setStartIndex setter method or start index refers where a
     * boundary sits in the contexts of a larger boundary. Useful when
     * splitting a boundary to hold important detail
     * @param value new index representing start value
     */
    void setStartIndex( int value );
    /**
     * @brief getEndIndex getter method end index refers where a boundary sits
     * in the contexts of a larger boundary. Useful when splitting a boundary
     * to hold important detail
     * @return int value representing end index of a pre-existing boundary
     */
    int getEndIndex() const;
    /**
     * @brief setEndIndex setter method or end index refers where a
     * boundary sits in the contexts of a larger boundary. Useful when
     * splitting a boundary to hold important detail
     * @param value new index representing end value
     */
    void setEndIndex( int value );
    /**
     * @brief getBoundary getter method for vector of points representing a
     * boundary
     * @return vector of points
     */
    QVector<QPointF>& getBoundary() const;
    /**
     * @brief setBoundary setter method for vector of points representing a
     * boundary
     * @param boundary new boundary
     */
    void setBoundary( QVector<QPointF>* boundary );
    /**
     * @brief previous simple method to quickly consider the boundary as a loop.
     * If we are at the beginning of a list, we move to the end of the list.
     * @param index current index
     * @return previous index (in the context of a looped list)
     */
    int previous( int index );
    /**
     * @brief next simple method to quickly consider the boundary as a loop.
     * If we are at the end of a list, we move to the beginning of the list.
     * @param index current index
     * @return next index (in the context of a looped list)
     */
    int next( int index );
    /**
     * @brief boundarySize returns the boundary size
     * @return boundary size
     */
    int boundarySize();
private:
    int startIndex;
    int endIndex;
    QVector<QPointF>* m_Boundary = NULL;
};

#endif // BOUNDARY_H
