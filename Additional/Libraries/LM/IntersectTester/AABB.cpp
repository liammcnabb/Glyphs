#include "LM/IntersectTester/AABB.h"

AABB::AABB()
{
    initialize();
}

AABB::AABB( float minX, float maxX, float minY, float maxY )
{
    initialize();

    minimums.at( XDIM ) = minX;
    minimums.at( YDIM ) = minY;
    minimums.at( ZDIM ) = 0;

    maximums.at( XDIM ) = maxX;
    maximums.at( YDIM ) = maxY ;
    maximums.at( ZDIM ) = 0;

}

AABB::AABB( float minX, float maxX, float minY,
                  float maxY, float minZ, float maxZ )
{
    initialize();
    minimums.at( XDIM ) = minX;
    minimums.at( YDIM ) = minY;
    minimums.at( ZDIM ) = minZ;

    maximums.at( XDIM ) = maxX;
    maximums.at( YDIM ) = maxY ;
    maximums.at( ZDIM ) = maxZ;

}

AABB::AABB( const AABB& other )
{
    initialize();
    minimums.at( XDIM ) = other.minimums.at( XDIM );
    minimums.at( YDIM ) = other.minimums.at( YDIM );
    minimums.at( ZDIM ) = other.minimums.at( ZDIM );

    maximums.at( XDIM ) = other.maximums.at( XDIM );
    maximums.at( YDIM ) = other.maximums.at( YDIM );
    maximums.at( ZDIM ) = other.maximums.at( ZDIM );
}


AABB& AABB::operator=( const AABB& other )
{
    maximums = other.maximums;
    minimums = other.minimums;
    return *this;
}

void AABB::overwrite( const AABB& other )
{
    minimums.at( XDIM ) = other.minimums.at( XDIM );
    minimums.at( YDIM ) = other.minimums.at( YDIM );
    minimums.at( ZDIM ) = other.minimums.at( ZDIM );

    maximums.at( XDIM ) = other.maximums.at( XDIM );
    maximums.at( YDIM ) = other.maximums.at( YDIM );
    maximums.at( ZDIM ) = other.maximums.at( ZDIM );
}

/**
 * @brief AABB::equals
 * @param comparitor comparison AABB to check for variable equality
 * @return false if any items are not the same value.
 */
bool AABB::equals( AABB comparitor ) const
{
    for ( int i = 0; i < TOTAL_SIZE; ++i )
    {
        if ( minimums.at( i ) != comparitor.minimums.at( i ) ||
                maximums.at( i ) != comparitor.maximums.at( i ) )
            return false;
    }

    return true;
}

/**
 * @brief AABB::intersects
 * @param comparitor comparison AABB to check for overlap
 * @return false if does not overlap on any of the axes
 */
bool AABB::intersects( AABB comparitor ) const
{
    if ( maximums.at( XDIM ) < comparitor.minimums.at( XDIM ) ||
            minimums.at( XDIM ) > comparitor.maximums.at( XDIM ) )
        return false;
    if ( maximums.at( YDIM ) < comparitor.minimums.at( YDIM ) ||
            minimums.at( YDIM ) > comparitor.maximums.at( YDIM ) )
        return false;
    if ( maximums.at( ZDIM ) < comparitor.minimums.at( ZDIM ) ||
            minimums.at( ZDIM ) > comparitor.maximums.at( ZDIM ) )
        return false;

    return true;
}

AABB::~AABB()
{

}

/**
 * @brief AABB::unify
 * @param a
 * @param b
 * @return
 */
AABB AABB::unify( AABB* a, AABB* b )
{
    float minX = std::min( a->minimums.at( XDIM ),
                           b->minimums.at( XDIM ) );
    float minY = std::min( a->minimums.at( YDIM ),
                           b->minimums.at( YDIM ) );
    float minZ = std::min( a->minimums.at( ZDIM ),
                           b->minimums.at( ZDIM ) );

    float maxX = std::max( a->maximums.at( XDIM ),
                           b->maximums.at( XDIM ) );
    float maxY = std::max( a->maximums.at( YDIM ),
                           b->maximums.at( YDIM ) );
    float maxZ = std::max( a->maximums.at( ZDIM ),
                           b->maximums.at( ZDIM ) );

    return AABB( minX, maxX, minY, maxY, minZ, maxZ );
}

float AABB::length( int dimension )
{
    switch( dimension )
    {
        case XDIM:
            return fabs( maximums[XDIM] - minimums[XDIM] );
            break;
        case YDIM:
            return fabs( maximums[YDIM] - minimums[YDIM] );
            break;
        case ZDIM:
            return fabs( maximums[ZDIM] - minimums[ZDIM] );
            break;
        default:
            std::cout << "AABB::length(int dimension) : " <<
                     "Dimension Doesn't exist." << std::endl;
            return 0.0f;
            break;
    }
}

/**
 * @brief AABB::initialize
 */
void AABB::initialize()
{
    minimums = std::vector<float>( TOTAL_SIZE, 0.0f );
    maximums = std::vector<float>( TOTAL_SIZE, 0.0f );
}


/**
 * @brief AABB::toString
 * @return  string representation of object
 */
std::string AABB::toString()
{
//    return "Minimums: { " +  std::to_string(minimums[ XDIM ])  + ", " +
//            std::to_string(minimums[ YDIM ])  + ", " +
//            std::to_string(minimums[ ZDIM ])  + " } Maximums: { " +
//            std::to_string(maximums[ XDIM ])  + ", " +
//            std::to_string(maximums[ YDIM ])  + ", " +
//            std::to_string(maximums[ ZDIM ])  + "}." + std::endl;
}

