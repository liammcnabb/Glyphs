#ifndef AABB_H
#define AABB_H

#include <vector>
#include <string>
#include <math.h>
#include <iostream>


class AABB
{
public:
    /**
     * @brief AABB Default constructor
     */
    AABB(); //Base Constructor
    /**
     * @brief AABB 2D Constructor
     * @param minX minimum x coordinate
     * @param maxX maximum x coordinate
     * @param minY minimum y coordinate
     * @param maxY maximum y coordinate
     */
    AABB( float minX, float maxX, float minY, float maxY );
    /**
     * @brief AABB 3D Constructor
     * @param minX minimum x coordinate
     * @param maxX maximum x coordinate
     * @param minY minimum y coordinate
     * @param maxY maximum y coordinate
     * @param minZ minimum z coordinate
     * @param maxZ maximum z coordinate
     */
    AABB( float minX, float maxX, float minY, float maxY,
             float minZ, float maxZ );
    /**
     * @brief AABB copy constructor
     * @param other other AABB to copy data from
     */
    AABB( const AABB& other ); //Copy Constructor
    /**
     * @brief operator= assignment operator
     * @param other other AABB to assign data from
     * @return this AABB
     */
    AABB& operator=( const AABB& other ); //Copy Assignment

    /**
     * @brief overwrite alternative assigment method
     * @param other AABB to assign from
     * @see ABBB::operator=
     */
    void overwrite( const AABB& other );
    /**
     * @brief AABB::equals
     * @param comparitor comparison AABB to check for variable equality
     * @return false if any items are not the same value.
     */
    bool equals( AABB comparitor ) const;
    /**
     * @brief AABB::intersects
     * @param comparitor comparison AABB to check for overlap
     * @return false if does not overlap on any of the axes
     */
    bool intersects( AABB comparitor ) const;
    /**
     * @brief AABB::unify
     * @param a
     * @param b
     * @return
     */
    static AABB unify( AABB* a, AABB* b );
    /**
     * @brief length calculates the distance between the min and max values of
     * the dimension
     * @param dimension the dimension to test: XDIM, YDIM, ZDIM.
     * @return the distance between the min and max values of the dimension
     */
    float length( int dimension );
    std::vector<float> minimums;
    std::vector<float> maximums;
    std::string toString();

    static const int XDIM = 0;
    static const int YDIM = 1;
    static const int ZDIM = 2;
    static const int TOTAL_SIZE = 3;

private:
    /**
     * @brief AABB::initialize initialize AABB
     */
    void initialize();
    /**
     * @brief AABB::toString
     * @return  string representation of object
     */
    void dimensionsDefaultSize();
};

#endif // AABB_H
