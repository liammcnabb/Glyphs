#ifndef AABB_H
#define AABB_H

#include <vector>
#include <string>
#include <math.h>
#include <iostream>


class AABB
{
public:
    AABB(); //Base Constructor
    AABB( float minX, float maxX, float minY, float maxY );
    AABB( float minX, float maxX, float minY, float maxY,
             float minZ, float maxZ );
    AABB( const AABB& other ); //Copy Constructor
    ~AABB();
    AABB& operator=( const AABB& other ); //Copy Assignment


    void overwrite( const AABB& other );
    bool equals( AABB comparitor ) const;
    bool intersects( AABB comparitor ) const;
    static AABB unify( AABB* a, AABB* b );

    float length( int dimension );
    std::vector<float> minimums;
    std::vector<float> maximums;
    std::string toString();

    static const int XDIM = 0;
    static const int YDIM = 1;
    static const int ZDIM = 2;
    static const int TOTAL_SIZE = 3;

private:
    void initialize();
    void dimensionsDefaultSize();
};

#endif // AABB_H
