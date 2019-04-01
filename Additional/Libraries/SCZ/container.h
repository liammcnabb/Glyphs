#ifndef CONTAINER_H
#define CONTAINER_H

//#include "global.h"
#include "SCZ/treenode.h"


class Container
{
public:
    /**
     * @brief Container Default Constructor.
     * @see LinkedList.h
     */
    Container();
    /**
     * @brief Container constructor with TreeNode object
     * @param obj TreeNode to contain
     */
    Container( TreeNode obj );
    /**
     * @brief Container constructor with TreeNode pointer
     * @param obj TreeNode pointer to contain
     */
    Container( TreeNode* obj );
    /**
     * @brief toString String representation
     * @return String representation
     */
    QString toString();
    Container* next = nullptr;
    Container* previous = nullptr;
    TreeNode* data;

    void setData( TreeNode* data );


};

#endif // CONTAINER_H
