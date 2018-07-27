#include "contiguitybuilder.h"

ContiguityBuilder::ContiguityBuilder( int searchType ,
        bool debugMode ) :
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
            for ( int k = 0; k < contigList.at( j ).polygons().size(); ++k )
            {
                if( NeighbourChecker::isNeighbour( current.at( 0 ),
                                                   contigList.at( j ).polygons().at( k ),
                                                   Segment::searchType() ) )
                {
                    neighbourFound = true;
                    break;
                }
            }

            if ( neighbourFound )
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
    }

    for( int i = 0; i < contigList.size(); ++i )
        contigList[i].sortedByArea();

    return contigList;
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
