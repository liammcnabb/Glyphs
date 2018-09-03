#ifndef MAPEXTRACTOR_H
#define MAPEXTRACTOR_H

#include "gdal/ogrsf_frmts.h"
#include "SCZ/polygon.h"
#include "SCZ/segment.h"

#include <QVector>
#include <QPointF>

class MapExtractor : public Segment
{
public:
    /**
     * @brief SCZMapExtractor::SCZMapExtractor Used to extract information from
     * from an OGRLayer (refer to fileloader class).
     * @param layer layer to extract map data from
     * @param dataType value data user option (no data/load data)
     * @param dataLoc location of data for if data type = load data
     */
    MapExtractor(OGRLayer* layer );
    /**
     * @brief SCZMapExtractor::toVector the primary method used to initialise
     * extraction of layer into a QVector list
     * @return A list of Polygons extracted from the the OGRLayer
     */
    QVector<Polygon> toVector();
private:
    OGRLayer* layer;
    int dataType = 0;
    QString dataLoc = "";

    /**
     * @brief SCZMapExtractor::accumulatePoints extract points and save to vector
     * @param ring ring of points taken from OGRFeature
     * @return return points as vector, after being forced as to be clockwise
     */
    QVector<QPointF> accumulatePoints(const OGRLinearRing *ring );
    /**
     * @brief SCZMapExtractor::accumulatePoints exctract points to current vector of points
     * @param ring ring of points taken from OGRFeature
     * @param points current list of points to append to
     */
    void accumulatePoints(const OGRLinearRing *ring,
                           QVector<QPointF>* points );
    /**
     * @brief SCZMapExtractor::extractPolygonPoints extract points from a specific
     * feature and add to the polygonList (may be more than one dependent on
     *  geometry type )
     * @param feature feature to extract polygons from
     * @param polygonList current polygonList to append new polygons to
     * @param fields data fields related to feature
     */
    void extractPolygonPoints(OGRFeature* feature,
                               QVector<Polygon>* polygonList,
                               QVector<QString>* fields );
    /**
     * @brief SCZMapExtractor::ArrangeClockwise checks if points are in clockwise orientation.
     * If not, reverse the list
     * @param input list of points
     * @return clockwise list of points;
     */
    QVector<QPointF> arrangeClockwise( QVector<QPointF> input );

};

#endif // MAPEXTRACTOR_H
