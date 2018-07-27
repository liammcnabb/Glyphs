#ifndef CONTAINER_H
#define CONTAINER_H

//#include "global.h"
#include "SCZ/treenode.h"


class Container
{
public:
    Container();
    Container( TreeNode obj );
    Container( TreeNode* obj );
    QString toString();
    Container* next = nullptr;
    Container* previous = nullptr;
    TreeNode* data;

    void setData( TreeNode* data );


};

#endif // CONTAINER_H
