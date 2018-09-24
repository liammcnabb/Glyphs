#ifndef SCZTREEBUILDER_H
#define SCZTREEBUILDER_H

//#include "global.h"
#include "treenode.h"
#include "linkedlist.h"
#include "polygon.h"
#include "neighbourchecker.h"
#include "LM/crfreader.h"
#include "segment.h"
//#include "objectrenderer.h"

#include <QDebug>
#include <QString>
#include <QVector>
#include <QDateTime>

#include <iostream>
#include <fstream>



class TreeBuilder : public Segment
{
public:
    static const int DEFAULT_INDEX = -1;

    static const int RECIPE_NONE = 0;
    static const int RECIPE_SAVE = 1;
    static const int RECIPE_LOAD = 2;

    static const int COLORGORICAL_MIN = 1;
    static const int COLORGORICAL_MAX = 15;

    static const int CALC_BY_ADDITION = 0;
    static const int CALC_BY_AVERAGE = 1;
    static const int CALC_BY_LARGEST = 2;
    static const int CALC_BY_FREQUENCY = 3;
    static const int CALC_BY_AREA_NORMALISED_SUM = 4;
    static const int CALC_BY_POPULATION_NORMALISED_SUM = 5;
    static const int CALC_BY_RATIO = 6;
    static const int CALC_BY_AVERAGE_SIMPLIFIED = 7;

    static const int SMALLEST_NEIGHBOUR = 0;
    static const int CLOSEST_VALUE = 1;
    static const int CLOSEST_CENTROID = 2;

    static const int DEEP_SEARCH = 0;
    static const int SHALLOW_SEARCH = 1;

    /**
     * @brief SCZTreeBuilder constructor
     * @param searchType type of search. Refer to SCZSegment::searchType()
     * @param neighbourType indicator for neighbour identification process.
     * Refer to SCZTreeBuilder::identifyNeighbour( LinkedList* list ).
     * @param recipeType indicator for user decided option for recipe
     * @param recipeName location of recipe. NULL is No recipe is saved or loaded.
     */
    TreeBuilder(int searchType, int neighbourType,
                    int recipeType, QString recipeName, int calculationType);

    /**
     * @brief SCZTreeBuilder::createBinaryTree sets up list of polygons as nodes
     * of tree
     * @param contiguousArea set of polygons from contiguous region to merge
     * @param instructions
     * @param loadedRecipe
     * @return last treenode in list after creating a link to other points
     */
    TreeNode createBinaryTree( QVector<Polygon> contiguousArea,
                               QVector<QString>* instructions,
                               QVector<CrfRow>* loadedRecipe );

    double lowerBoundSize() const;
    void setLowerBoundSize( double lowerBoundSize );

    double higherBoundSize() const;
    void setHigherBoundSize( double higherBoundSize );

    int getNeighbourType() const;
    void setNeighbourType( int value );

    int getRecipeType() const;
    void setRecipeType( int value );

    QString getRecipeSaveLocation() const;
    void setRecipeSaveLocation( const QString& recipeSaveLocation );

    QString getRecipeLoadLocation() const;
    void setRecipeLoadLocation( const QString& recipeLoadLocation );

    QVector<CrfRow>* getLoadedRecipe() const;
    void setLoadedRecipe( QVector<CrfRow>* loadedRecipe );

    int getCalculationType() const;
    void setCalculationType( int value );

private:
    //Variables
    double m_lowerBoundSize = DEFAULT_INDEX;
    double m_higherBoundSize = DEFAULT_INDEX;
    int neighbourType = 0;
    QString m_recipeSaveLocation = "";
    QString m_recipeLoadLocation = "";
    int recipeType = 0;
    int calculationType = 0;
    QVector<int> freq;
    double upperValue = INT_MIN;


    //Pointers
    QVector<QString>* m_mergeInstructions = nullptr;
    QVector<CrfRow>* m_loadedRecipe = nullptr;

    /**
     * @brief SCZTreeBuilder::lowerRange set the lower range of areas within the list
     * @param list list to search through
     * @param returned flag to check if lower Range value is saved
     * @return the lowest area value in list
     */
    double lowerRange( LinkedList* list, bool returned );

