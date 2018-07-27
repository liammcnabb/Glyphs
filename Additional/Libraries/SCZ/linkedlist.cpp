#include "linkedlist.h"

/*
 * CONSTRUCTORS
 */
LinkedList::LinkedList()
{

}

LinkedList::LinkedList( TreeNode obj )
{
    add_only( obj );
}

LinkedList::LinkedList( TreeNode* obj )
{
    add_only( obj );
}

/*
 * PUBLIC METHODS
 */

bool LinkedList::insert( int index, TreeNode obj )
{
    index = checkBounds( index, 0, size() );

    if ( index <= 0 )
        return prepend( obj );
    else if ( index >= size() )
        return append( obj );

    Container* id = this->get_cFirst();

    for( int i = 0; i < index; ++i )
        id = id->next;

    Container* newObj = new Container( obj );
    newObj->next = id;
    newObj->previous = id->previous;
    id->previous->next = newObj;
    id->previous = newObj;
    set_size( size() + 1 );

    return true;
}

bool LinkedList::removeFirst()
{
    if( size() == 1 )
        remove_only();
    else
    {
        set_cFirst( get_cFirst()->next );
        get_cFirst()->previous = nullptr;
        set_size( size() - 1 );
    }
    return true;
}

bool LinkedList::removeLast()
{
    if( size() == 1 )
        remove_only();
    else
    {
        set_cLast( get_cLast()->previous );
        get_cLast()->next = nullptr;
        set_size( size() - 1 );
    }



    return true;
}

bool LinkedList::removeAt( int index )
{
    index = checkBounds( index, 0, size() );

    if ( index <= 0 )
        return removeFirst();
    else if ( index >= size() - 1 )
        return removeLast();

    Container* id = this->get_cFirst();

    for( int i = 0; i < index; ++i )
        id = id->next;

    id->previous->next = id->next;
    id->next->previous = id->previous;
    set_size( size() - 1 );


    return true;
}

bool LinkedList::append( TreeNode obj )
{
    if ( size() == 0 )
        add_only( obj );
    else
    {
        Container* newObj = new Container( obj );
        //   if( newObj->data->getLeftChild() != nullptr )
        //       newObj->data->getLeftChild()->setParent(newObj->data);
        //   if( newObj->data->getRightChild() != nullptr )
        //       newObj->data->getRightChild()->setParent(newObj->data);
        get_cLast()->next = newObj;
        newObj->previous = get_cLast();
        set_cLast( newObj );
        set_size( size() + 1 );
    }

    return true;
}

bool LinkedList::append( TreeNode* obj )
{
    if ( size() == 0 )
        add_only( obj );
    else
    {
        Container* newObj = new Container( obj );
        get_cLast()->next = newObj;
        newObj->previous = get_cLast();
        set_cLast( newObj );
        set_size( size() + 1 );
    }

    return true;
}

bool LinkedList::prepend( TreeNode obj )
{
    if ( size() == 0 )
        add_only( obj );
    else
    {
        Container* newObj = new Container( obj );
        get_cFirst()->previous = newObj;
        newObj->next = get_cFirst();
        set_cFirst( newObj );
        set_size( size() + 1 );
    }

    return true;
}

TreeNode* LinkedList::at( int index )
{
    index = checkBounds( index, 0, size() );
    if ( index == size() )
        return last();

    Container* id = this->get_cFirst();

    for( int i = 0; i < index; ++i )
        id = id->next;

    return id->data;
}

TreeNode* LinkedList::first()
{
    return get_cFirst()->data;
}

TreeNode* LinkedList::last()
{
    return get_cLast()->data;
}

int LinkedList::indexOf( TreeNode* obj )
{
    if ( size() == 0 )
        return 0;

    Container* id = this->get_cFirst();

    for( int i = 0; i < size(); ++i )
    {
        if ( *id->data == *obj )
            return i;
        id = id->next;
    }
    qDebug() << CLASS << E << INDEX_NOT_FOUND;
    return -1;
}

int LinkedList::size()
{
    return m_size;
}

QString LinkedList::toString()
{
    QString string;
    string.append( "{ " );
    string.append( at_c( 0 )->toString() );

    for ( int i = 1; i < size(); ++i )
    {
        string.append( ", " );
        string.append( at_c( i )->toString() );
    }

    string.append( " }" );

    return string;
}

void LinkedList::link( std::vector<Container> c )
{
    //    if (c.size() == this->size())
    //    {
    //        for (int i = 0; i < this->size(); ++i)
    //        {
    //            at_c(i)->setData(&c[i]);
    //        }
    //    }
}


/*
 * PRIVATE METHODS
 */

void LinkedList::set_cFirst( Container* obj )
{
    m_first = obj;
}

void LinkedList::set_cLast( Container* obj )
{
    m_last = obj;
}

void LinkedList::set_size( int newSize )
{
    m_size = newSize;
}

Container* LinkedList::get_cFirst()
{
    return m_first;
}

Container* LinkedList::get_cLast()
{
    return m_last;
}

void LinkedList::remove_only()
{
    set_cFirst( nullptr );
    set_cLast( nullptr );

    set_size( 0 );
    return;
}

void LinkedList::add_only( TreeNode obj )
{
    Container* firstObj = new Container( obj );
    set_cFirst( firstObj );
    set_cLast( firstObj );
    set_size( size() + 1 );
}

void LinkedList::add_only( TreeNode* obj )
{
    Container* firstObj = new Container( obj );
    set_cFirst( firstObj );
    set_cLast( firstObj );
    set_size( size() + 1 );
}

Container* LinkedList::at_c( int index )
{
    index = checkBounds( index, 0, size() );

    Container* id = this->get_cFirst();

    for( int i = 0; i < index; ++i )
        id = id->next;

    return id;
}

int LinkedList::checkBounds( int value, int min, int max )
{
    if ( value < min )
    {
        qDebug() << ERROR_INDEX_SMALL;
        return min;
    }
    else if ( value > max )
    {
        qDebug() << ERROR_INDEX_LARGE;
        return max;
    }
    else
        return value;
}
