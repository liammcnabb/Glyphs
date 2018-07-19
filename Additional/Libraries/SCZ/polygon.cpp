#include "polygon.h"

Polygon::Polygon()
{
    m_points = new QVector<QPointF>();
    m_centroid = new QPointF();
    m_boundingBox = AABB();

    minX = minY = INT_MAX;
    maxX = maxY = INT_MIN;
}

Polygon::Polygon( const Polygon& obj )
{
    m_edges = obj.edges();
    m_area = obj.area();
    minX = obj.getMinX();
    minY = obj.getMinY();
    maxX = obj.getMaxX();
    maxY = obj.getMaxY();
    sortCriteria = obj.sortCriteria;
    fields = obj.getFields();
    values = obj.values;
    m_boundingBox = obj.getBoundingBox();
    m_points = new QVector<QPointF>( m_edges );
    std::copy( obj.m_points->begin(), obj.m_points->end(),
               m_points->begin() );
    m_centroid = new QPointF( *obj.centroid() );
}

Polygon::~Polygon()
{
    delete m_points;
    delete m_centroid;
}

Polygon& Polygon::operator=( const Polygon& other )
{
    if( this == &other )
        return *this;

    m_edges = other.edges();
    m_area = other.area();
    minX = other.getMinX();
    minY = other.getMinY();
    maxX = other.getMaxX();
    maxY = other.getMaxY();
    fields = other.getFields();
    values = other.values;
    sortCriteria = other.sortCriteria;
    m_points->resize( int( m_edges ) );
    std::copy( other.m_points->begin(), other.m_points->end(),
               m_points->begin() );
    m_centroid->setX( other.centroid()->x() );
    m_centroid->setY( other.centroid()->y() );

    m_boundingBox.overwrite( other.getBoundingBox() );

    return *this;
}

Polygon::Polygon( QVector<QPointF> input )
{
    m_points = new QVector<QPointF>( input );
    m_centroid = new QPointF();

    initBounds();
    setEdges( getPoints().size() );
    calculateArea();
    calculateCentroid();
}

bool Polygon:: operator <( const Polygon& other ) const
{
    if ( sortCriteria == 0 )
        return area() < other.area();
    return centroid()->x() + centroid()->y() <
           other.centroid()->x() + centroid()->y();
}


bool Polygon::initialise()
{
    return true;
}

bool Polygon::initPoints( QVector<QPointF> input )
{
    m_points->clear();
    m_points->resize( input.size() );
    std::copy( input.begin(), input.end(), m_points->begin() );
    initBounds();
    setEdges( getPoints().size() );
    calculateArea();
    calculateCentroid();

    m_points->squeeze();
    return true;
}

bool Polygon::calculateCentroid()
{
    m_centroid->setX( ( getMinX() + ( fabs( getMaxX() - getMinX() ) /
                                      2 ) ) );
    m_centroid->setY( ( getMinY() + ( fabs( getMaxY() - getMinY() ) /
                                      2 ) ) );

    return true;
}

bool Polygon::neighbourIndexes( QVector<int> neighbours )
{
    if( neighbours.size() != 0 )
    {
        m_neighbourIndexes = new QVector<int>( neighbours );
        return true;
    }

    return false;
}

bool Polygon::giveParents( QVector<int> parents )
{
    m_parents = new QVector<int>( parents );
    return true;
}

QPointF* Polygon::centroid() const
{
    return m_centroid;
}

void Polygon::setCentroid( QPointF* centroid )
{
    m_centroid = centroid;
}

QVector<int>& Polygon::getParents() const
{
    return *m_parents;
}

void Polygon::setParents( QVector<int>* parents )
{
    m_parents = parents;
}

bool Polygon::calculateArea()
{
    QVector<double> calc1, calc2;

    for ( QVector<QPointF>::const_iterator it = getPoints().begin();
            it < getPoints().end();
            ++it )
    {
        calc1.append( it->x() );
        calc2.append( it->y() );
    }

    int polygonZero;
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

    if( polygonArea == 0 )
        polygonZero++;

    if( polygonArea < 0 )
        polygonArea = polygonArea - ( polygonArea * 2 );

    setArea( polygonArea );
    return true;
}