    /**
     * @brief SCZTreeBuilder::upperRange set the upper range of areas within the list
     * @param list list to search through
     */
    void upperRange( LinkedList* list );

    /**
     * @brief SCZTreeBuilder::buildBinaryTree builds a binary tree of polygons using boundaries
     * @param list list to build binary tree around
     * @return return when list is linked.
     */
    void buildBinaryTree( LinkedList* list );

    /**
     * @brief SCZTreeBuilder::identifyNeighbour identify the neighbour of the merge
     * candidate ( which is first in list). Ordered fastest to slowest in terms of
     * computation time.
     * @param list of neighbour candidates
     * @return index of neighbour candidate.
     */
    int identifyNeighbour( LinkedList* list );

    /**
     * @brief SCZTreeBuilder::computeParentBoundaries used to find out calculate the
     * boundary for the parent of current and neighbour.
     * @param current selected polygon for boundary merge
     * @param neighbour smallest neighbour of selected polygon for boundary merge.
     * @return returns the default nonSharedBoundaries of the parent for current
     * and neighbour
     */
    QVector<QPointF> computeParentBoundaries( TreeNode* current,
            TreeNode* neighbour );

    /**
     * @brief SCZTreeBuilder::computeParentBoundaries used to find out calculate the
     * boundary for the parent of current and neighbour.
     * @param current selected polygon for boundary merge
     * @param neighbour smallest neighbour of selected polygon for boundary merge.
     * @param indexes csvRow that holds boundary indices for splitting
     * @return returns the default nonSharedBoundaries of the parent for current
     * and neighbour
     */
    QVector<QPointF> computeParentBoundaries( TreeNode* current,
            TreeNode* neighbour,
            CrfRow indexes );

    /**
     * @brief SCZTreeBuilder::splitBoundary splits the boundary into shared and non-shared
     * boundaries
     * @param current current smallest neighbour in merge couple
     * @param neighbour neighbour candidate within merge couple
     * @return true if successful
     */
    bool splitBoundary( TreeNode* current, TreeNode* neighbour );

    /**
     * @brief SCZTreeBuilder::splitBoundary splits the boundary into shared and non-shared
     * boundaries using the already identifiexd boundary
     * @param current current smallest neighbour in merge couple
     * @param neighbour neighbour candidate within merge couple
     * @param indexStart start of shared boundary
     * @param indexEnd end of shared boundary
     * @return true if successful
     */
    bool splitBoundary( TreeNode* current, TreeNode* neighbour,
                        int indexStart, int indexEnd );

    /**
     * @brief SCZTreeBuilder::findSharedBoundary calculates the shared boundary and creates a
     * list of those points in the correct order.
     * @param current current smallest neighbour in merge couple
     * @param neighbour neighbour candidate within merge couple
     */
    void findSharedBoundary( TreeNode* current,
                             TreeNode* neighbour );

    /**
     * @brief SCZTreeBuilder::findSharedBoundary calculates the shared boundary
     * and creates a list of those points in the correct order.
     * @param current current smallest neighbour in merge couple
     * @param neighbour neighbour candidate within merge couple
     * @param indexStart start of shared boundary
     * @param indexEnd end of shared boundary
     */
    void findSharedBoundary( TreeNode* current, TreeNode* neighbour,
                             int indexStart, int indexEnd );

    /**
     * @brief SCZTreeBuilder::identifyBoundaryRange identifies all common vertices
     * and checks the list for the longest chain, which signifies the start and
     * beginning indexes
     * @param startIndex startIndex pointer to save to
     * @param endIndex endIndex point to save to
     * @param current current smallest neighbour in merge couple
     * @param neighbour neighbour candidate within merge couple
     */
    void identifyBoundaryRange( int* startIndex, int* endIndex,
                                TreeNode* current, TreeNode* neighbour );

    /**
     * @brief SCZTreeBuilder::identifyLongestChain identify the longest distance between
     * two common vertices
     * @param commonVertices list of all found common vertices.
     * @param current current polygon for identification
     * @return the index of the longest common Vertices, within get Points
     * (correct end index)
     */
    int identifyLongestChain( QVector<QPointF>* commonVertices,
                              TreeNode* current );

