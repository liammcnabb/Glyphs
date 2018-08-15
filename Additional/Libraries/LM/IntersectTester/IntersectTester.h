#ifndef INTERSECTTESTER_H
#define INTERSECTTESTER_H

#include <limits>
#include <QDebug>
#include "AABB.h"
//#include "IntersectTester.cpp"


class Point {
public:
        float x, y, z;
        Point() 
        {
            this->x = 0;
            this->y = 0;
            this->z = 0;
        }
        Point( float x, float y )
        {
            this->x = x;
            this->y = y;
            this->z = 0;
        }
        Point( float x, float y, float z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
         Point& operator= (const Point& other)
         {
             x = other.getX();
             y = other.getY();
             z = other.getZ();
             return *this;
         }
        float getX() const { return x; }
        float getY() const { return y; }
        float getZ() const { return z; }
        void setX( float newX ) { x = newX; }
        void setY( float newY ) { y = newY; }
        void setZ( float newZ ) { z = newZ; }
};

class LineSegment {
public:
        Point start;
        Point end;
        LineSegment(Point x, Point y)
        {
             start = Point(x.getX(), x.getY(), x.getZ());          
             end = Point(y.getX(), y.getY(), y.getZ());
        }
        Point getStart() const { return start; } 
        Point getEnd() const { return end; } 
};

class Line {
public:
        Point start;
        Point end;
        Line(Point x, Point y)
        {
             start = Point(x.getX(), x.getY(), x.getZ());
             end = Point(y.getX(), y.getY(), y.getZ());
        }
        Point getStart() const { return start; } 
        Point getEnd() const { return end; } 
};

class Triangle {
public:
        Point v1, v2 ,v3;
        Triangle(Point x, Point y, Point z)
        {
             v1 = Point(x.getX(), x.getY(), x.getZ());
             v2 = Point(y.getX(), y.getY(), y.getZ());
             v3 = Point(y.getX(), y.getY(), y.getZ());
        }
        Point getVertexOne() const { return v1; } 
        Point getVertexTwo() const { return v2; } 
        Point getVertexThree() const { return v3; } 
};

class Circle {
public:
    Point center;
    float radius;
    Circle(Point center, float radius)
    {
        this->center = center;
        this->radius = radius;
    }
    Point getCenter() const { return center; }
    float getRadius() const { return radius; }
};



class IntersectTester
{

public:
    IntersectTester();
    inline static bool isIntersecting(Point a, Point b)
    { 
        return a.getX() == b.getX() &&
               a.getY() == b.getY() &&
               a.getZ() == b.getZ();
    }
   /**
    * @brief IntersectTester::isIntersecting calls isPointOnLineSegment
    * @refer IntersectTester::isPointOnLineSegment
    * @param p coordinate set to test
    * @param ls lineSegment
    * @return if point is on line segment (ls), return
    * true, otherwise return false.
    */
    inline static bool isIntersecting(Point p, LineSegment ls) 
    { return isPointOnLineSegment( p, ls ); }

    inline static bool isIntersecting(Point p, Line l) 
    { return isPointOnLine( p, l ); }

    inline static bool isIntersecting(LineSegment a, LineSegment b) 
    { return areLineSegmentsIntersecting( a, b ); }

    inline static bool isIntersecting(Line l, Triangle t) 
    { return doLineAndTriangleIntersect( l, t ); }

    inline static bool isIntersecting(AABB a, AABB b) 
    { return areBoxesIntersecting( a, b ); }
    
    inline static bool isIntersecting(Point p, AABB a)
    { return isPointOnAABB( p, a ); }
    
    inline static bool isIntersecting(LineSegment ls, AABB a)
    { return doesLineSegmentIntersectAABB( ls, a ); }

    inline static bool isIntersecting(Point p, Circle c)
    { return isPointOnCircle( p,c ); }
    

    static float distanceBetweenPoints(Point a, Point b);
private:
    /**
    * @brief IntersectTester::isPointOnLineSegment used to check
    * whether a coordinate point (p) intersects with a line (ls).
    * @param p coordinate set to test
    * @param ls lineSegment
    * @return if point is on the line (ls), return
    * true, otherwise return false.
    */
    static bool isPointOnLineSegment(Point p, LineSegment ls);
    static bool isPointOnLine(Point p, Line l);
    static bool isPointOnTriangle(Point p, Triangle t);
    static bool doLineAndTriangleIntersect(Line l, Triangle t);
    static bool areLineSegmentsIntersecting(LineSegment a, LineSegment b);
    static bool isPointOnAABB(Point p, AABB a);
    static bool doesLineSegmentIntersectAABB(LineSegment ls, AABB a );
    static bool isPointOnCircle(Point p, Circle c);


    static bool areBoxesIntersecting(AABB a, AABB b);
};


#endif // INTERSECTTESTER_H
