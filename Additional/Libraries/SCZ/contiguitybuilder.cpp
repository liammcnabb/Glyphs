#include "contiguitybuilder.h"

ContiguityBuilder::ContiguityBuilder( int searchType ) :
    Segment( searchType )
{
    //Nothing Specific for ContiguityBuilder. All params used in
    //constructor chaining.
}

QVector<ContiguousArea> ContiguityBuilder::sortContiguously(
    QVector<Polygon> unsorted )
{
    QVector<ContiguousArea> contigList;
    bool neighbourFound = false;

    while ( !unsorted.isEmpty() )
    {
        ContiguousArea newIsland;
        QVector<Polygon> current;
        current.append( unsorted.first() );
        unsorted.removeFirst();

        for ( int j = 0; j < contigList.size(); ++j )
        {
            if ( current.at(0).getBoundingBox().intersects(
                               contigList.at( j ).getBoundingBox() ) &&
                    isPartofContiguousArea(current.at(0), contigList.at( j ) ) )
            {
                for ( int k = 0; k < contigList.at( j ).polygons().size();
                        ++k )
                    current.append( contigList.at( j ).polygons().at( k ) );
                contigList.removeAt( j );
                --j;
                neighbourFound = false;
            }
        }
        newIsland.initPolygons( current );
        contigList.append( newIsland );

//        qDebug() << "ContigList size: " << contigList.size();
    }

    for( int i = 0; i < contigList.size(); ++i )
        contigList[i].sortedByArea();

    qDebug() << "Contig PL_counter =" << NeighbourChecker::PL_counter;
    qDebug() << "Contig BB_counter =" << NeighbourChecker::BB_counter;
    return contigList;
}

bool ContiguityBuilder::isPartofContiguousArea(Polygon p, ContiguousArea ca)
{
    for ( int i = 0; i < ca.polygons().size(); ++i )
    {
        if( NeighbourChecker::isNeighbour( p,
                                           ca.polygons().at( i ),
                                           Segment::searchType() ) )
        {
            return true;
        }
    }
    return false;
}

bool ContiguityBuilder::debugRender( QVector<ContiguousArea>* list,
                                        int debugMode,
                                        int highlight, int sleepMul )
{
//    if ( Segment::getDebugMode() )
//        Segment::renderer()->renderObject( list, NULL,
//                                              debugMode, highlight,
//                                              sleepMul );

    return true;
}
