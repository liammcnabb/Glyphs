#ifndef TREENODE_H
#define TREENODE_H

//#include "global.h"
#include "SCZ/polygon.h"
#include "SCZ/boundary.h"
#include "LM/IntersectTester/AABB.h"
#include "personalerrors.cpp"
#include <QVector>


class TreeNode
{
public:
    /**
     * @brief DEFAULT_INDEX index given when searching to test for no matches
     */
    static const int DEFAULT_INDEX = -1;
    /**
     * @brief TreeNode Default Constructor
     */
    TreeNode();
    /**
     * @brief TreeNode Constructor passing set of points and area of the polygon
     * @param points list of associate points
     * @param area area of polygon
     */
    TreeNode( QVector<QPointF> points, double area );
    /**
     * @brief TreeNode Copy constructor
     * @param polygon Polygon object to copy data from
     */
    TreeNode( Polygon polygon );
    /**
     * @brief TreeNode Copy constructor
     * @param obj TreeNode object to copy data from
     */
    TreeNode( TreeNode* obj );
    ~TreeNode();
    /**
     * @brief operator = assignment operator
     * @param b oject to assign to this
     * @return this object
     */
    TreeNode& operator=( const TreeNode& b );
    /**
     * @brief operator == equality check. Tests whether objects are equivalent
     * @param b object to check equality against
     * @return true if equivalent, false otherwise
     */
    bool operator==( const TreeNode& b ) const;
    /**
     * @brief operator != non-equality check. Tests whether objects are
     * non-equivalent
     * @param b object to check non-equality against
     * @return true if non-equivalent, false otherwise
     */
    bool operator!=( const TreeNode& b );

    /**
     * @brief top move to the top of the data structure
     * @param t current treenode
     * @return returns the topmost treenode in the data structure
     */
    static TreeNode* top( TreeNode* t );

    /**
     * @brief getArea getter method to return area of polygon
     * @return area area of polygon
     */
    double getArea() const;
    /**
     * @brief setArea setter method for the area of the polygon
     * @param value new area
     */
    void setArea( double value );

    /**
     * @brief getParent getter method for TreeNode's parent node
     * @return pointer to parent TreeNode
     */
    TreeNode* getParent() const;
    /**
     * @brief setParent setter method for TreeNode's parent node
     * @param value new pointer address for parent
     */
    void setParent( TreeNode* value );

    /**
     * @brief getNonSharedBoundary getter method for non-shared boundary point
     * list
     * @return list of non-shared boundary points
     */
    Boundary* getNonSharedBoundary() const;
    /**
     * @brief setNonSharedBoundary setter method for non-shared boundary point
     * list
     * @param value new list of non-shared boundary points
     */
    void setNonSharedBoundary( QVector<QPointF>* value );

    /**
     * @brief getSharedBoundary getter method for shared boundary point list
     * @return list of shared boundary points
     */
    Boundary* getSharedBoundary() const;
    /**
     * @brief setSharedBoundary setter method for shared boundary point list
     * @param value new list of shared boundary points
     */
    void setSharedBoundary( QVector<QPointF>* value );

    /**
     * @brief initNonSharedBoundary an initialization method that saves the
     * points to the treenode and calculates calls other intial processes
     * @param value list of associate points
     */
    void initNonSharedBoundary( QVector<QPointF> value );

    /**
     * @brief splitBoundary splits the boundary into shared and non-shared
     * boundary points
     * @param neighbour the TreeNode's associated neighbour
     * @return whether the process has ended successfully
     */
    bool splitBoundary( TreeNode* neighbour );

    /**
     * @brief centroid getter method for polygon's centroid
     * @return polygon's centroid
     */
    QPointF* centroid() const;
    /**
     * @brief setCentroid setter method for polygon's centroid
     * @param centroid polygon's new centroid
     */
    void setCentroid(QPointF *centroid);
    /**
     * @brief initBounds initialize bounding box of the polygon
     * @return whether the process has ended successfully
     */
    bool initBounds();

    /**
     * @brief getLeftChild getter method for left child of treenode
     * @return pointer depicting left child in the data structure
     */
    TreeNode* getLeftChild() const;
    /**
     * @brief setLeftChild setter method for left child of treenode
     * @param value new pointer depicting left child in the data structure
     */
    void setLeftChild( TreeNode* value );

    /**
     * @brief getRightChild getter method for right child of treenode
     * @return pointer depicting right child in the data structure
     */
    TreeNode* getRightChild() const;
    /**
     * @brief setRightChild setter method for right child of treenode
     * @param value new pointer depicting right child in the data structure
     */
    void setRightChild( TreeNode* value );

