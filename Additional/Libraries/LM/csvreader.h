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
    /**
     * @brief CsvReader constructor used to call CsvReader
     * @param fileName the file location of the CSV file
     */
    CsvReader( std::string fileName );
    /**
     * @brief extract extracts the csv contents and saves to a vector of
     * string lists
     */
    void extract();
    /**
     * @brief extract extracts the csv contents from the fileName
     * @param fileName location of the CSV
     */
    void extract( std::string fileName );

    /**
     * @brief getData getter method for the data extracted from the CSV file
     * @return a vector of string lists extracted from the csv
     */
    QVector<QStringList> getData() const;
    /**
     * @brief setData setter method for the data extracted from the CSV file
     * @param value new vector of string lists
     */
    void setData( const QVector<QStringList>& value );

private:
    QVector<QStringList> data;

    //Split on comma only if not around ""
    QString REGEX = ",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)";
};

#endif // CSVREADER_H
