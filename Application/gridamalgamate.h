#ifndef GRIDAMALGAMATE_H
#define GRIDAMALGAMATE_H

#include <QVector>
#include <QStringList>
#include <QDebug>

#include "SCZ/polygon.h"
#include "SCZ/treenode.h"
#include "LM/IntersectTester/AABB.h"
#include "LM/IntersectTester/IntersectTester.h"

class GridAmalgamate
{
public:
    /**
     * @brief amalgamate returns a set of TreeNodes that present a grid view of
     * the underlying geospatial data.
     * @param nodes nodes to split and match to a grid
     * @param envelope the extents of the geospatial map
     * @return a list of ordered TreeNodes set up as a grid
     */
    static QVector<TreeNode> amalgamate(QVector<Polygon> nodes, AABB envelope );
private:
    /**
     * @brief updateValue append any new matched values to a cell and update
     *  values
     * @param values original value assigned to grid
     * @param newValues value assigned to grid
     * @return updated values
     */
    static QStringList updateValue( QStringList values, QStringList newValues);
};

#endif // GRIDAMALGAMATE_H
