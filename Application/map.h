#ifndef MAP_H
#define MAP_H

#include <QString>

#include "gdal/ogrsf_frmts.h"
#include "SCZ/mapextractor.h"
#include "personalerrors.cpp"

class Map
{
public:
    /** CONSTANTS **/
    bool DEBUG_CLASS = false;

    /** Methods **/
    Map(GDALDataset *map );
    Map(GDALDataset *map, QVector<QStringList> data);

    GDALDataset *getMap() const;
    void setMap(GDALDataset *value);

    OGREnvelope getWrapper() const;
    void setWrapper(const OGREnvelope &value);

    QString getName() const;
    void setName(const QString &value);

    QVector<Polygon> getLoadedPolygons() const;
    void setLoadedPolygons(const QVector<Polygon> &loadedPolygons);

    QVector<QStringList> getValueData() const;
    void setValueData(const QVector<QStringList> &value);

private:
    GDALDataset* m_map;
    OGREnvelope m_wrapper;
    QString m_name;
    QVector<Polygon> m_loadedPolygons;
    QVector<QStringList> valueData;

    void copyInfoFromFile();
    void extractMap(OGRLayer *layer);
    QVector<Polygon> linkDataToPolygons(QVector<Polygon> polygons,
                            QVector<QStringList> data);
};

#endif // MAP_H
