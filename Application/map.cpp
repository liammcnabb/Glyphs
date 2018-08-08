#include "map.h"

Map::Map(GDALDataset* map)
{
    setMap(map);
    copyInfoFromFile();
}

Map::Map(GDALDataset* map, QVector<QStringList> data)
{
    setMap(map);
    setValueData(data);
    copyInfoFromFile();
}

Map::Map(GDALDataset* map, QVector<QStringList> data, QString recipeLoc)
{
    setMap(map);
    setValueData(data);
    setRecipeLoc(recipeLoc);
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
    splitContiguousRegions( getLoadedPolygons() );
    buildHierarchy(getContiguousRegions());
}

void Map::extractMap( OGRLayer* layer )
{
    if(DEBUG_CLASS)
        qDebug() << "Start: void Map::extractMap( OGRLayer* layer )";

    MapExtractor extractor = MapExtractor( layer );
    setLoadedPolygons(extractor.toVector());
    getMap()->Release();

    if( !getValueData().isEmpty() )
        setLoadedPolygons(linkDataToPolygons( getLoadedPolygons(),
                                              getValueData() ) );

    if(DEBUG_CLASS)
        qDebug() << "End: void Map::extractMap( OGRLayer* layer )";

    return;
}

QVector<Polygon> Map::linkDataToPolygons( QVector<Polygon> polygons,
                              QVector<QStringList> data )
{
    if(DEBUG_CLASS)
        qDebug() << "Start: void Map::linkDataToPolygons( QVector<Polygon> polygons,"
                    "QVector<QStringList> data )";

    int linkColumn = 0;
    int linkedShapesCounter = 0;
    bool linkedFlag = false;

    //Save StringList to correct polygon
    for ( int i = 0; i < polygons.size(); ++i )
    {
        for ( int j = 0; j < data.size(); ++j )
        {
            if( !data.at(j).isEmpty() && polygons.at( i ).getFields().contains(
                        data.at( j ).at( linkColumn ) ) )
            {
                QStringList newValue = data.at( j );
                polygons[i].values = newValue;
                ++linkedShapesCounter;
                if( DEBUG_CLASS )
                {
                    if (linkedShapesCounter == polygons.size())
                        qDebug() << linkedShapesCounter << "/" << polygons.size()
                             << "linked (" << 100.0000 << "% ).";
                    else
                        qDebug() << linkedShapesCounter << "/" << polygons.size()
                         << "linked (" << ( ( double )linkedShapesCounter /
                            ( double )polygons.size() * 100 ) << "% ).";
                }

                linkedFlag = true;
                break;
            }
        }


        if ( DEBUG_CLASS && !linkedFlag  )
        {
            qDebug() << "polygon[" << i << "] Not Linked.";
            qDebug() << polygons.at( i ).getFields().at( 0 );
        }
        linkedFlag = false;
    }

    if( linkedShapesCounter  == 0 )
        qDebug() << E << NO_LINKED_DATA;

    if(DEBUG_CLASS)
        qDebug() << "End: void Map::linkDataToPolygons( QVector<Polygon>"
                    " polygons, QVector<QStringList> data )";

    return polygons;
}

void Map::splitContiguousRegions( QVector<Polygon> list )
{
    if(DEBUG_CLASS)
        qDebug() << "Begin: void Map::splitContiguousRegions("
                    " QVector<Polygon> list )";

    ContiguityBuilder builder(0);
    QVector<ContiguousArea> contigs = builder.sortContiguously(list);
    setContiguousRegions(contigs);

    if(DEBUG_CLASS)
        qDebug() << "End: void Map::splitContiguousRegions("
                    " QVector<Polygon> list )";

    return;
}

void Map::buildHierarchy( QVector<ContiguousArea> list)
{
    QVector<TreeNode> trees;
    if(DEBUG_CLASS)
        qDebug() << "Begin: void Map::buildHierarchy("
                    " QVector<ContiguousArea> list )";

    TreeBuilder builder = TreeBuilder(0,0,getRecipeType(),getRecipeLoc(),1);

    QVector<QString>* instructions = new QVector<QString>();
    CrfReader reader(getRecipeLoc().toStdString() );
    QVector<CrfRow>* loadedRecipe;
    if ( getRecipeType() == RECIPE_LOAD )
        {
            loadedRecipe = new QVector<CrfRow>( reader.read(
                    getRecipeLoc().toUtf8().constData( ) ) );
        }

    for( int i = 0; i < list.size(); ++i )
        trees.append( builder.createBinaryTree(
                          list.at(i).polygons(),
                          instructions, loadedRecipe) );

    if ( getRecipeType() == RECIPE_SAVE )
       {
           CrfWriter writer( getRecipeLoc().toUtf8().constData() );
           writer.write( instructions );
       }

    setHierarchies(trees);

       delete instructions;
       if ( getRecipeType() == RECIPE_LOAD )
           delete loadedRecipe;

    if(DEBUG_CLASS)
        qDebug() << "End: void Map::buildHierarchy("
                    " QVector<ContiguousArea> list )";
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

QVector<QStringList> Map::getValueData() const
{
    return valueData;
}

void Map::setValueData(const QVector<QStringList> &value)
{
    valueData = value;
}

QVector<ContiguousArea> Map::getContiguousRegions() const
{
    return m_contiguousRegions;
}

void Map::setContiguousRegions(const QVector<ContiguousArea> &contiguousRegions)
{
    m_contiguousRegions = contiguousRegions;
}

QString Map::getRecipeLoc() const
{
    return m_recipeLoc;
}

void Map::setRecipeLoc(const QString &recipeLoc)
{
    m_recipeLoc = recipeLoc;
}

int Map::getRecipeType() const
{
    return m_recipeType;
}

void Map::setRecipeType(int recipeType)
{
    m_recipeType = recipeType;
}

QVector<TreeNode> Map::getHierarchies() const
{
    return m_hierarchies;
}

void Map::setHierarchies(const QVector<TreeNode> &hierarchies)
{
    m_hierarchies = hierarchies;
}
