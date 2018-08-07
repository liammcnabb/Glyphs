#include "contiguousarea.h"

ContiguousArea::ContiguousArea()
{
    m_polygons = new QVector<Polygon>();
}

ContiguousArea::ContiguousArea( const ContiguousArea& obj )
{
    m_polygons = new QVector<Polygon>( obj.polygons().size() );
    std::copy( obj.polygons().begin(),
               obj.polygons().end(),
               m_polygons->begin() );
    setBoundingBox(obj.getBoundingBox());
}

ContiguousArea& ContiguousArea::operator=( const ContiguousArea&
        other )
{
    if ( this == &other )
        return *this;

    m_polygons->resize( other.polygons().size() );
    std::copy( other.polygons().begin(),
               other.polygons().end(),
               m_polygons->begin() );
    setBoundingBox(other.getBoundingBox());

    return *this;
}

ContiguousArea::~ContiguousArea()
{
    delete m_polygons;
}

bool ContiguousArea::initPolygons( QVector<Polygon> input )
{
    m_polygons->clear();
    m_polygons->resize( input.size() );
    std::copy( input.begin(), input.end(), m_polygons->begin() );
    //    m_polygons = new QVector<Polygon>(input);

    setupAABB(m_polygons);
    return true;
}

void ContiguousArea::setupAABB(QVector<Polygon> *list)
{
    float minX = std::numeric_limits<float>::max();
    float maxX = -std::numeric_limits<float>::max();
    float minY = std::numeric_limits<float>::max();
    float maxY = -std::numeric_limits<float>::max();

    for(int i = 0; i < list->size(); ++i)
    {
        minX = std::min(minX, list->at(i).getMinX());
        maxX = std::max(maxX, list->at(i).getMaxX());
        minY = std::min(minY, list->at(i).getMinY());
        maxY = std::max(maxY, list->at(i).getMaxY());
    }

    setBoundingBox(AABB(minX,maxX,minY,maxY));
}

bool ContiguousArea::sortedByArea()
{
    //    bool flag = false;
    //    QVector<Polygon> sortedList = *m_polygons;


    //    sortedList.append(polygons().first());

    //    for ( int i = 1; i < polygons().size(); ++i )
    //    {
    //        Polygon p = polygons().at(i);
    //        for ( int j = 0; j < sortedList.size(); ++j)
    //        {
    //            if ( polygons().at(i) < sortedList.at(j) )
    //            {
    //                if (j == 0)
    //                    sortedList.prepend(p);
    //                else
    //                    sortedList.insert(j, p);
    //                flag=true;
    //                break;
    //            }
    //        }
    //        if (!flag)
    //        {
    //            sortedList << p;
    //        }
    //        flag = false;
    //    }
    //    m_polygons->clear();
    //    m_polygons->append( QVector<Polygon>(sortedList) );
    qSort( *m_polygons );
    return true;
}

AABB ContiguousArea::getBoundingBox() const
{
    return m_boundingBox;
}

void ContiguousArea::setBoundingBox(const AABB &boundingBox)
{
    m_boundingBox = boundingBox;
}

bool ContiguousArea::initSortedIndexes() const
{
    sortedIndexes().empty();
    
    sortedIndexes().append( 0 );
    
    for ( int i = 1; i < polygons().size(); ++i )
    {
        for ( int j = 0; j < sortedIndexes().size(); ++j )
        {
            if ( polygons( i ).area() < polygons( sortedIndexes().at(
                    j ) ).area() )
            {
                sortedIndexes().insert( j, i );
                break;
            }
        }
        if ( !sortedIndexes().contains( i ) )
            sortedIndexes().push_back( i );
    }

    return true;
}


const Polygon& ContiguousArea::polygons( int value ) const
{
    if ( value >= 0 && value < polygons().size() )
        return polygons().at( value );
    else
        qDebug() <<
                 "ERROR: Out of Bounds call of ContiguousArea.polygons()";

    return polygons().at( 0 );
}

bool ContiguousArea::treeReadyFlag() const
{
    return m_treeReadyFlag;
}

void ContiguousArea::setTreeReadyFlag( bool treeReadyFlag )
{
    m_treeReadyFlag = treeReadyFlag;
}

QVector<Polygon>& ContiguousArea::polygons() const
{
    return *m_polygons;
}

QVector<int>& ContiguousArea::sortedIndexes() const
{
    return *m_sortedIndexes;
}

void ContiguousArea::setSortedIndexes( QVector<int>*
                                       sortedIndexes )
{
    m_sortedIndexes = sortedIndexes;
}

void ContiguousArea::setPolygons( QVector<Polygon>* polygons )
{
    m_polygons = polygons;
}
