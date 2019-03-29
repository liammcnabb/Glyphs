#ifndef LM_WRITER_H
#define LM_WRITER_H

#include <string>

class Writer
{
public:
    /**
     * @brief Writer Default Constructor
     */
    Writer();
    /**
     * @brief getFileName getter method for filename location
     * @return returns filename (location)
     */
    std::string getFileName() const;
    /**
     * @brief setFileName setter method for filename
     * @param value new value of filename (location)
     */
    void setFileName( const std::string& value );

private:
    std::string fileName = "";
};

#endif // LM_WRITER_H
