#include "crfreader.h"

CrfReader::CrfReader( std::string fileName )
{
    Reader::setFileName( fileName );
}

/**
 * @brief CrfReader::exists checks if a file exists.
 * "The stat function returns information about the attributes of the file
 * named by filename in the structure pointed to by buf. If filename is the
 * name of a symbolic link, the attributes you get describe the file that the
 * link points to. If the link points to a nonexistent file name, then stat
 * fails reporting a nonexistent file. The return value is 0 if the operation
 * is successful, or -1 on failure. "
 * @see https://en.wikibooks.org/wiki/C_Programming/POSIX_Reference/sys/stat.h#Member_functions
 * @param name file location of item to check existance of in
 * @return true if exists, false otherwise.
 */
bool CrfReader::exists( const QString& name )
{
    struct stat buffer;
    return ( stat( name.toUtf8().constData(), &buffer ) == 0 );
}

QVector<CrfRow> CrfReader::read( QString fileName )
{
    std::ifstream file;
    file.open( fileName.toStdString(), std::ifstream::in );

    if( !file.is_open() )
    {
        qDebug() << "CrfReader:: could not open file: " << fileName;
        return QVector<CrfRow>();
    }

    QVector<CrfRow> organisedList;

    std::string neighbourIndex, b1Start, b1End, b2Start, b2End;

    while( std::getline( file, neighbourIndex, ',' ) &&
            std::getline( file, b1Start, ',' ) &&
            std::getline( file, b1End, ',' ) &&
            std::getline( file, b2Start, ',' ) &&
            std::getline( file, b2End, '\n' ) )
    {
        row.setNeighbourIndex( std::stoi( neighbourIndex ) );
        row.setPOneStartIndex( std::stoi( b1Start ) );
        row.setPOneEndIndex( std::stoi( b1End ) );
        row.setPTwoStartIndex( std::stoi( b2Start ) );
        row.setPTwoEndIndex( std::stoi( b2End ) );
        organisedList.push_back( row );
    }
    file.close();
    return organisedList;
}
