#ifndef READER_H
#define READER_H

#include <string>

class Reader
{
public:
    /**
     * @brief Reader Default Constructor
     */
    Reader();
    /**
     * @brief getFileName getter method for a filename
     * @return returns a filename (location)
     */
    std::string getFileName() const;
    /**
     * @brief setFileName setter method for filename
     * @param value new filename (location)
     */
    void setFileName( const std::string& value );

private:
    std::string fileName = "";
};

#endif // READER_H
