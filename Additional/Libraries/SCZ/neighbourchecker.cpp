#include "neighbourchecker.h"

long NeighbourChecker::PL_counter = 0;
long NeighbourChecker::BB_counter = 0;

bool NeighbourChecker::isNeighbour( Polygon pOne, Polygon pTwo,
                                    int searchType )
{
    BB_counter++;
    if ( pOne.getBoundingBox().intersects( pTwo.getBoundingBox() ) )
        return commonVertices( pOne.getPoints(),
                               pTwo.getPoints(),
                               searchType );
    return false;
}

bool NeighbourChecker::isNeighbour( TreeNode pOne, int pTwo,
                                    LinkedList* list, int searchType )
{
    if ( pOne.getBoundingBox().intersects( list->at(
            pTwo )->getBoundingBox() ) )
        return commonVertices( pOne.fullBoundary(),
                               list->at( pTwo )->fullBoundary(), searchType );
    return false;
}


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

bool NeighbourChecker::isPointOnLine( QPointF point,
                                      QPointF linePointA,
                                      QPointF linePointB )
{
    PL_counter++;
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
    BB_counter++;
    return a.intersects( b );
}

int NeighbourChecker::next( QVector<QPointF> list, int index )
{
    if( index == list.size() - 1 )
        return 0;
    else
        return index + 1;
}
