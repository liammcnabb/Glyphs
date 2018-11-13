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
    GridAmalgamate();
    static QVector<TreeNode> amalgamate(QVector<Polygon> nodes, AABB envelope );
private:
    static QStringList updateValue( QStringList values, QStringList newValues);
};

#endif // GRIDAMALGAMATE_H
