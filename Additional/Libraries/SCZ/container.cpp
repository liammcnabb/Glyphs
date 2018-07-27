#include "container.h"

Container::Container()
{

}

Container::Container( TreeNode obj )
{
    this->data = new TreeNode( obj );
}

Container::Container( TreeNode* obj )
{
    this->data = obj;
}



QString Container::toString()
{
    return QString::number( data->getArea() );
}

void Container::setData( TreeNode* data )
{
    this->data = data;
}
