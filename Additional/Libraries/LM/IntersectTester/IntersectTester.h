#ifndef INTERSECTTESTER_H
#define INTERSECTTESTER_H

#include <limits>
#include <QDebug>
#include "AABB.h"
//#include "IntersectTester.cpp"


class Point {
public:
        float x, y, z;
        /**
         * @brief Point Default Constructor
         */
        Point() 
        {
            this->x = 0;
            this->y = 0;
            this->z = 0;
        }
        /**
         * @brief Point Constructor for a 2D Point
         * @param x
         * @param y
         */
        Point( float x, float y )
        {
            this->x = x;
            this->y = y;
            this->z = 0;
        }
        /**
         * @brief Point Constructor for a 3D Point
         * @param x
         * @param y
         * @param z
         */
        Point( float x, float y, float z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        /**
          * @brief operator= assignment operator
          * @param other the point to assign to this object
          * @return return this object
          */
         Point& operator= (const Point& other)
         {
             x = other.getX();
             y = other.getY();
             z = other.getZ();
             return *this;
         }
        /**
        * @brief getX getter method for the x axis coordinate reference
        * @return float depicting x axis coordinate reference
        */
        float getX() const { return x; }
        /**
        * @brief getY getter method for the y axis coordinate reference
        * @return float depicting y axis coordinate reference
        */
        float getY() const { return y; }
        /**
        * @brief getZ getter method for the z axis coordinate reference
        * @return float depicting z axis coordinate reference
        */
        float getZ() const { return z; }
        /**
         * @brief setX setter method for the x axis coordinate reference
         * @param newX new value for the x axis coordinate reference
         */
        void setX( float newX ) { x = newX; }
        /**
         * @brief setY setter method for the y axis coordinate reference
         * @param newY new value for the y axis coordinate reference
         */
        void setY( float newY ) { y = newY; }
        /**
         * @brief setZ setter method for the z axis coordinate reference
         * @param newZ new value for the z axis coordinate reference
         */
        void setZ( float newZ ) { z = newZ; }
};

class LineSegment {
public:
        Point start;
        Point end;
        /**
         * @brief LineSegment Default Constructor, a line between 2 points
         * @param x starting point
         * @param y ending point
         */
        LineSegment(Point x, Point y)
        {
             start = Point(x.getX(), x.getY(), x.getZ());
             end = Point(y.getX(), y.getY(), y.getZ());
        }
        /**
         * @brief getStart getter method for starting point
         * @return starting point of line segment
         */
        Point getStart() const { return start; }
        /**
         * @brief getEnd getter method for end of line segment
         * @return end point of line segment
         */
        Point getEnd() const { return end; } 
};


class Triangle {
public:
        Point v1, v2 ,v3;
        /**
         * @brief Triangle Default consructor for triangle
         * @param x vertex one
         * @param y vertex two
         * @param z vertex three
         */
        Triangle(Point x, Point y, Point z)
        {
             v1 = Point(x.getX(), x.getY(), x.getZ());
             v2 = Point(y.getX(), y.getY(), y.getZ());
             v3 = Point(z.getX(), z.getY(), z.getZ());
        }
        /**
         * @brief getVertexOne getter method for the first vertex
         * @return  vertex one
         */
        Point getVertexOne() const { return v1; } 
        /**
         * @brief getVertexTwo getter method for the second vertex
         * @return  vertex two
         */
        Point getVertexTwo() const { return v2; } 
        /**
         * @brief getVertexThree getter method for the third vertex
         * @return vertex three
         */
        Point getVertexThree() const { return v3; } 
};

class Circle {
public:
    Point center;
    float radius;
    /**
     * @brief Circle Default constructor for circle
     * @param center center point of the circle
     * @param radius the radius of the circle (distance from center to edge)
     */
    Circle(Point center, float radius)
    {
        this->center = center;
        this->radius = radius;
    }
    /**
     * @brief getCenter getter method for center point
     * @return center
     */
    Point getCenter() const { return center; }
    /**
     * @brief getRadius getter method for radius of circle
     * @return radius
     */
    float getRadius() const { return radius; }
};



class IntersectTester
{

public:
    /**
     * @brief IntersectTester Default Constructor
     */
    IntersectTester();

    /**
    * @brief IntersectTester::isIntersecting checks if the two points sit on each other
     */
    inline static bool isIntersecting(Point a, Point b)
    { return a.getX() == b.getX() &&
             a.getY() == b.getY() &&
             a.getZ() == b.getZ();
    }
   /**
    * @brief IntersectTester::isIntersecting calls isPointOnLineSegment
    * @refer IntersectTester::isPointOnLineSegment
    */
    inline static bool isIntersecting(Point p, LineSegment ls) 
    { return isPointOnLineSegment( p, ls ); }

    /**
     * @brief IntersectTester::isIntersecting calls isPointOnCircle
     * @refer IntersectTester::isPointOnCircle
     */
    inline static bool isIntersecting(Point p, Circle c)
    { return isPointOnCircle( p,c ); }

