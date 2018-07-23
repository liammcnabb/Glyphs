#ifndef CSVREADER_H
#define CSVREADER_H

#include "reader.h"

#include <QVector>
#include <QStringList>
#include <sstream>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class CsvReader : public Reader
{
public:
    CsvReader( std::string fileName );
    void extract();
    void extract( std::string fileName );

    QVector<QStringList> getData() const;
    void setData( const QVector<QStringList>& value );

private:
    QVector<QStringList> data;

    //Split on comma only if not around ""
    QString REGEX = ",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)";
};

#endif // CSVREADER_H
