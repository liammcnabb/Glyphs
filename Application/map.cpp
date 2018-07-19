#include "map.h"

Map::Map(GDALDataset* map)
{
    setMap(map);
    copyInfoFromFile();

}

void Map::copyInfoFromFile()
{
    OGRLayer* layer = getMap()->GetLayer( 0 );
    OGREnvelope envelope;
    layer->GetExtent( &envelope );
    setWrapper( envelope );
    setName( layer->GetName() );

    extractMap( layer );
}

void Map::extractMap( OGRLayer* layer )
{
    if(DEBUG_CLASS)
        qDebug() << "Start: void Map::extractMap( OGRLayer* layer )";

    MapExtractor extractor = MapExtractor( layer );
    setLoadedPolygons(extractor.toVector());
    getMap()->Release();

//    if( getDataType() == DATA_LOAD )
//        linkDataToPolygons( m_defaultPolygons, getData() );
    if(DEBUG_CLASS)
        qDebug() << "End: void Map::extractMap( OGRLayer* layer )";

    return;
}

GDALDataset *Map::getMap() const
{
    return m_map;
}

void Map::setMap(GDALDataset *value)
{
    m_map = value;
}

OGREnvelope Map::getWrapper() const
{
    return m_wrapper;
}

void Map::setWrapper(const OGREnvelope &value)
{
    m_wrapper = value;
}

QString Map::getName() const
{
    return m_name;
}

void Map::setName(const QString &value)
{
    m_name = value;
}

QVector<Polygon> Map::getLoadedPolygons() const
{
    return m_loadedPolygons;
}

void Map::setLoadedPolygons(const QVector<Polygon> &loadedPolygons)
{
    m_loadedPolygons = loadedPolygons;
}