    /**
     * @brief  IntersectTester::isIntersecting calls isPointOnTriangle
     * @refer IntersectTester::isPointOnTriangle
     */
    inline static bool isIntersecting(Point p, Triangle t)
    { return isPointOnTriangle( p,t ); }

    /**
     * @brief  IntersectTester::isIntersecting calls isPointOnAABB
     * @refer IntersectTester::isPointOnTriangle
     */
    inline static bool isIntersecting(Point p, AABB a)
    { return isPointOnAABB( p, a ); }

    /**
     * @brief  IntersectTester::isIntersecting calls areLineSegmentsIntersecting
     * @refer IntersectTester::areLineSegmentsIntersecting
     */
    inline static bool isIntersecting(LineSegment a, LineSegment b) 
    { return areLineSegmentsIntersecting( a, b ); }

    /**
     * @brief  IntersectTester::isIntersecting calls areLineSegmentAndCircleIntersecting
     * @refer IntersectTester::areLineSegmentAndCircleIntersecting
     */
    inline static bool isIntersecting(LineSegment a, Circle c)
    { return areLineSegmentAndCircleIntersecting( a, c ); }

    /**
     * @brief  IntersectTester::isIntersecting calls doesLineSegmentIntersectTriangle
     * @refer IntersectTester::doesLineSegmentIntersectTriangle
     */
    inline static bool isIntersecting(LineSegment ls, Triangle t)
    { return doesLineSegmentIntersectTriangle( ls, t ); }

    /**
     * @brief  IntersectTester::isIntersecting calls doesLineSegmentIntersectAABB
     * @refer IntersectTester::doesLineSegmentIntersectAABB
     */
    inline static bool isIntersecting(LineSegment ls, AABB a)
    { return doesLineSegmentIntersectAABB( ls, a ); }

    /**
     * @brief  IntersectTester::isIntersecting calls doCirclesIntersect
     * @refer IntersectTester::doCirclesIntersect
     */
    inline static bool isIntersecting(Circle a, Circle b)
    { return doCirclesIntersect(a,b); }

    /**
     * @brief  IntersectTester::isIntersecting calls doesCircleIntersectTriangle
     * @refer IntersectTester::doesCircleIntersectTriangle
     */
    inline static bool isIntersecting(Circle c, Triangle t)
    { return doesCircleIntersectTriangle(c,t); }

    /**
     * @brief  IntersectTester::isIntersecting calls doCircleandAABBIntersect
     * @refer IntersectTester::doCircleandAABBIntersect
     */
    inline static bool isIntersecting(Circle c, AABB a)
    { return doCircleandAABBIntersect(c, a); }

    /**
     * @brief  IntersectTester::isIntersecting calls doTrianglesIntersect
     * @refer IntersectTester::doTrianglesIntersect
     */
    inline static bool isIntersecting(Triangle a, Triangle b)
    { return doTrianglesIntersect(a,b); }

    /**
     * @brief  IntersectTester::isIntersecting calls doTriangleAndAABBIntersect
     * @refer IntersectTester::doTriangleAndAABBIntersect
     */
    inline static bool isIntersecting(Triangle t, AABB a)
    { return doTriangleAndAABBIntersect(t,a); }

    /**
     * @brief  IntersectTester::isIntersecting calls areBoxesIntersecting
     * @refer IntersectTester::areBoxesIntersecting
     */
    inline static bool isIntersecting(AABB a, AABB b) 
    { return areBoxesIntersecting( a, b ); }
    


    /**
     * @brief distanceBetweenPoints calculates the distance between
     * two points.
     * @param a Point
     * @param b Point
     * @return a floating point that depicts the distance
     *  between two points
     */
    static float distanceBetweenPoints(Point a, Point b);
    /**
     * @brief crossProduct calculates the cross product of
     * three points
     * @param a Point
     * @param b Point
     * @param c Point
     * @return
     */
    static float crossProduct(Point a, Point b, Point c);
    /**
     * @brief dotProduct calculates the dot product of
     * three points
     * @param a
     * @param b
     * @param c
     * @return
     */
    static float dotProduct(Point a, Point b, Point c);
    /**
     * @brief direction return the sign of the vector
     * of points.
     * @param a Point
     * @param b Point
     * @param c Point
     * @return returns 1 if positive, -1 if negative,
     * and 0 if colinear.
     */
    static int direction(Point a, Point b, Point c);

    /**
     * @brief setTolerance set the tolerance value for precision tests.
     * @param value the new tolerance value
     */
    static void setTolerance(float value);

