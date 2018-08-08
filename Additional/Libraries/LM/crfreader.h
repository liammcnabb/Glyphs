#ifndef LM_CRFREADER_H
#define LM_CRFREADER_H

//#include "global.h"
#include "crfrow.h"

#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <vector>
#include <string>
#include <QDebug>
#include <sys/stat.h>
#include <unistd.h>

#include "reader.h"


class CrfReader : public Reader
{
public:
    CrfReader( std::string fileName );
    QVector<CrfRow> read( QString fileName );
    bool exists( const QString& name );
private:
    CrfRow row;
};

#endif // LM_CrfReader_H
