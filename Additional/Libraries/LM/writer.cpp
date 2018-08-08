#include "writer.h"

Writer::Writer()
{

}

std::string Writer::getFileName() const
{
    return fileName;
}

void Writer::setFileName( const std::string& value )
{
    fileName = value;
}
