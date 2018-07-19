#ifndef MAP_H
#define MAP_H

#include <QString>

#include "gdal/ogrsf_frmts.h"
#include "SCZ/mapextractor.h"

class Map
{
public:
    /** CONSTANTS **/
    bool DEBUG_CLASS = false;

    /** Methods **/
    Map(GDALDataset *map);

    GDALDataset *getMap() const;
    void setMap(GDALDataset *value);

    OGREnvelope getWrapper() const;
    void setWrapper(const OGREnvelope &value);

    QString getName() const;
    void setName(const QString &value);

    QVector<Polygon> getLoadedPolygons() const;
    void setLoadedPolygons(const QVector<Polygon> &loadedPolygons);

private:
    GDALDataset* m_map;
    OGREnvelope m_wrapper;
    QString m_name;
    QVector<Polygon> m_loadedPolygons;

    void copyInfoFromFile();
    void extractMap(OGRLayer *layer);

};

#endif // MAP_H
