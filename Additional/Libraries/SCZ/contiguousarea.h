#ifndef CONTIGUOUSAREA_H
#define CONTIGUOUSAREA_H

//#include "global.h"
#include <QDebug>
#include "polygon.h"
#include <QVector>


class ContiguousArea
{
public:
    ContiguousArea();
    ContiguousArea( const ContiguousArea& obj );
    ContiguousArea& operator=( const ContiguousArea& other );
    ~ContiguousArea();

    QVector<Polygon>& polygons() const;
    void setPolygons( QVector<Polygon>* polygons );

    bool initPolygons( QVector<Polygon> input );

    bool treeReadyFlag() const;
    void setTreeReadyFlag( bool treeReadyFlag );

    const Polygon& polygons( int value ) const;

    QVector<int>& sortedIndexes() const;
    void setSortedIndexes( QVector<int>* sortedIndexes );

    bool initSortedIndexes() const;
    bool sortedByArea();
private:
    QVector<Polygon>* m_polygons = NULL;
    QVector<int>* m_sortedIndexes = NULL;
    bool m_treeReadyFlag = false;

};

#endif // CONTIGUOUSAREA_H
