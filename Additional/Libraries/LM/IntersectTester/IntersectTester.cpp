#include "IntersectTester.h"

bool IntersectTester::isPointOnLineSegment( Point p, LineSegment ls)
{
    double crossproduct = ( p.getY() - ls.getStart().getY() ) *
                          ( ls.getEnd().getX() - ls.getStart().getX() ) -
                          ( p.getX() - ls.getStart().getX() ) *
                          ( ls.getEnd().getY() - ls.getStart().getY() );

    if ( fabs( crossproduct ) >
            std::numeric_limits<float>::epsilon() )
        return false;

    double dotproduct = ( p.getX() - ls.getStart().getX() ) *
                        ( ls.getEnd().getX() - ls.getStart().getX() ) +
                        ( p.getY() - ls.getStart().getY() ) *
                        ( ls.getEnd().getY() - ls.getStart().getY() );

    if ( dotproduct < 0 )
        return false;

    double squaredlengthba = ( ls.getEnd().getX() - ls.getStart().getX() ) *
                             ( ls.getEnd().getX() - ls.getStart().getX() ) +
                             ( ls.getEnd().getY() - ls.getStart().getY() ) *
                             ( ls.getEnd().getY() - ls.getStart().getY() );

    if ( dotproduct > squaredlengthba )
        return false;

    return true;
}

bool IntersectTester::areLineSegmentsIntersecting(LineSegment a, LineSegment b)
{
    if( a.getStart().getZ() != a.getEnd().getZ() ||
         b.getStart().getZ() != b.getEnd().getZ() ) // 3D Plane Check
    {

    }
    else if ( a.getStart().getZ() == b.getStart().getZ())// 2D Plane Check
    {

    }
    else // 2D Planes do not align
        return false;
}

bool IntersectTester::doLineAndTriangleIntersect(Line l, Triangle t)
{

}

bool IntersectTester::isPointOnCircle(Point p, Circle c)
{
    if(distanceBetweenPoints(p,c.getCenter()) < c.getRadius())
    {
        qDebug() << c.getRadius();
        return true;
    }

    return false;
}

float IntersectTester::distanceBetweenPoints(Point a, Point b)
{
    float squareX = (b.getX()-a.getX())*(b.getX()-a.getX());
    float squareY = (b.getY()-a.getY())*(b.getY()-a.getY());
    float answer = sqrt( squareX + squareY );

    qDebug() << answer;
     return answer;
}

bool IntersectTester::isPointOnAABB( Point p, AABB a )
{
    AABB b(p.getX(),p.getX(),p.getY(),p.getY(), p.getZ(), p.getZ());
    return a.intersects(b);
}

bool IntersectTester::doesLineSegmentIntersectAABB(LineSegment ls, AABB a )
{
    float minX, maxX, minY, maxY;
    minX = std::min( ls.getStart().getX(), ls.getEnd().getX() );
    minY = std::min( ls.getStart().getY(), ls.getEnd().getY() );
    maxX = std::max( ls.getStart().getX(), ls.getEnd().getX() );
    maxY = std::max( ls.getStart().getY(), ls.getEnd().getY() );
    AABB b( minX, maxX, minY, maxY );
    return a.intersects(b);
}

bool IntersectTester::areBoxesIntersecting( AABB a, AABB b )
{
    return a.intersects(b);
}