bool Polygon::initBounds()
{
    float minimumX, minimumY, maximumX, maximumY;
    minimumX = minimumY = maximumX = maximumY = 0;

    for ( QVector<QPointF>::const_iterator it = getPoints().begin();
            it < getPoints().end();
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

    m_boundingBox = AABB( minimumX, maximumX, minimumY, maximumY );


    return true;
}

bool Polygon::setNeighbourIndex( int rank )
{
    neighbourCheck = true;
    setNeighbourRank( rank );

    return true;
}

float Polygon::getMinX() const
{
    return minX;
}

void Polygon::setMinX( float value )
{
    minX = value;
}

float Polygon::getMaxX() const
{
    return maxX;
}

void Polygon::setMaxX( float value )
{
    maxX = value;
}

float Polygon::getMinY() const
{
    return minY;
}

void Polygon::setMinY( float value )
{
    minY = value;
}

float Polygon::getMaxY() const
{
    return maxY;
}

void Polygon::setMaxY( float value )
{
    maxY = value;
}

QVector<int>& Polygon::getNeighbourIndexes() const
{
    return *m_neighbourIndexes;
}

void Polygon::setNeighbourIndexes( QVector<int>*
                                   neighbourIndexes )
{
    m_neighbourIndexes = neighbourIndexes;
}

int Polygon::getPolygonNumber() const
{
    return m_polygonNumber;
}

void Polygon::setPolygonNumber( int polygonNumber )
{
    m_polygonNumber = polygonNumber;
}

bool Polygon::getNeighbourCheck() const
{
    return neighbourCheck;
}

void Polygon::setNeighbourCheck( bool value )
{
    neighbourCheck = value;
}

int Polygon::getNeighbourRank() const
{
    return neighbourRank;
}

void Polygon::setNeighbourRank( int value )
{
    neighbourRank = value;
}

int Polygon::getNeighbour( int index )
{
    if ( index > neighbourSize() )
    {
//        qDebug() << ERROR << ERROR_INDEX_LARGE;
        return m_neighbours[neighbourSize() - 1];
    }
    else if ( index < 0 )
    {
//        qDebug() << ERROR << ERROR_INDEX_SMALL;
        return m_neighbours[0];
    }
    else
        return m_neighbours[index];
}

bool Polygon::setNeighbour( int index, int value )
{
    if ( index < 0 )
    {
//        qDebug() << ERROR << ERROR_INDEX_SMALL;
        return false;
    }
    else if ( index > neighbourSize() )
    {
//        qDebug() << ERROR << ERROR_INDEX_LARGE;
        return false;
    }
    else
    {
        m_neighbours[index] = value;
        return true;
    }
}

double Polygon::edges() const
{
    return m_edges;
}

void Polygon::setEdges( double edges )
{
    m_edges = edges;
}

double Polygon::area() const
{
    return m_area;
}

void Polygon::setArea( double area )
{
    m_area = area;
}

double Polygon::name() const
{
    return m_name;
}

void Polygon::setName( double name )
{
    m_name = name;
}

QVector<QPointF>& Polygon::getPoints() const
{
    return *m_points;
}

void Polygon::setPoints( QVector<QPointF>* points )
{
    m_points = points;
}

int Polygon::neighbourSize()
{
    return sizeof( m_neighbours ) / sizeof( m_neighbours[0] );
}

int Polygon::getSortCriteria() const
{
    return sortCriteria;
}

void Polygon::setSortCriteria( int value )
{
    sortCriteria = value;
}

QVector<QString> Polygon::getFields() const
{
    return fields;
}

void Polygon::setFields( const QVector<QString>& value )
{
    fields = value;
}

QStringList Polygon::getValues() const
{
    return values;
}

void Polygon::setValues( const QStringList value )
{
    values = value;
}

AABB Polygon::getBoundingBox() const
{
    return m_boundingBox;
}

void Polygon::setBoundingBox( AABB boundingBox )
{
    m_boundingBox = boundingBox;
}

void Polygon::toString()
{
    qDebug() << "Polygon: ";
    qDebug() << "Edges: " << edges();
    qDebug() << "Area: " << area();
    qDebug() << "Points: " << getPoints();
    qDebug() << "Neighbours: " << getNeighbourIndexes();
}


