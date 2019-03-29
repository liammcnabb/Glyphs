#ifndef NEIGHBOURCHECKER_H
#define NEIGHBOURCHECKER_H

#include "SCZ/treenode.h"
#include "SCZ/linkedlist.h"
//#include "global.h"
#include "LM/IntersectTester/AABB.h"

class NeighbourChecker
{
public:
    /**
     * @brief NeighbourChecker::isNeighbour checks if two polygons are neighbours
     * @param pOne polygon One
     * @param pTwo polygon Two
     * @param searchType type of search necessary (shallow search check for listed
     * points, deep checks all points against possible lines
     * @return true if neighbours, false otherwise
     */
    static bool isNeighbour( Polygon pOne, Polygon pTwo,
                             int searchType );
    /**
     * @brief NeighbourChecker::isNeighbour
     * @param pOne polygon one to check intersection of
     * @param pTwo index of polygon two in list (added for debug oppurtunity)
     * @param list List of all polygons
     * @param searchType type of search necessary (shallow search check for added
     * points, deep checks all points against possible lines
     * @return true if two polygons neighbour each other with at least two common
     * vertices
     */
    static bool isNeighbour( TreeNode pOne, int pTwo,
                             LinkedList* list, int searchType );
    /**
     * @brief NeighbourChecker::commonVertices checks whether there is a concrete
     * boundary. Variable counter constrains the points to have at least 2 distinct
     * bounds found (need at least two to be considered a neighbour). DEEP_SEARCH
     * checks each point to see if a point is found on the line of the neighbour.
     * This is important for simple boundaries (US counties) who may have 1 common
     * vertex, but 2 points on a line. Examples where deep search are necessary
     * drawn below.
     *
     *     *------------*            *-------------*
     *     |            |            |             |
     *     |            |            |             |
     *    [*]-----------*---[ ]      *-----[-]-----*------[ ]
     *     |                 |              |              |
     *     |                 |              |              |
     *    [ ]---------------[ ]            [ ]------------[ ]
     *
     * @param pOne First list of points
     * @param pTwo Second list of points
     * @param searchType refer to NeighbourChecker::isNeighbour( Polygon pOne, Polygon pTwo,
                                        int searchType )
     * @return true if enough common vertices found, false if otherwise.
     */
    static bool commonVertices( QVector<QPointF> pOne,
                                QVector<QPointF> pTwo,
                                int searchType );
    /**
     * @brief NeighbourChecker::isPointOnLine used to check whether a set of
     * coordinates intersects with on line (lastNeighbour to nextNeighbour)
     * @param point coordinate set to test
     * @param linePointA last neighbour to have a common vertex
     * @param linePointB the next vertex after the last common vertex
     * @return if point is on the line (lastNeighbour to nextNeighbour), return
     * true, otherwise return false.
     */
    static bool isPointOnLine( QPointF point, QPointF linePointA,
                               QPointF linePointB );
    /**
     * @brief isIntersecting checks if two AABB are intersecting. Used for
     * test incrementer
     * @param a AABB one
     * @param b AABB two
     * @return returns true is the two AABB intersect, false otherwise
     */
    static bool isIntersecting( AABB a, AABB b );

    /**
     * @brief next used to return next index considering list as a loop
     * @param list list to check
     * @param index current index to find next index of
     * @return next index considering list is looped
     */
    static int next(QVector<QPointF> list, int index);

    static const int NEIGHBOUR_MIN = 1;

    static long PL_counter;
    static long BB_counter;
};

#endif // NEIGHBOURCHECKER_H
