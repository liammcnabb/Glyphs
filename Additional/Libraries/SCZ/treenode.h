#ifndef TREENODE_H
#define TREENODE_H

//#include "global.h"
#include "SCZ/polygon.h"
#include "SCZ/boundary.h"
#include "LM/aabb.h"
#include "personalerrors.cpp"
#include <QVector>


class TreeNode
{
public:
    static const int DEFAULT_INDEX = -1;

    TreeNode();
    TreeNode( QVector<QPointF> points, double area );
    TreeNode( Polygon polygon );
    TreeNode( TreeNode* obj );
    ~TreeNode();
    TreeNode& operator=( const TreeNode& b );
    bool operator==( const TreeNode& b );
    bool operator!=( const TreeNode& b );

    static TreeNode* top( TreeNode* t );

    double getArea() const;
    void setArea( double value );

    TreeNode* getParent() const;
    void setParent( TreeNode* value );

    Boundary* getNonSharedBoundary() const;
    void setNonSharedBoundary( QVector<QPointF>* value );

    Boundary* getSharedBoundary() const;
    void setSharedBoundary( QVector<QPointF>* value );

    void initNonSharedBoundary( QVector<QPointF> value );

    bool splitBoundary( TreeNode* neighbour );

    QPointF* centroid() const;
    bool initBounds();

    TreeNode* getLeftChild() const;
    void setLeftChild( TreeNode* value );

    TreeNode* getRightChild() const;
    void setRightChild( TreeNode* value );

    QVector<TreeNode*>* getNeighbours() const;
    void setNeighbours( QVector<TreeNode*>* value );

    AABB getBoundingBox() const;
    void setBoundingBox( AABB boundingBox );

    float getMaxX() const;
    void setMaxX( float value );

    float getMaxY() const;
    void setMaxY( float value );

    float getMinX() const;
    void setMinX( float value );

    float getMinY() const;
    void setMinY( float value );

    QVector<QPointF> fullBoundary();

    void updateNeighbours();

    QString toString() const;
    double value = 0;

    QStringList values;

private:
    void calculateArea();

    TreeNode* parent = nullptr;
    Boundary* nonSharedBoundary = nullptr;
    Boundary* sharedBoundary = nullptr;
    TreeNode* leftChild = nullptr;
    TreeNode* rightChild = nullptr;
    QPointF* m_centroid = nullptr;
    AABB m_boundingBox;

    QVector<TreeNode*>* neighbours = nullptr;


    float maxX = 0, maxY = 0, minX = 0, minY = 0;

    double allPoints = 0;

    double area = 0.0;


    void calculateCentroid();
};

#endif // TREENODE_H
