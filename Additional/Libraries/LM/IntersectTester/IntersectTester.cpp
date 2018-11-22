#include "IntersectTester.h"

bool IntersectTester::isIntersecting(Point a, Point b)
{
    return a.getX() == b.getX() &&
            a.getY() == b.getY() &&
            a.getZ() == b.getZ();
}


bool IntersectTester::isPointOnLineSegment( Point p, LineSegment ls)
{

    double crossproduct = crossProduct(p, ls.getStart(), ls.getEnd());

    if ( fabs( crossproduct ) >
            std::numeric_limits<float>::epsilon() )
        return false;

    double dotproduct = dotProduct( p, ls.getStart(), ls.getEnd() );
//            p.getX() - ls.getStart().getX() ) *
//                        ( ls.getEnd().getX() - ls.getStart().getX() ) +
//                        ( p.getY() - ls.getStart().getY() ) *
//                        ( ls.getEnd().getY() - ls.getStart().getY() );

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

bool IntersectTester::isPointOnCircle(Point p, Circle c)
{
    return distanceBetweenPoints(p,c.getCenter()) <= c.getRadius();
}

bool IntersectTester::isPointOnTriangle(Point p, Triangle t)
{
    Point t1 = t.getVertexOne(), t2 = t.getVertexTwo(), t3 = t.getVertexThree();

    if( isIntersecting(p,t1) || isIntersecting(p,t2) || isIntersecting(p,t3) )
        return true;

    if( !isIntersecting( p, AABB( std::min( std::min( t1.getX(),t2.getX() ), t3.getX() ),
                                 std::max( std::min( t1.getX(),t2.getX() ), t3.getX() ),
                                 std::min( std::min( t1.getY(),t2.getY() ), t3.getY() ),
                                 std::max( std::min( t1.getY(),t2.getY() ), t3.getY() ) ) ) )
            return false;

//    float crossP1 = crossProduct(p, t.getVertexOne(), t.getVertexTwo());
//    float crossP2 = crossProdcut(p, t.getVertexTwo(), t.getVertexThree());
//    float crossP3 = crossProduct(p, t.getVertexThree(), t.getVertexOne());

//    if(crossP1 > 0 && crossP2 > 0 && crossP3 > 0)
//        return true;
//    if(crossP1 < 0 && crossP2 < 0 && crossP3 < 0)
//        return true;
//    return false;

    float bary1 = ( (t2.getY() - t3.getY() ) * ( p.getX()-t3.getX() )
                  + ( t3.getX()-t2.getX() ) * ( p.getY()-t3.getY() ) /
                  ( t2.getY() - t3.getY() ) * ( t1.getX()-t3.getX() )
                  + ( t2.getX()-t1.getX() ) * ( t1.getY()-t3.getY() ) );

    float bary2 = ( (t3.getY() - t1.getY() ) * ( p.getX()-t3.getX() )
                  + ( t1.getX()-t3.getX() ) * ( p.getY()-t3.getY() ) /
                  ( t2.getY() - t3.getY() ) * ( t1.getX()-t3.getX() )
                  + ( t2.getX()-t1.getX() ) * ( t1.getY()-t3.getY() ) );
    float bary3 = 1 - bary1 - bary2;

    if (bary1 >= 0 && bary1 <= 1 &&
            bary2 >= 0 && bary2 <= 1 &&
            bary3 >= 0 && bary3 <= 1)
        return true;

    if( !isIntersecting( p, LineSegment(t1,t2) ) && !isIntersecting( p, LineSegment(t2,t3) ) && !isIntersecting( p, LineSegment(t3,t1) ) )
        return false;

    return true;

}

bool IntersectTester::isPointOnAABB( Point p, AABB a )
{
    AABB b(p.getX(),p.getX(),p.getY(),p.getY(), p.getZ(), p.getZ());
    return a.intersects(b);
}

bool IntersectTester::areLineSegmentsIntersecting(LineSegment a, LineSegment b)
{
    if( a.getStart().getZ() != a.getEnd().getZ() ||
         b.getStart().getZ() != b.getEnd().getZ() ) // 3D Plane Check
    {

    }
    else if ( a.getStart().getZ() == b.getStart().getZ())// 2D Plane Check
    {
        Point p1 = a.getStart(); Point p2 = a.getEnd();
        Point p3 = b.getStart(); Point p4 = b.getEnd();

        int or1, or2, or3, or4;
        or1 = direction( p1, p3, p2 );
        or2 = direction( p1, p3, p4 );
        or3 = direction( p2, p4, p1 );
        or4 = direction( p2, p4, p3 );

        if (or1 != or2 && or3 != or4 )
            return true;
        if( or1 == 0 && isIntersecting( p3, a ) )
            return true;
        if( or2 == 0 && isIntersecting( p1, b ) )
            return true;
        if( or3 == 0 && isIntersecting( p4, a ) )
            return true;
        if( or4 == 0 && isIntersecting( p2, b ) )
            return true;

        return false;
    }
    // else 2D Planes do not align
        return false;
}

bool IntersectTester::areLineSegmentAndCircleIntersecting(LineSegment a, Circle c)
{
    if( isIntersecting( a.getStart(), c.getCenter()) || isIntersecting(a.getEnd(), c) )
        return true;

    Point p1 = a.getStart();
    Point p2 = a.getEnd();

    float distX = p1.getX() - p2.getX();
    float distY = p1.getY() - p2.getY();
    float len = sqrt( (distX * distX ) + (distY * distY ) );
    float dot = dotProduct( c.getCenter(), p1, p2 ) / (len*len);

    float closestX = p1.getX() + ( dot * ( p2.getX() - p1.getX() ) );
    float closestY = p1.getY() + ( dot * ( p2.getY() - p1.getY() ) );

    if( !isIntersecting( Point( closestX, closestY ), a ) )
        return false;

    float distTest = distanceBetweenPoints( c.getCenter(),
                                            Point( closestX, closestY ) );

    if( distTest <= c.getRadius() )
        return true;

    return false;
}

bool IntersectTester::doesLineSegmentIntersectTriangle( LineSegment ls, Triangle t )
{
    if( isIntersecting( ls, LineSegment( t.getVertexOne(), t.getVertexTwo() ) )
     || isIntersecting( ls, LineSegment( t.getVertexTwo(), t.getVertexThree() ) )
     || isIntersecting( ls, LineSegment( t.getVertexThree(), t.getVertexOne() ) ) )
        return true;
    return false;
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


bool IntersectTester::doCirclesIntersect(Circle a, Circle b)
{
    return ( distanceBetweenPoints( a.getCenter(), b.getCenter() ) <=
             a.getRadius() + b.getRadius() );
}

bool IntersectTester::doesCircleIntersectTriangle(Circle c, Triangle t)
{
    Point A = t.getVertexOne();
    Point B = t.getVertexTwo();
    Point C = t.getVertexThree();

    if(!isIntersecting( c.getCenter(), t ) &&
       !isIntersecting( LineSegment( A, B ), c )&&
       !isIntersecting( LineSegment( B, C ), c )&&
       !isIntersecting( LineSegment( C, A ), c ) )
        return false;

    return true;
}

bool IntersectTester::doCircleandAABBIntersect(Circle c, AABB a)
{
    Point A(a.minimums[AABB::XDIM], a.minimums[AABB::YDIM]);
    Point B(a.minimums[AABB::XDIM], a.maximums[AABB::YDIM]);
    Point C(a.maximums[AABB::XDIM], a.minimums[AABB::YDIM]);
    Point D(a.maximums[AABB::XDIM], a.maximums[AABB::YDIM]);

    if(!isIntersecting( c.getCenter(), a ) &&
       !isIntersecting( LineSegment( A, B ), c )&&
       !isIntersecting( LineSegment( B, C ), c )&&
       !isIntersecting( LineSegment( C, D ), c )&&
       !isIntersecting( LineSegment( D, A ), c ) )
        return false;

    return true;
}


bool IntersectTester::doTrianglesIntersect(Triangle a, Triangle b)
{
    if( isIntersecting( LineSegment( a.getVertexOne(), a.getVertexTwo() ), b) ||
        isIntersecting( LineSegment( a.getVertexTwo(), a.getVertexThree() ), b) ||
        isIntersecting( LineSegment( a.getVertexThree(), a.getVertexOne() ), b) ||
        isIntersecting( LineSegment( b.getVertexOne(), b.getVertexTwo() ), a) ||
        isIntersecting( LineSegment( b.getVertexTwo(), b.getVertexThree() ), a) ||
        isIntersecting( LineSegment( b.getVertexThree(), b.getVertexOne() ), a) )
        return true;

    return false;
}

bool IntersectTester::doTriangleAndAABBIntersect(Triangle t, AABB a)
{
    Point A(a.minimums[AABB::XDIM], a.minimums[AABB::YDIM]);
    Point B(a.minimums[AABB::XDIM], a.maximums[AABB::YDIM]);
    Point C(a.maximums[AABB::XDIM], a.minimums[AABB::YDIM]);
    Point D(a.maximums[AABB::XDIM], a.maximums[AABB::YDIM]);

    if(isIntersecting( LineSegment( A, B ), t ) ||
       isIntersecting( LineSegment( B, C ), t ) ||
       isIntersecting( LineSegment( C, D ), t ) ||
       isIntersecting( LineSegment( D, A ), t ) )
        return true;

    return false;
}


bool IntersectTester::areBoxesIntersecting( AABB a, AABB b )
{
    return a.intersects(b);
}

float IntersectTester::distanceBetweenPoints(Point a, Point b)
{
    float squareX = (b.getX()-a.getX())*(b.getX()-a.getX());
    float squareY = (b.getY()-a.getY())*(b.getY()-a.getY());
    float answer = sqrt( squareX + squareY );

     return answer;
}

float IntersectTester::crossProduct(Point a, Point b, Point c)
{
    return ( a.getY() - b.getY() ) *
           ( c.getX() - b.getX() ) -
           ( a.getX() - b.getX() ) *
           ( c.getY() - b.getY() );
}

float IntersectTester::dotProduct(Point a, Point b, Point c)
{
    return ( ( a.getX() - b.getX() ) * (c.getX() - b.getX() ) ) +
           ( ( a.getY() - b.getY() ) * (c.getY() - b.getY() ) );
}

int IntersectTester::direction(Point a, Point b, Point c)
{
    float dir = ( b.getY() - a.getY() ) * ( c.getX() - b.getX() ) -
              ( b.getX() - a.getX() ) * ( c.getY() - b.getY() );

    if (dir == 0)
        return 0; //Colinear
    else if ( dir > 0 )
        return 1; //Clockwise

    return -1; //Anti-clockwise
}

