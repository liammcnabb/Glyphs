#ifndef MAP_H
#define MAP_H

#include <QString>

#include "gdal/ogrsf_frmts.h"
#include "SCZ/mapextractor.h"
#include "SCZ/contiguousarea.h"
#include "SCZ/contiguitybuilder.h"
#include "SCZ/treebuilder.h"
#include "LM/crfwriter.h"


class Map
{
public:
    /** CONSTANTS **/
    bool DEBUG_CLASS = true;
    static const int RECIPE_NONE = 0;
    static const int RECIPE_SAVE = 1;
    static const int RECIPE_LOAD = 2;

    /** Methods **/
    Map(GDALDataset *map );
    Map(GDALDataset *map, QVector<QStringList> data);
    Map(GDALDataset *map, QVector<QStringList> data, QString recipeLoc);

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

    QVector<ContiguousArea> getContiguousRegions() const;
    void setContiguousRegions(const QVector<ContiguousArea> &contiguousRegions);


    QString getRecipeLoc() const;
    void setRecipeLoc(const QString &recipeLoc);

    int getRecipeType() const;
    void setRecipeType(int recipeType);

    QVector<TreeNode> getHierarchies() const;
    void setHierarchies(const QVector<TreeNode> &hierarchies);

private:
    GDALDataset* m_map;
    OGREnvelope m_wrapper;
    QString m_name;
    QVector<Polygon> m_loadedPolygons;
    QVector<QStringList> valueData;
    QVector<ContiguousArea> m_contiguousRegions;
    QVector<TreeNode> m_hierarchies;
    QString m_recipeLoc;
    int m_recipeType = RECIPE_LOAD;

    void copyInfoFromFile();
    void extractMap(OGRLayer *layer);
    QVector<Polygon> linkDataToPolygons(QVector<Polygon> polygons,
                                        QVector<QStringList> data);
    void splitContiguousRegions(QVector<Polygon> list);
    void buildHierarchy(QVector<ContiguousArea> list);
};

#endif // MAP_H
