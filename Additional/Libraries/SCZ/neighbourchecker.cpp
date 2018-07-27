#include "neighbourchecker.h"

/**
 * @brief NeighbourChecker::isNeighbour checks if two polygons are neighbours
 * @param pOne polygon One
 * @param pTwo polygon Two
 * @param searchType type of search necessary (shallow search check for listed
 * points, deep checks all points against possible lines
 * @return true if neighbours, false otherwise
 */
bool NeighbourChecker::isNeighbour( Polygon pOne, Polygon pTwo,
                                    int searchType )
{
    if ( pOne.getBoundingBox().intersects( pTwo.getBoundingBox() ) )
        return commonVertices( pOne.getPoints(),
                               pTwo.getPoints(),
                               searchType );
    return false;
}

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
bool NeighbourChecker::isNeighbour( TreeNode pOne, int pTwo,
                                    LinkedList* list, int searchType )
{
    if ( pOne.getBoundingBox().intersects( list->at(
            pTwo )->getBoundingBox() ) )
        return commonVertices( pOne.fullBoundary(),
                               list->at( pTwo )->fullBoundary(), searchType );
    return false;
}

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
bool NeighbourChecker::commonVertices( QVector<QPointF> pOne,
                                       QVector<QPointF> pTwo,
                                       int searchType )
{
    int counter = 0;
    QPointF lastCommon;
    QPointF nextCommon;
    QVector<QPointF> common;

    if( pOne.first() != pOne.last() &&
            pTwo.contains( pOne.first() ) )
    {
        counter++;
        common.append( pOne.first() );

    }

    switch( searchType )
    {
        case 0:
            for( int i = 1; i < pOne.size(); ++i )
            {
                if( pOne.at( i ) != pOne.at( i - 1 ) )
                {
                    if ( ( pTwo.contains( pOne.at( i ) ) ) &&
                            !common.contains( pOne.at( i ) )  )
                    {
                        counter++;
                        common.append( pOne.at( i ) );
                        int index = pTwo.indexOf( pOne.at( i ) );
                        lastCommon = pTwo.at( index );
                        nextCommon = pTwo.at( next( pTwo,
                                                            index ) );

                        while ( lastCommon == nextCommon )
                        {
                            index = index + 1;
                            lastCommon = pTwo.at( index );
                            nextCommon = pTwo.at( next( pTwo,
                                                                index ) );
                        }
                    }
                    else if ( !lastCommon.isNull() && !nextCommon.isNull() &&
                              isPointOnLine( pOne.at( i ), lastCommon,
                                             nextCommon ) &&
                              !common.contains( pOne.at( i ) ) )
                    {
                        counter++;
                        common.append( pOne.at( i ) );
                    }

                    if ( counter > NEIGHBOUR_MIN )
                        return true;
                }
            }

            return false;

        case 1:
            for( int i = 1; i < pOne.size(); ++i )
            {
                if( pOne.at( i ) != pOne.at( i - 1 ) &&
                        pTwo.contains( pOne.at( i ) ) &&
                        !common.contains( pOne.at( i ) ) )
                {
                    counter++;
                    common.append( pOne.at( i ) );
                }

                if ( counter > NEIGHBOUR_MIN )
                    return true;
            }

            return false;
    }
    return false;
}

/**
 * @brief NeighbourChecker::isPointOnLine used to check whether a set of
 * coordinates intersects with on line (lastNeighbour to nextNeighbour)
 * @param point coordinate set to test
 * @param linePointA last neighbour to have a common vertex
 * @param linePointB the next vertex after the last common vertex
 * @return if point is on the line (lastNeighbour to nextNeighbour), return
 * true, otherwise return false.
 */
bool NeighbourChecker::isPointOnLine( QPointF point,
                                      QPointF linePointA,
                                      QPointF linePointB )
{
    QPointF a = linePointA;
    QPointF b = linePointB;
    QPointF c = point;

    double crossproduct = ( c.y() - a.y() ) *
                          ( b.x() - a.x() ) -
                          ( c.x() - a.x() ) *
                          ( b.y() - a.y() );

    if ( fabs( crossproduct ) >
            std::numeric_limits<float>::epsilon() )
        return false;

    double dotproduct = ( c.x() - a.x() ) *
                        ( b.x() - a.x() ) +
                        ( c.y() - a.y() ) *
                        ( b.y() - a.y() );

    if ( dotproduct < 0 )
        return false;

    double squaredlengthba = ( b.x() - a.x() ) *
                             ( b.x() - a.x() ) +
                             ( b.y() - a.y() ) *
                             ( b.y() - a.y() );

    if ( dotproduct > squaredlengthba )
        return false;

    return true;
}

bool NeighbourChecker::isIntersecting(AABB a, AABB b )
{
    return a.intersects( b );
}

int NeighbourChecker::next( QVector<QPointF> list, int index )
{
    if( index == list.size() - 1 )
        return 0;
    else
        return index + 1;
}
