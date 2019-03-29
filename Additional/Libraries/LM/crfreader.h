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
    /**
     * @brief CrfReader Default constructor for CrfReader
     * @param fileName location of the file
     */
    CrfReader( std::string fileName );
    /**
     * @brief read Reads the data as a vector of CrfRows and returns them to
     * the user
     * @param fileName the location of the file
     * @return a vector of CrfRows read from the file
     */
    QVector<CrfRow> read( QString fileName );
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
    bool exists( const QString& name );
private:
    CrfRow row;
};

#endif // LM_CrfReader_H
