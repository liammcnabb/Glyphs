#include "crfreader.h"

CrfReader::CrfReader( std::string fileName )
{
    Reader::setFileName( fileName );
}

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
