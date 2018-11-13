#include "treenode.h"

TreeNode::TreeNode()
{
    sharedBoundary = new Boundary();
    nonSharedBoundary = new Boundary();
//    neighbours = new QVector<TreeNode*>();
}

TreeNode::TreeNode( TreeNode* obj )
{
    sharedBoundary = obj->getSharedBoundary();
    nonSharedBoundary = obj->getNonSharedBoundary();
//    neighbours = obj->getNeighbours();
    m_boundingBox = obj->getBoundingBox();

    area = obj->getArea();
    m_centroid = obj->centroid();
    maxX = obj->getMaxX();
    maxY = obj->getMaxY();
    minX = obj->getMinX();
    minY = obj->getMinY();
    leftChild = obj->getLeftChild();
    rightChild = obj->getRightChild();
    value = obj->value;
    setValues(obj->getValues());
    setLevel(obj->getLevel());
    setParentCentroid(obj->getParentCentroid());
}

TreeNode::~TreeNode()
{
    //    delete sharedBoundary;
    //    delete nonSharedBoundary;
    //    delete leftChild;
    //    delete rightChild;
}

TreeNode& TreeNode::operator=( const TreeNode& b )
{
    if ( this == &b )
        return *this;

    area = b.getArea();
    m_centroid = b.centroid();
    maxX = b.getMaxX();
    maxY = b.getMaxY();
    minX = b.getMinX();
    minY = b.getMinY();
    leftChild = b.getLeftChild();
    rightChild = b.getRightChild();
    value = b.value;
    setValues(b.getValues());
    setLevel(b.getLevel());
    setParentCentroid(b.getParentCentroid());

    sharedBoundary = b.getSharedBoundary();
    nonSharedBoundary = b.getNonSharedBoundary();
    m_boundingBox = b.getBoundingBox();

//    neighbours->resize( b.getNeighbours()->size() );
//    std::copy( b.getNeighbours()->begin(),
//               b.getNeighbours()->end(),
//               neighbours->begin() );
    return *this;
}


TreeNode::TreeNode( QVector<QPointF> points, double area )
{
    sharedBoundary = new Boundary();
    nonSharedBoundary = new Boundary( points );
//    neighbours = new QVector<TreeNode*>();

    this->area = area;
    initBounds();
    calculateCentroid();
}

TreeNode::TreeNode( Polygon polygon )
{
    sharedBoundary = new Boundary();
    nonSharedBoundary = new Boundary();
    //    m_boundingBox = polygon.getBoundingBox();
    m_boundingBox = AABB( polygon.getBoundingBox().minimums[AABB::XDIM],
                             polygon.getBoundingBox().maximums[AABB::XDIM],
                             polygon.getBoundingBox().minimums[AABB::YDIM],
                             polygon.getBoundingBox().maximums[AABB::YDIM] );
    initNonSharedBoundary( polygon.getPoints() );
//    neighbours = new QVector<TreeNode*>();
    setArea( polygon.area() );
    setValues(polygon.getValues());
    setLevel(0);
    //    value = rand() % COLORGORICAL_MAX ;
    //    if( polygon.getValues() && polygon.getFields())
    //        value = polygon.getFields().at( 2 ).toInt();
    //    else
    //        value = 0;
    //    values = polygon.values;
}

bool TreeNode::operator==( const TreeNode& b ) const
{
    if ( sharedBoundary != b.getSharedBoundary() )
        return false;
    if ( nonSharedBoundary != b.getNonSharedBoundary() )
        return false;
    return true;
}



bool TreeNode::operator!=( const TreeNode& b )
{
    if ( sharedBoundary == b.getSharedBoundary() )
        return false;
    if ( nonSharedBoundary == b.getNonSharedBoundary() )
        return false;
    return true;
}

TreeNode* TreeNode::top( TreeNode* t )
{
    if ( t->getParent() != nullptr )
        return top( t->getParent() );
    return t;
}

