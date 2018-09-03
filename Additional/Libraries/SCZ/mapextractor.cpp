#include "mapextractor.h"

MapExtractor::MapExtractor(OGRLayer* layer) :
    Segment( 0 )
{
    this->layer = layer;
}

QVector<Polygon> MapExtractor::toVector()
{
    OGRFeature* feature;
    feature = layer->GetNextFeature();
    QVector<Polygon> polygonList;

    while( ( feature != NULL ) )
    {
        QVector<QString> fields;
        for( int i = 0; i < feature->GetFieldCount(); ++i )
            fields.append( feature->GetFieldAsString( i ) );

        extractPolygonPoints( feature, &polygonList, &fields );
        feature = layer->GetNextFeature();
    }
    return polygonList;
}

void MapExtractor::extractPolygonPoints( OGRFeature* feature,
        QVector<Polygon>* polygonList,
        QVector<QString>* fields )
{
    Polygon currentPolygon = Polygon();
    OGRGeometry* geometry = feature->GetGeometryRef();
    QVector<QPointF> points = QVector<QPointF>();

    switch( wkbFlatten( geometry->getGeometryType() ) )
    {
        case wkbPolygon:
        {
            OGRPolygon* polygon = ( OGRPolygon* ) geometry;
            OGRLinearRing *extRing = polygon->getExteriorRing();
            extRing->closeRings();
            if ( extRing->getNumPoints() < 5 )
                return;
            points = accumulatePoints( extRing );

            for ( int j = 0; j < polygon->getNumInteriorRings(); ++j )
            {
                OGRLinearRing* intRing = polygon->getInteriorRing( j );
                intRing->closeRings();

                /** Hardcoded fix, comment and uncomment as necessary. **/
                if ( intRing->getNumPoints() > 10 )
                    accumulatePoints( intRing, &points );
            }

            points.squeeze();
            currentPolygon = Polygon( points );
            currentPolygon.setFields( *fields );
            polygonList->push_back( currentPolygon );

            break;
        }
        case wkbMultiPolygon:
        {
            OGRGeometryCollection* collection =
                ( OGRGeometryCollection* ) geometry;

            for ( int i = 0; i < /*collection->getNumGeometries()*/1; i++ )
            {
                OGRPolygon* poly = ( OGRPolygon* ) collection->getGeometryRef(
                                       i );
                OGRLinearRing *extRing = poly->getExteriorRing();
                extRing->closeRings();
                if ( extRing->getNumPoints() < 5 )
                    return;
                points = accumulatePoints( extRing );

                for ( int j = 0; j < poly->getNumInteriorRings(); ++j )
                {
                    OGRLinearRing* intRing = poly->getInteriorRing( j );
                    intRing->closeRings();

                    /** Hardcoded fix, comment and uncomment as necessary. **/
                    if ( intRing->getNumPoints() > 10 )
                        accumulatePoints( intRing, &points );
                }

                points.squeeze();
                currentPolygon = Polygon( points );
                currentPolygon.setFields( *fields );
                polygonList->push_back( currentPolygon );

            }
            break;
        }
        default:
            qDebug() << "UNWORKED GEOMETRY TYPE: " <<
                     geometry->getGeometryType();
            break;
    }

    delete geometry;
    return;
}

QVector<QPointF> MapExtractor::accumulatePoints(
    const OGRLinearRing* ring )
{
    QVector<QPointF> points = QVector<QPointF>();
    double x, y;

    for ( int i = 0; i < ring->getNumPoints(); i++ )
    {
        x = ring->getX( i );
        y = ring->getY( i );
        points.append( QPointF( x, y ) );
    }
    points = arrangeClockwise( points );
    return points;
}

void MapExtractor::accumulatePoints( const OGRLinearRing*
                                        ring,
                                        QVector<QPointF>* points )
{
    double x, y;
    QVector<QPointF> tempPoints;

    for ( int i = 0; i < ring->getNumPoints(); i++ )
    {
        x = ring->getX( i );
        y = ring->getY( i );
        tempPoints.append( QPointF( x, y ) );
    }

    tempPoints = arrangeClockwise( tempPoints );

    for ( int i = 0; i < tempPoints.size(); ++i )
        points->append( tempPoints.at( i ) );

    return;
}

QVector<QPointF> MapExtractor::arrangeClockwise(
    QVector<QPointF> input )
{
    double rotation = 0;
    double POSITIVE_NUMBERS = 0;
    QVector<QPointF> clockwise;

    for ( int i = 0; i < input.size() - 1; ++i )
        rotation += ( ( input.at( i + 1 ).x() - input.at( i ).x() ) *
                      ( input.at( i + 1 ).y() + input.at( i ).y() ) );

    rotation += ( ( input.first().x() - input.last().x() ) *
                  ( input.first().y() + input.last().y() ) );

    if ( rotation < POSITIVE_NUMBERS )
        for( int i = input.size(); i > 0; --i )
            clockwise.append( input.at( i - 1 ) );
    else
        for( int i = 0; i < input.size(); ++i )
            clockwise.append( input.at( i ) );

    return clockwise;
}

