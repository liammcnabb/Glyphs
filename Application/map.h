#ifndef MAP_H
#define MAP_H

#include <QString>

#include "gdal/ogrsf_frmts.h"
#include "SCZ/mapextractor.h"
#include "SCZ/contiguousarea.h"
#include "SCZ/contiguitybuilder.h"
#include "SCZ/treebuilder.h"
#include "LM/crfwriter.h"
#include "LM/IntersectTester/IntersectTester.h"
#include "LM/IntersectTester/AABB.h"


class Map
{
public:
    /** CONSTANTS **/
    bool DEBUG_CLASS = true;
    /**
     * @brief RECIPE_NONE Recipe state when recipe is not applied
     */
    static const int RECIPE_NONE = 0;
    /**
     * @brief RECIPE_SAVE recipe state when recipe is saved to location
     */
    static const int RECIPE_SAVE = 1;
    /**
     * @brief RECIPE_LOAD recipe state when recipe is loaded from location
     */
    static const int RECIPE_LOAD = 2;

    /** Methods **/
    Map(GDALDataset *map );
    Map(GDALDataset *map, QVector<QStringList> data);
    Map(GDALDataset *map, QVector<QStringList> data, QString recipeLoc);

    /**
     * @brief getMap getter method for the GDALDataset
     * @return GDALDataset holding loaded map details
     */
    GDALDataset *getMap() const;
    /**
     * @brief setMap setter method for the GDALDataset
     * @param value GDALDataset holding loaded map details
     */
    void setMap(GDALDataset *value);

    /**
     * @brief getWrapper getter method holds the canvas envelope in OGREnvelope format
     * (minX, maxX, minY, maxY)
     * @return the default canvas envelope in OGREnvelope format
     */
    OGREnvelope getWrapper() const;
    /**
     * @brief setWrapper setter method sets the canvas envelope in OGREnvelope format
     * (minX, maxX, minY, maxY)
     * @param value holding canvas envelope in OGREnvelope format
     */
    void setWrapper(const OGREnvelope &value);

    /**
     * @brief getName getter method holds the name of the loaded map
     * @return the name of the loaded map
     */
    QString getName() const;
    /**
     * @brief setName setter method to hold the name of the loaded map
     * @param value the new name of the loaded map
     */
    void setName(const QString &value);

    /**
     * @brief getLoadedPolygons getter method for the loaded polygons
     * as a vector of Polygons
     * @see Polygon.h
     * @return list of loaded polygons
     */
    QVector<Polygon> getLoadedPolygons() const;
    /**
     * @brief setLoadedPolygons setter method for the loaded polygons
     * as a vector of Polygons
     * @see Polygon.h
     * @param loadedPolygons
     */
    void setLoadedPolygons(const QVector<Polygon> &loadedPolygons);

    /**
     * @brief getValueData getter method for the loaded data values
     * @return the loaded data values as a vector of string lists.
     */
    QVector<QStringList> getValueData() const;
    /**
     * @brief setValueData setter method for the loaded data values
     * @param value the new values fo the loaded data values as a
     * vector of string lists.
     */
    void setValueData(const QVector<QStringList> &value);

    /**
     * @brief getContiguousRegions getter method for the loaded polygons
     * into sorted contiguous regions as a vector of ContiguousArea
     * @return  a vector of contiguousArea
     */
    QVector<ContiguousArea> getContiguousRegions() const;
    /**
     * @brief setContiguousRegions setter method for the sorted polygons in
     * the form of contiguous regions
     * @param contiguousRegions new values for the list of contiguous areas
     */
    void setContiguousRegions(const QVector<ContiguousArea> &contiguousRegions);

    /**
     * @brief getRecipeLoc getter method for the location of the crf file to
     * enhance performance of build method.
     * @return String directory of choropleth recipe file
     */
    QString getRecipeLoc() const;
    /**
     * @brief setRecipeLoc setter method for the location of the crf file to
     * enhance performance of build method.
     * @param recipeLoc new location of choropleth recipe file
     */
    void setRecipeLoc(const QString &recipeLoc);

    /**
     * @brief getRecipeType getter method for the current state of the recipe
     * method (Save to recipe or Load from recipe)
     * @see Map::RECIPE_SAVE
     * @see Map::RECIPE_LOAD
     * @return integer representing recipe state
     */
    int getRecipeType() const;
    /**
     * @brief setRecipeType setter method for the current state of the recipe
     * method (Save to recipe or Load from recipe)
     * @see Map::RECIPE_SAVE
     * @see Map::RECIPE_LOAD
     * @param recipeType new value for recipe state (for this application,
     *  not used)
     */
    void setRecipeType(int recipeType);

    /**
     * @brief getHierarchies getter method for the modified polygons using
     * the dynamic choropleth map algortihm
     * @see TreeBuilder.h
     * @return vector of hierarchical data structures
     */
    QVector<TreeNode> getHierarchies() const;
    /**
     * @brief setHierarchies setter method for the modified polygons using
     * the dynamic choropleth map algorithm
     * @see TreeBuilder.h
     * @param hierarchies vector of hierarchical data structures
     */
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

    /**
     * @brief copyInfoFromFile method used to extract information from map and
     * begin process
     */
    void copyInfoFromFile();
    /**
     * @brief extractMap method to extract data from the map layer and save the
     * data to the vector of polygons. Also calls Map::linkDataToPolygons(QVector<Polygon> polygons, QVector<QStringList> data);
     * @param layer
     */
    void extractMap(OGRLayer *layer);
    /**
     * @brief linkDataToPolygons moves through data to find matching headers.
     * If found, append data values to the string lists
     * @param polygons list of polygons to append the data to
     * @param data data values to append to polygons
     * @return updated polygon list with appended values.
     */
    QVector<Polygon> linkDataToPolygons(QVector<Polygon> polygons,
                                        QVector<QStringList> data);
    /**
     * @brief splitContiguousRegions calls the contiguity builder to sort the
     * polygons into contiguous regions
     * @see ContiguityBuilder.h
     * @param list a list of unsorted polygons
     */
    void splitContiguousRegions(QVector<Polygon> list);
    /**
     * @brief buildHierarchy method  prepares and calls treebuilder to create
     * hierarchical data structure of the loaded polygons in TreeNode format
     * @see treebuilder.h
     * @param list list of sorted, contiguous areas
     */
    void buildHierarchy(QVector<ContiguousArea> list);
};

#endif // MAP_H
