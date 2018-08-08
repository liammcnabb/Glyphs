#ifndef LM_CRFWRITER_H
#define LM_CRFWRITER_H

#include "LM/writer.h"

#include <string>
#include <QVector>
#include <fstream>

class CrfWriter : public Writer
{
public:
    CrfWriter( std::string fileName );

    void write( QVector<QString>* data );
    void write( std:: string fileName , QVector<QString>* data );
};

#endif // LM_CRFWRITER_H