    /**
     * @brief SCZTreeBuilder::isLongestChain checks if currIndex has a longer length
     * then longestL
     * @param current list of vertices
     * @param currIndex index of current chain
     * @param nextIndex index of index for distance check;
     * @param longestL current longest length
     * @return true if new longest, otherwise false.
     */
    bool isLongestChain( QVector<QPointF> current, int currIndex,
                         int nextIndex, int* longestL );

    /**
     * @brief SCZTreeBuilder::findNonSharedBoundary uses found Shared Boundary to
     * correct current non-shared boundary. The method assumes there is one
     * boundary that is consistent, meaning there is a clear separation between
     * shared and non-shared boundaries.
     * @param current TreeNode for polygon to split and find the Non-Shared
     * boundary.
     * @param neighbour TreeNode selected as neighbour. Necessary to check for
     * doughnut case. Doughnut case do not need sealed boundaries.
     */
    void findNonSharedBoundary( TreeNode* current,
                                TreeNode* neighbour );

    /**
     * @brief SCZTreeBuilder::updateList updates list by removing merged polygons
     * and adding the parent polygon
     * @param list list of active polygons
     * @param parent parent of current merge candidates
     * @param neighbour index of currents merge couple
     */
    void updateList( LinkedList* list, TreeNode* parent,
                     int neighbour );

    /**
     * @brief SCZTreeBuilder::addParentToList add's parent to list
     * @param list list of active polygons to merge
     * @param parent polygon to add to list.
     * @param neighbour index of neighbour (parent will always be bigger in size
     * than neighbour)
     */
    void addParentToList( LinkedList* list, TreeNode* parent,
                          int neighbour );

    /**
     * @brief selectDefaultValue selects value of default polygon based on
     * whether any linked data is provided
     * @param p polygon to select default value for
     * @return selected default value of linked data, if no linked data, return a
     * random value from 1 to qualitative value max
     */
    double selectDefaultValue( Polygon p );

    /**
     * @brief applyValue updates the node's value based on the calculationType
     * @param node node to update value of
     * @param calculationType type of calculation to use. Addition which gives
     *  the sum of the two children, average which gives the average of the two
     * children, largest which saves the largest area's value (always right branch's child)
     */
    QStringList applyValue( TreeNode* node, int calculationType );

    /**
     * @brief calculateValueByAverage recursively check the all leaf nodes of
     * node using DFS to calculate the average value. Base method to call.
     * @param node node to calculate average value of
     * @return average value
     */
    double calculateValueByAverage(TreeNode* node , int fieldIndex);

    /**
     * @brief calculateValueByAverage recursive method to calculate average
     * should not be called by anything other than itself or base
     * @see SCZTreeBuilder::calculateValueByAverage(TreeNode* node)
     * @param vCount current count of leaf nodes
     * @param value current sum of values
     * @param node current node in DFS
     */
    void calculateValueByAverage(int* vCount, double* value,
                                  TreeNode* node , int fieldIndex);
    /**
     * @brief calculateValueByFrequency Base call for finding accurate frequency
     *  of values of leaf nodes only. This would be used for Qualitative data
     *  (religion)
     * @param node node to find value of
     * @param upperValue maximum value possible (necessary for sizing vector)
     * @return highest frequent value
     */
    int calculateValueByFrequency( TreeNode* node,
                                   int upperValue, int fieldIndex );

    /**
     * @brief calculateValueByFrequency recursive method to calculate most
     * frequent value. Should not be called by anything other than itself or
     *  base.
     * @see SCZTreeBuilder::calculateValueByFrequency( TreeNode* node, int uppderValue )
     * @param node current node in DFS
     */
    void calculateValueByFrequency( TreeNode* node, int fieldIndex );

    /**
     * @brief calculateValueRange calculate maximum value in list
     * @param list list of nodes
     */
    void calculateValueRange( LinkedList* list );
    double calculateValueByAreaNormalisedSum(TreeNode* node , int fieldIndex);
    bool debugRender( LinkedList* list, int debugMode, int highlight,
                      int sleepMul );

    double distance(double range1, double range2);
    int next(QVector<QPointF> list, int index);
};

#endif // SCZTREEBUILDER_H
