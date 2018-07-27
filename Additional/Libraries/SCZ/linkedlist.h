#ifndef LINKEDLIST_H
#define LINKEDLIST_H

//#include "global.h"
#include "SCZ/treenode.h"
#include "SCZ/container.h"
#include <QDebug>
#include <QPointF>
#include <string>

//#include "personalerrors.cpp"



class LinkedList
{
public:
    LinkedList();
    LinkedList( TreeNode obj );
    LinkedList( TreeNode* obj );

    bool insert( int index, TreeNode obj );
    bool removeFirst();
    bool removeLast();
    bool removeAt( int index );
    bool append( TreeNode obj );
    bool append( TreeNode* obj );
    bool prepend( TreeNode obj );
    TreeNode* at( int index );
    TreeNode* first();
    TreeNode* last();

    int indexOf( TreeNode* obj );

    int size();
    QString toString();

    void link( std::vector<Container> c );
    Container* get_cFirst();
    Container* at_c( int index );
private:

    Container* get_cLast();
    void set_cFirst( Container* obj );
    void set_cLast( Container* obj );
    void set_size( int newSize );

    Container* m_first = nullptr;
    Container* m_last = nullptr;
    int m_size = 0;
    static constexpr char const* CLASS =
        "[LinkedList]";

    void remove_only();
    void add_only( TreeNode obj );
    void add_only( TreeNode* obj );
    static int checkBounds(int value, int min, int max);
};

#endif // LINKEDLIST_H