    /**
     * @brief closestPoint returns the closest point on a line segment
     * to Point c.
     * @param ls LineSegment
     * @param c Point
     * @return
     */
    static Point closestPoint(LineSegment ls, Point c);
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
    /**
     * @brief isPointOnCircle Tested by checking the distance
     * between the point, and the center of the circle, if the
     * distance is less than or equal to the radius, the point is
     * within the circle.
     * @param p Point
     * @param c Circle
     * @return if point is in the circle, return true,
     * otherwise return false
     */
    static bool isPointOnCircle(Point p, Circle c);
    /**
     * @brief isPointOnTriangle In order for a point to sit inside
     * a triangle we must check the crossproduct for a direction.
     * if all crossproducts move in the same direction, then the
     * point sits in the triangle. We also check edge cases using
     * previous tests point-to-line, and point-to-point.
     * @param p Point
     * @param t Triangle
     * @return if point is in triangle, return true,
     * otherwise return false
     */
    static bool isPointOnTriangle(Point p, Triangle t);
    /**
     * @brief isPointOnAABB We test the null hypothesis.
     * If the X axis, or the Y axis fall outside of the axes
     * range of the bounding box, the we know this is false.
     * Otherwise it is true.
     * @param p Point
     * @param a AABB
     * @return if point is within AABB, return true,
     * otherwise return false.
     */
    static bool isPointOnAABB(Point p, AABB a);
    /**
     * @brief areLineSegmentsIntersecting we check the vector direction
     * between the points. If the both ends of the line segment sit on
     * seperate sides of the opposing line,than they intersect. Otherwise
     * we also check if the lines sit on top of each other.
     * @param a LineSegment a
     * @param b LineSegment b
     * @return if line segments intersect, return true,
     * otherwise return false
     */
    static bool areLineSegmentsIntersecting(LineSegment a, LineSegment b);
    /**
     * @brief areLineSegmentAndCircleIntersecting We calculate the
     * closest point between the line and the circle's center. If the
     * closest point falls on the line segment and the distance is less than
     * the radius, the two intersect.
     * @param a LineSegment
     * @param c Circle
     * @return if linesegment and circle intersect, return true,
     * otherwise return false.
     */
    static bool areLineSegmentAndCircleIntersecting( LineSegment a, Circle c );
    /**
     * @brief doesLineSegmentIntersectTriangle we test the line segment
     * against each edge of the triangle. If any of the lines intersect,
     * than we know the line and triangle intersect.
     * @param a LineSegment
     * @param t Triangle
     * @return if linesegment and triangle intersect, return true,
     * otherwise return false.
     */
    static bool doesLineSegmentIntersectTriangle( LineSegment a, Triangle t);
    /**
     * @brief doesLineSegmentIntersectAABB We first check if either point lies of
     * the line segment fall inside the box, if not, we test every line-to-line
     * intersection. If any return true, we know the LineSegment and
     * AABB intersect
     * @param ls LineSegment
     * @param a AABB
     * @return if linesegment and AABB intersect, return true,
     * otherwise return false.
     */
    static bool doesLineSegmentIntersectAABB(LineSegment ls, AABB a );
    /**
     * @brief doCirclesIntersect we calculate the distance between points.
     * If the distance is less than the combined radius, the two circles
     * intersect.
     * @param a Circle a
     * @param b Circle b
     * @return if the circles intersect, return true, otherwise
     * return false.
     */
    static bool doCirclesIntersect(Circle a, Circle b);
    /**
     * @brief doesCircleIntersectTriangle we test if the circle's center
     * point sits in the triangle, if not we also check if any triangle
     * edge intersects with the circle. If any of these are true, we
     * know the two objects intersect.
     * @param c Circle
     * @param t Triangle
     * @return if the circle and triangle intersect, return true,
     * otherwise return false.
     */
    static bool doesCircleIntersectTriangle(Circle c, Triangle t);
    /**
     * @brief doCircleandAABBIntersect we test the circle's center,
     * using a point-to-box, and point-to-line tests. If any are
     * true, we know the two intersect.
     * @param c Circle
     * @param a AABB
     * @return if the circle and AABB intersect, return true,
     * otherwise return false.
     */
    static bool doCircleandAABBIntersect(Circle c, AABB a);
    /**
     * @brief doTrianglesIntersect we test the edges of the triangles
     * against each other. If any are true, we know the triangles
     * intersect
     * @param a Triangle a
     * @param b Triangle b
     * @return if the triangles intersect. return true,
     * otherwise return false.
     */
    static bool doTrianglesIntersect(Triangle a, Triangle b);
    /**
     * @brief doTriangleAndAABBIntersect we test the edges of the
     * triangle and AABB against each other. If any are true,
     * we know the two intersect
     * @param t Triangle
     * @param a AABB
     * @return if the triangle and AABB intersect, return true,
     * otherwise return false.
     */
    static bool doTriangleAndAABBIntersect(Triangle t, AABB a);
    /**
     * @brief areBoxesIntersecting the axis-aligned box test is similar to the point test.
     * We use the null hypothesis. If the X dimension extents of AABB 2 do not fall into
     * the extents of AABB 1, then we know that it is not possible for the boxes to
     * intersect. We can make the same assumption for the Y axis. If both the X and Y axes
     * of AABB 2 can be found in AABB 1, then we know that they intersect.
     * @param a AABB 1
     * @param b AABB 2
     * @return
     */
    static bool areBoxesIntersecting(AABB a, AABB b);

    static float tolerance;


    bool isPointOnLineSegmentOld(Point p, LineSegment ls);
};


#endif // INTERSECTTESTER_H
