#ifndef LM_WRITER_H
#define LM_WRITER_H

#include <string>

class Writer
{
public:
    Writer();

    std::string getFileName() const;
    void setFileName( const std::string& value );

private:
    std::string fileName = "";
};

#endif // LM_WRITER_H
