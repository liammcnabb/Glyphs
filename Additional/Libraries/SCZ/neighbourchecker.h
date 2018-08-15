#ifndef NEIGHBOURCHECKER_H
#define NEIGHBOURCHECKER_H

#include "SCZ/treenode.h"
#include "SCZ/linkedlist.h"
//#include "global.h"
#include "LM/IntersectTester/AABB.h"

class NeighbourChecker
{
public:
    static bool isNeighbour( Polygon pOne, Polygon pTwo,
                             int searchType );
    static bool isNeighbour( TreeNode pOne, int pTwo,
                             LinkedList* list, int searchType );
    static bool commonVertices( QVector<QPointF> pOne,
                                QVector<QPointF> pTwo,
                                int searchType );
    static bool isPointOnLine( QPointF point, QPointF linePointA,
                               QPointF linePointB );
    static bool isIntersecting( AABB a, AABB b );

    static int next(QVector<QPointF> list, int index);

    static const int NEIGHBOUR_MIN = 1;
};

#endif // NEIGHBOURCHECKER_H
