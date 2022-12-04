// Name: James Little
// Seneca Student ID: 028496123
// Seneca email: walittle@myseneca.ca
// Date of completion: 19/11/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#define _CRT_SECURE_NO_WARNINGS
#ifndef UTILITIES_H
#define UTILITIES_H

namespace sdds{

class Utilities {

private:
//instance variable
    size_t m_widthField {1};
//class variable
    static char m_delimiter;
public:

//member functions
void setFieldWidth(size_t newWidth);
size_t getFieldWidth() const;
std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
std::string&  ltrim(std::string& str);
std::string& rtrim(std::string& str);
std::string& fullTrim(std::string& str);
//class functions
static void setDelimiter(char newDelimiter);
static char getDelimiter();

};

}

#endif