    /**
     * @brief getBoundingBox getter method for polygon's bounding box
     * @return polygon's bounding box
     */
    AABB getBoundingBox() const;
    /**
     * @brief setBoundingBox setter method for polygon's bounding box
     * @param boundingBox new bounding box of polygon
     */
    void setBoundingBox( AABB boundingBox );

    /**
     * @brief getMaxX getter method for maximum x coordinate
     * @return maximum x coordinate
     */
    float getMaxX() const;
    /**
     * @brief setMaxX setter method for maximum x coordinate
     * @param value new value of maximum x coordinate
     */
    void setMaxX( float value );

    /**
     * @brief getMaxY getter method for maximum y coordinate
     * @return maximum y coordinate
     */
    float getMaxY() const;
    /**
     * @brief setMaxY setter method for maximum y coordinate
     * @param value new value of maximum y coordinate
     */
    void setMaxY( float value );

    /**
     * @brief getMinX getter method for minimum x coordinate
     * @return minimum x coordinate
     */
    float getMinX() const;
    /**
     * @brief setMinX setter method for maximum x coordinate
     * @param value new value of minimum x coordinate
     */
    void setMinX( float value );

    /**
     * @brief getMinY getter method for maximum y coordinate
     * @return minimum y coordinate
     */
    float getMinY() const;
    /**
     * @brief setMinY setter method for maximum y coordinate
     * @param value new value of minimum y coordinate
     */
    void setMinY( float value );

    /**
     * @brief fullBoundary getter method for full boundary of the polygon
     * @return all boundary points saved to the treenode
     */
    QVector<QPointF> fullBoundary();

    /**
     * @brief toString return string representation of treenode
     * @return string representation of treenode
     */
    QString toString() const;

    /**
     * @brief getValues getter method for values associated with treenode
     * @return list of string values associated with treenode
     */
    QStringList getValues() const;
    /**
     * @brief setValues setter method for values associated with treenode
     * @param value new list of string values associated with treenode
     */
    void setValues(const QStringList &value);

    /**
     * @brief getLevel getter method for level of hierarchical data structure,
     * 0 = leafnode.
     * @return level within data structure
     */
    int getLevel() const;
    /**
     * @brief setLevel setter method for level of hierarchical data structure,
     * 0 = leafnode
     * @param value new value depicting level within data structure
     */
    void setLevel(int value);

    /**
     * @brief getParentCentroid getter method for centroid of parent treenode
     * @return centroid of parent treenode
     */
    QPointF getParentCentroid() const;
    /**
     * @brief setParentCentroid setter method for centroid of parent treenode
     * @param parentCentroid new value depicting centroid of parent treenode
     */
    void setParentCentroid(const QPointF &parentCentroid);

    /**
     * @brief getR getter method for red value associated with treenode
     * @return red value associated with treenode
     */
    float getR() const;
    /**
     * @brief setR setter method for red value associated with treenode
     * @param r new red value associated with treenode
     */
    void setR(float r);

    /**
     * @brief getG getter method for green value associated with treenode
     * @return green value associated with treenode
     */
    float getG() const;
    /**
     * @brief setG setter method for green value associated with treenode
     * @param g new green value associated with treenode
     */
    void setG(float g);

    /**
     * @brief getB getter method for blue value associated with treenode
     * @return blue value associated with treenode
     */
    float getB() const;
    /**
     * @brief setB setter method for blue value associated with treenode
     * @param b new blue value associated with treenode
     */
    void setB(float b);

    double value = 0;

    QStringList values;
private:
    /**
     * @brief calculateArea traverse saved points to calculate the area of the
     * polygon
     */
    void calculateArea();
    /**
     * @brief calculateCentroid traverse saved points to calculate center points
     * of the polygon
     */
    void calculateCentroid();

    TreeNode* parent = nullptr;
    Boundary* nonSharedBoundary = nullptr;
    Boundary* sharedBoundary = nullptr;
    TreeNode* leftChild = nullptr;
    TreeNode* rightChild = nullptr;
    QPointF* m_centroid = nullptr;
    QPointF m_parentCentroid;
    AABB m_boundingBox;
    float m_r, m_g, m_b;
    float maxX = 0, maxY = 0, minX = 0, minY = 0;
    double allPoints = 0;
    double area = 0.0;
    int level;


};

#endif // TREENODE_H
