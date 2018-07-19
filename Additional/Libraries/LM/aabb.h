#ifndef AABB_H
#define AABB_H

#include "LM/boundingbox.h"
#include <vector>
#include <string>
#include <math.h>
#include <QDebug>


class AABB : public BoundingBox
{
public:
    AABB(); //Base Constructor
    AABB( float minX, float maxX, float minY, float maxY );
    AABB( float minX, float maxX, float minY, float maxY,
             float minZ, float maxZ );
    AABB( const AABB& other ); //Copy Constructor
    ~AABB(); //Destructor

    AABB& operator=( const AABB& other ); //Copy Assignment

    void overwrite( const AABB& other );
    bool equals( AABB comparitor ) const;
    bool intersects( AABB comparitor ) const;
    static AABB unify( AABB* a, AABB* b );

    float length( int dimension );


    std::vector<float> minimums;
    std::vector<float> maximums;


    std::string toString();

private:


    void initialize();
    void dimensionsDefaultSize();
};

#endif // AABB_H
