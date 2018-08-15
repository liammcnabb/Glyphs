#ifndef POLYGON_H
#define POLYGON_H

#include <QDebug>
#include "LM/IntersectTester/AABB.h"
#include <QVector>
#include <stdio.h>

#include <QPointF>

class Polygon
{
public:
    Polygon();
    Polygon( QVector<QPointF> input ); //Default Constructor
    Polygon( const Polygon& obj ); //Copy Constructor
    ~Polygon(); //Destructor
    Polygon& operator= ( const Polygon& other ); //Copy assignment
    bool initialise();
    bool initPoints( QVector<QPointF> input );

    void toString();

    double edges() const;
    void setEdges( double edges );

    double area() const;
    void setArea( double area );

    double name() const;
    void setName( double name );

    int getNeighbour( int index );

    int neighbourSize();

    bool setNeighbour( int index, int value );

    QColor getDefaultColor() const;
    void setDefaultColor( const QColor& defaultColor );


    QVector<QPointF>& getPoints() const;
    void setPoints( QVector<QPointF>* points );

    QVector<int>& getNeighbourIndexes() const;
    void setNeighbourIndexes( QVector<int>* neighbourIndexes );

    AABB getBoundingBox() const;
    void setBoundingBox( AABB boundingBox );

    int getPolygonNumber() const;
    void setPolygonNumber( int polygonNumber );
    bool merged = false;
    bool neighbourCheck = false;


    int getNeighbourRank() const;
    void setNeighbourRank( int value );

    bool getNeighbourCheck() const;
    void setNeighbourCheck( bool value );

    bool setNeighbourIndex( int rank );
    float getMinX() const;
    void setMinX( float value );

    float getMaxX() const;
    void setMaxX( float value );

    float getMinY() const;
    void setMinY( float value );

    float getMaxY() const;
    void setMaxY( float value );

    bool neighbourIndexes( QVector<int> neighbours );
    QVector<int>& getParents() const;
    void setParents( QVector<int>* parents );

    bool giveParents( QVector<int> parents );
    QPointF* centroid() const;
    void setCentroid( QPointF* centroid );

    bool calculateCentroid();
    int islandIndex;

    QVector<QPointF>* m_points = NULL;
    bool operator <( const Polygon& other ) const;

    int getSortCriteria() const;
    void setSortCriteria( int value );

    int sortCriteria = 0;


    QVector<QString> getFields() const;
    void setFields( const QVector<QString>& value );

    QStringList getValues() const;
    void setValues( const QStringList value );

    QStringList values;

private:
    double m_edges;
    double m_area;
    double m_name;
    int m_neighbours[10];
    QVector<int>* m_neighbourIndexes = nullptr;
    QVector<int>* m_parents = NULL;
    AABB m_boundingBox;
    QVector<QString> fields;



    int m_polygonNumber;
    int neighbourRank;
    float minX = 0, maxX = 0, minY = 0, maxY = 0;
    QPointF* m_centroid = NULL;



    bool calculateArea();
    bool initBounds();

};

#endif // POLYGON_H
