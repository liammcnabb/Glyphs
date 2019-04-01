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
    /**
     * @brief LinkedList
     */
    LinkedList();
    /**
     * @brief LinkedList
     * @param obj
     */
    LinkedList( TreeNode obj );
    /**
     * @brief LinkedList
     * @param obj
     */
    LinkedList( TreeNode* obj );

    /**
     * @brief insert
     * @param index
     * @param obj
     * @return
     */
    bool insert( int index, TreeNode obj );
    /**
     * @brief removeFirst
     * @return
     */
    bool removeFirst();
    /**
     * @brief removeLast
     * @return
     */
    bool removeLast();
    /**
     * @brief removeAt
     * @param index
     * @return
     */
    bool removeAt( int index );
    /**
     * @brief append
     * @param obj
     * @return
     */
    bool append( TreeNode obj );
    /**
     * @brief append
     * @param obj
     * @return
     */
    bool append( TreeNode* obj );
    /**
     * @brief prepend
     * @param obj
     * @return
     */
    bool prepend( TreeNode obj );
    /**
     * @brief at
     * @param index
     * @return
     */
    TreeNode* at( int index );
    /**
     * @brief first
     * @return
     */
    TreeNode* first();
    /**
     * @brief last
     * @return
     */
    TreeNode* last();

    /**
     * @brief indexOf
     * @param obj
     * @return
     */
    int indexOf( TreeNode* obj );

    /**
     * @brief size
     * @return
     */
    int size();
    /**
     * @brief toString
     * @return
     */
    QString toString();

    /**
     * @brief link
     * @param c
     */
    void link( std::vector<Container> c );
    /**
     * @brief get_cFirst
     * @return
     */
    Container* get_cFirst();
    /**
     * @brief at_c
     * @param index
     * @return
     */
    Container* at_c( int index );
private:

    /**
     * @brief get_cLast
     * @return
     */
    Container* get_cLast();
    /**
     * @brief set_cFirst
     * @param obj
     */
    void set_cFirst( Container* obj );
    /**
     * @brief set_cLast
     * @param obj
     */
    void set_cLast( Container* obj );
    /**
     * @brief set_size
     * @param newSize
     */
    void set_size( int newSize );

    Container* m_first = nullptr;
    Container* m_last = nullptr;
    int m_size = 0;
    static constexpr char const* CLASS =
        "[LinkedList]";

    /**
     * @brief remove_only
     */
    void remove_only();
    /**
     * @brief add_only
     * @param obj
     */
    void add_only( TreeNode obj );
    /**
     * @brief add_only
     * @param obj
     */
    void add_only( TreeNode* obj );
    /**
     * @brief checkBounds
     * @param value
     * @param min
     * @param max
     * @return
     */
    static int checkBounds(int value, int min, int max);
};

#endif // LINKEDLIST_H
