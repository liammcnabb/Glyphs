#include "shpreader.h"

ShpReader::ShpReader( QString fileName )
{
    Reader::setFileName( fileName.toStdString() );
    initialise();
}

bool ShpReader::initialise()
{
    GDALAllRegister();
    QByteArray temp = QString::fromStdString(
                          Reader::getFileName() ).toLatin1();
    GDALDataset* shpfile;


    shpfile = ( GDALDataset* ) GDALOpenEx( temp.data(),
                                           GDAL_OF_VECTOR,
                                           NULL,
                                           NULL,
                                           NULL );

    if( shpfile == NULL )
    {
        throw std::runtime_error( LOADING_FAILURE );
        return false;
    }
    setMapData( shpfile );
    return true;
}

GDALDataset* ShpReader::getMapData() const
{
    return mapData;
}

void ShpReader::setMapData( GDALDataset* value )
{
    mapData = value;
}