QVector<QPointF> TreeNode::fullBoundary()
{
    QVector<QPointF> full;

    full.append( nonSharedBoundary->getBoundary() );
    full.append( sharedBoundary->getBoundary() );

    return full;
}

//void TreeNode::updateNeighbours()
//{
//    if ( leftChild != nullptr && rightChild != nullptr )
//    {
//        getNeighbours()->clear();
//        for( int i = 0; i < leftChild->getNeighbours()->size(); ++i )
//        {
//            qDebug() << leftChild->getNeighbours()->at( i ) << rightChild;
//            if ( *leftChild->getNeighbours()->at( i ) != *rightChild )
//                getNeighbours()->append( leftChild->getNeighbours()->at( i ) );
//        }
//        for( int i = 0; i < rightChild->getNeighbours()->size(); ++i )
//            if( *rightChild->getNeighbours()->at( i ) != *leftChild &&
//                    !getNeighbours()->contains( rightChild->getNeighbours()->at(
//                                                    i ) ) )
//                getNeighbours()->append( rightChild->getNeighbours()->at( i ) );

//        getNeighbours()->squeeze();
//        qDebug() << getNeighbours()->size() <<
//                 " != " << leftChild->getNeighbours()->size() +
//                 rightChild->getNeighbours()->size();
//    }
//    else
//        qDebug() << E << NEIGHBOURS_UPDATE;
//    return;
//}

void TreeNode::initNonSharedBoundary( QVector<QPointF> value )
{
    if ( nonSharedBoundary != NULL &&
            !nonSharedBoundary->getBoundary().isEmpty() )
        allPoints = nonSharedBoundary->boundarySize();

    nonSharedBoundary->getBoundary().clear();
    if ( value.isEmpty() )
    {
        nonSharedBoundary->setStartIndex( DEFAULT_INDEX );
        nonSharedBoundary->setEndIndex( DEFAULT_INDEX );
    }
    else if ( sharedBoundary->getBoundary().isEmpty() )
    {
        nonSharedBoundary->getBoundary().append( value );
        calculateArea();
        initBounds();
        calculateCentroid();
    }
    else
        nonSharedBoundary->getBoundary().append( value );
}

void TreeNode::calculateCentroid()
{
    m_centroid = new QPointF();
    m_centroid->setX( ( getMaxX() - ( getMaxX() - getMinX() ) /
                        2 ) );
    m_centroid->setY( ( getMaxY() - ( getMaxY() - getMinY() ) /
                        2 ) );
}

bool TreeNode::initBounds()
{
    float minimumX, minimumY, maximumX, maximumY;
    minimumX = minimumY = maximumX = maximumY = 0;
    for ( QVector<QPointF>::const_iterator it =
                getNonSharedBoundary()->getBoundary().begin();
            it < getNonSharedBoundary()->getBoundary().end();
            ++it )
    {
        if( it->x() < minimumX || minimumX == 0 )
            minimumX = it->x();
        if( it->x() > maximumX || maximumX == 0 )
            maximumX = it->x();
        if( it->y() < minimumY || minimumY == 0 )
            minimumY = it->y();
        if( it->y() > maximumY || maximumY == 0 )
            maximumY = it->y();
    }

    setMinX( minimumX );
    setMinY( minimumY );
    setMaxX( maximumX );
    setMaxY( maximumY );

    m_boundingBox = AABB( minimumX, maximumX, minimumY,
                             maximumY );


    return true;
}

