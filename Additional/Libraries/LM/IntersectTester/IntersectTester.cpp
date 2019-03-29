#include "IntersectTester.h"

float IntersectTester::tolerance = std::numeric_limits<float>::epsilon();




bool IntersectTester::isPointOnLineSegment( Point p, LineSegment ls)
{
 if(isIntersecting(p,ls.getStart()) || isIntersecting(p,ls.getEnd()))
     return true;

 Point closest = closestPoint(ls, p);
 float distance = distanceBetweenPoints(closest, p);
 AABB box(std::min(ls.getStart().getX(), ls.getEnd().getX()),
      std::max(ls.getStart().getX(), ls.getEnd().getX()),
      std::min(ls.getStart().getY(), ls.getEnd().getY()),
      std::max(ls.getStart().getY(), ls.getEnd().getY()));
 if( distance < tolerance &&
     isIntersecting(closest, box) )
     return true;

    return false;
}

bool IntersectTester::isPointOnLineSegmentOld(Point p, LineSegment ls)
{

        double crossproduct = crossProduct(p, ls.getStart(), ls.getEnd());

        if ( fabs( crossproduct ) >
                std::numeric_limits<float>::epsilon() )
            return false;

        double dotproduct = dotProduct( p, ls.getStart(), ls.getEnd() );

        if ( dotproduct < 0 )
            return false;

        double squaredlengthba = ( ls.getEnd().getX() - ls.getStart().getX() ) *
                                 ( ls.getEnd().getX() - ls.getStart().getX() ) +
                                 ( ls.getEnd().getY() - ls.getStart().getY() ) *
                                 ( ls.getEnd().getY() - ls.getStart().getY() );

        if ( dotproduct > squaredlengthba )
            return false;

        return true;

        float a = ls.getEnd().getY() - ls.getStart().getY() /
                  ls.getEnd().getX() - ls.getEnd().getX();
        float b = ls.getStart().getY() - a * ls.getStart().getX();
        if( fabs(p.getY() - (a*p.getX()+b)) < tolerance )
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
                                 std::max( std::max( t1.getX(),t2.getX() ), t3.getX() ),
                                 std::min( std::min( t1.getY(),t2.getY() ), t3.getY() ),
                                 std::max( std::max( t1.getY(),t2.getY() ), t3.getY() ) ) ) )
            return false;

    float crossP1 = crossProduct(p, t.getVertexOne(), t.getVertexTwo());
    float crossP2 = crossProduct(p, t.getVertexTwo(), t.getVertexThree());
    float crossP3 = crossProduct(p, t.getVertexThree(), t.getVertexOne());

    if(crossP1 > 0 && crossP2 > 0 && crossP3 > 0)
        return true;
    if(crossP1 < 0 && crossP2 < 0 && crossP3 < 0)
        return true;

    if( !isIntersecting( p, LineSegment(t1,t2) ) &&
        !isIntersecting( p, LineSegment(t2,t3) ) &&
        !isIntersecting( p, LineSegment(t3,t1) ) )
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
    int or1, or2, or3, or4;
    or1 = direction( a.getStart(), a.getEnd(), b.getStart() );
    or2 = direction( a.getStart(), a.getEnd(), b.getEnd() );
    or3 = direction( b.getStart(), b.getEnd(), a.getStart() );
    or4 = direction( b.getStart(), b.getEnd(), a.getEnd() );

    if (or1 != or2 && or3 != or4 )
        return true;
    if( or1 == 0 && isIntersecting( b.getStart(), a ) )
        return true;
    if( or2 == 0 && isIntersecting( a.getStart(), b ) )
        return true;
    if( or3 == 0 && isIntersecting( b.getEnd(), a ) )
        return true;
    if( or4 == 0 && isIntersecting( a.getEnd(), b ) )
        return true;

    return false;
}

bool IntersectTester::areLineSegmentAndCircleIntersecting(LineSegment a, Circle c)
{
    if( isIntersecting( a.getStart(), c) || isIntersecting(a.getEnd(), c) )
        return true;

    Point closest = closestPoint(a, c.getCenter());

    if (!isIntersecting(closest,a))
        return false;

    float distTest = distanceBetweenPoints( closest, c.getCenter() );
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
    if(isIntersecting(ls.getStart(), a) || isIntersecting(ls.getEnd(), a))
        return true;

    Point A(a.minimums[AABB::XDIM], a.minimums[AABB::YDIM]);
    Point B(a.minimums[AABB::XDIM], a.maximums[AABB::YDIM]);
    Point C(a.maximums[AABB::XDIM], a.maximums[AABB::YDIM]);
    Point D(a.maximums[AABB::XDIM], a.minimums[AABB::YDIM]);

    if(!isIntersecting( LineSegment( A, B ), ls )&&
       !isIntersecting( LineSegment( B, C ), ls )&&
       !isIntersecting( LineSegment( D, C ), ls )&&
       !isIntersecting( LineSegment( A, D ), ls ) )
        return false;

    return true;
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

    if(isIntersecting( c.getCenter(), t ) ||
       isIntersecting( LineSegment( A, B ), c ) ||
       isIntersecting( LineSegment( B, C ), c ) ||
       isIntersecting( LineSegment( C, A ), c ) )
        return true;

    return false;
}

bool IntersectTester::doCircleandAABBIntersect(Circle c, AABB a)
{
    Point A(a.minimums[AABB::XDIM], a.minimums[AABB::YDIM]);
    Point B(a.minimums[AABB::XDIM], a.maximums[AABB::YDIM]);
    Point C(a.maximums[AABB::XDIM], a.maximums[AABB::YDIM]);
    Point D(a.maximums[AABB::XDIM], a.minimums[AABB::YDIM]);

    if(isIntersecting( c.getCenter(), a ) ||
       isIntersecting( LineSegment( A, B ), c ) ||
       isIntersecting( LineSegment( B, C ), c ) ||
       isIntersecting( LineSegment( D, C ), c ) ||
       isIntersecting( LineSegment( A, D ), c ) )
        return true;

    return false;
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

    if( isIntersecting( t.getVertexOne(), a ) ||
        isIntersecting( t.getVertexTwo(), a ) ||
        isIntersecting( t.getVertexThree(), a ) ||
        isIntersecting( LineSegment( A, B ), t ) ||
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

void IntersectTester::setTolerance(float value)
{
    tolerance = value;
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


Point IntersectTester::closestPoint(LineSegment ls, Point c)
{
    Point p1 = ls.getStart();
    Point p2 = ls.getEnd();
    Point p3 = c;

    float distX = (p1.getX() - p2.getX());
    float distY = (p1.getY() - p2.getY());

    float len = sqrt( (distX * distX ) + (distY * distY ) );
    float dot = (dotProduct( p3, p1, p2 )) / (len*len);

    float closestX = p1.getX() + ( dot * fabs( p2.getX() - p1.getX() ) );
    float closestY = p1.getY() + ( dot * fabs( p2.getY() - p1.getY() ) );
    return Point(closestX, closestY);
}

