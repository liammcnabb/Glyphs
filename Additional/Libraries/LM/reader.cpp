#include "reader.h"

Reader::Reader()
{

}

std::string Reader::getFileName() const
{
    return fileName;
}

void Reader::setFileName( const std::string& value )
{
    fileName = value;
}