void TreeNode::calculateArea()
{
    QVector<double> calc1, calc2;

    for ( QVector<QPointF>::const_iterator it =
                getNonSharedBoundary()->getBoundary().begin();
            it < getNonSharedBoundary()->getBoundary().end();
            ++it )
    {
        calc1.append( it->x() );
        calc2.append( it->y() );
    }
    //Calculation to work out area of polygon
    double area1 = 0;
    double area2 = 0;

    for( int i = 0; i < calc2.size() - 1; ++i )
        area1 += ( calc1.at( i ) * calc2.at( i + 1 ) );

    area1 += ( calc1.last() * calc2.first() );

    for( int i = 0; i < calc1.size() - 1; ++i )
        area2 += ( calc1.at( i + 1 ) * calc2.at( i ) );

    area2 += ( calc1.first() * calc2.last() );

    double polygonArea = ( double ) ( ( area1 - area2 ) / 2 );

    if( polygonArea < 0 )
        polygonArea = polygonArea - ( polygonArea * 2 );

    setArea( polygonArea );
    return;
}

void TreeNode::setCentroid(QPointF *centroid)
{
    m_centroid = centroid;
}

float TreeNode::getB() const
{
    return m_b;
}

void TreeNode::setB(float b)
{
    m_b = b;
}

float TreeNode::getG() const
{
    return m_g;
}

void TreeNode::setG(float g)
{
    m_g = g;
}

float TreeNode::getR() const
{
    return m_r;
}

void TreeNode::setR(float r)
{
    m_r = r;
}

QPointF TreeNode::getParentCentroid() const
{
    return m_parentCentroid;
}

void TreeNode::setParentCentroid(const QPointF &parentCentroid)
{
    m_parentCentroid = parentCentroid;
}

int TreeNode::getLevel() const
{
    return level;
}

void TreeNode::setLevel(int value)
{
    level = value;
}

AABB TreeNode::getBoundingBox() const
{
    return m_boundingBox;
}

void TreeNode::setBoundingBox( AABB boundingBox )
{
    m_boundingBox = boundingBox;
}




QPointF* TreeNode::centroid() const
{
    return m_centroid;
}

float TreeNode::getMinY() const
{
    return minY;
}

void TreeNode::setMinY( float value )
{
    minY = value;
}

float TreeNode::getMinX() const
{
    return minX;
}

void TreeNode::setMinX( float value )
{
    minX = value;
}

float TreeNode::getMaxY() const
{
    return maxY;
}

void TreeNode::setMaxY( float value )
{
    maxY = value;
}

float TreeNode::getMaxX() const
{
    return maxX;
}

void TreeNode::setMaxX( float value )
{
    maxX = value;
}

Boundary* TreeNode::getSharedBoundary() const
{
    return sharedBoundary;
}

TreeNode* TreeNode::getLeftChild() const
{
    return leftChild;
}

void TreeNode::setLeftChild( TreeNode* value )
{
    leftChild = value;
    leftChild->setParent( this );
}

TreeNode* TreeNode::getRightChild() const
{
    return rightChild;
}

void TreeNode::setRightChild( TreeNode* value )
{
    rightChild = value;
    rightChild->setParent( this );
}

double TreeNode::getArea() const
{
    return area;
}

void TreeNode::setArea( double value )
{
    area = value;
}

TreeNode* TreeNode::getParent() const
{
    return parent;
}

void TreeNode::setParent( TreeNode* value )
{
    parent = value;
    setParentCentroid(*value->centroid());
}

Boundary* TreeNode::getNonSharedBoundary() const
{
    return nonSharedBoundary;
}

QString TreeNode::toString() const
{
    return "Non-Shared: " + QString::number(
               getNonSharedBoundary()->boundarySize() ) +
           ",\t Shared: " + QString::number(
               getSharedBoundary()->boundarySize() ) +
           ",\n Area: " + QString::number( getArea() ) +
           "\n MinX: " + QString::number( getMinX() ) +
           ",\t MaxX: " + QString::number( getMaxX() ) +
           "\n MinY: " + QString::number( getMinY() ) +
           ",\t MaxY: " + QString::number( getMaxY() ) +
           "\n Value: " + QString::number( value );
}

QStringList TreeNode::getValues() const
{
    return values;
}

void TreeNode::setValues(const QStringList &value)
{
    values = value;
}

