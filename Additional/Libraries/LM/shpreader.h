#ifndef SHPREADER_H
#define SHPREADER_H

#include "LM/reader.h"

#include <QString>
#include <gdal/ogrsf_frmts.h>
#include <iostream>

class OGRDataSource;

class ShpReader: public Reader
{
public:
    /**
     * @brief FileLoader default constructor used to extract data to
     * GDALDataSet pointer.
     * @param fileName location of shape file to extract
     */
    ShpReader( QString fileName );

    /**
     * @brief getFilename get location of shape file to extract
     * @return location of shape file to extract
     */
    QString getFilename() const;

    /**
     * @brief setFilename set location of shape file to extract
     * @param value new location of shape file to extract
     */
    void setFilename( const QString& value );

    /**
     * @brief initialise saves shape file data to GDALDataset and saves to newMap
     * @see http://www.gdal.org/classGDALDataset.html#a9cb8585d0b3c16726b08e25bcc94274a
     * @return true if successful, false if error is thrown
     */
    bool initialise();

    /**
     * @brief getMapData get extracted map data
     * @return extracted map data
     */
    GDALDataset* getMapData() const;

    /**
     * @brief setMapData set extracted map data
     * @param value new extracted map data
     */
    void setMapData( GDALDataset* value );

    static constexpr char const* LOADING_FAILURE = "File loading failed.";
private:
    GDALDataset* mapData;


};

#endif // SHPREADER_H
