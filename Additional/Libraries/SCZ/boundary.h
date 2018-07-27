#ifndef BOUNDARY_H
#define BOUNDARY_H

//#include "global.h"
#include <QVector>
#include <QPointF>


class Boundary
{
public:
    static const int DEFAULT_INDEX = -1;
    Boundary();
    Boundary( QVector<QPointF> points );
    Boundary( const Boundary& boundary );
    ~Boundary();

    Boundary& operator=( const Boundary& b );

    int getStartIndex() const;
    void setStartIndex( int value );

    int getEndIndex() const;
    void setEndIndex( int value );

    QVector<QPointF>& getBoundary() const;
    void setBoundary( QVector<QPointF>* boundary );

    int previous( int index );
    int next( int index );
    int boundarySize();
private:
    int startIndex;
    int endIndex;
    QVector<QPointF>* m_Boundary = NULL;
};

#endif // BOUNDARY_H
