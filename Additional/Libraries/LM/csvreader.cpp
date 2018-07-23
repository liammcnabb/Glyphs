#include "csvreader.h"

CsvReader::CsvReader( std::string fileName )
{
    Reader::setFileName( fileName );
}

void CsvReader::extract()
{
    extract( Reader::getFileName() );
}

void CsvReader::extract( std::string fileName )
{
    data.empty();
    QFile file( QString::fromStdString( fileName ) );
    if ( file.open( QIODevice::ReadOnly ) )
    {
        int lineIndex = 0;
        QTextStream in( &file );

        while( !in.atEnd() )
        {
            QString fileLine = in.readLine();
            QStringList lineToken = fileLine.split( QRegExp(REGEX),
                                                    QString::SkipEmptyParts );
            data.append( lineToken );
            lineIndex++;
        }
        file.close();
    }
    else
        qDebug() << "Could not Open File:" << QString::fromStdString( fileName );
}

QVector<QStringList> CsvReader::getData() const
{
    return data;
}

void CsvReader::setData( const QVector<QStringList>& value )
{
    data = value;
}
