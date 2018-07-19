#ifndef READER_H
#define READER_H

#include <string>

class Reader
{
public:
    Reader();
    std::string getFileName() const;
    void setFileName( const std::string& value );

private:
    std::string fileName = "";
};

#endif // READER_H
