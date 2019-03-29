#ifndef LM_CRFWRITER_H
#define LM_CRFWRITER_H

#include "LM/writer.h"

#include <string>
#include <QVector>
#include <fstream>

class CrfWriter : public Writer
{
public:
    /**
     * @brief CrfWriter Default constructor
     * @param fileName location of file
     */
    CrfWriter( std::string fileName );

    /**
     * @brief write writes string data to the file in crf format
     * @param data data to write to file
     */
    void write( QVector<QString>* data );
    /**
     * @brief write writes string data to the file in crf format
     * @param fileName location of file
     * @param data data to write to file
     */
    void write( std:: string fileName , QVector<QString>* data );
};

#endif // LM_CRFWRITER_H
