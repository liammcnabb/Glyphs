#include "crfwriter.h"

CrfWriter::CrfWriter( std::string fileName )
{
    Writer::setFileName( fileName );

}

void CrfWriter::write( QVector<QString>* data )
{
    write( Writer::getFileName(), data );
}

void CrfWriter::write( std::string fileName, QVector<QString>* data )
{
    std::ofstream recipe( fileName );
    for( int i = 0; i < data->size(); ++i )
        recipe << data->at( i ).toStdString() <<
               std::endl;
    recipe.close();
}


