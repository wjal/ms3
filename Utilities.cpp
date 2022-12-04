// Name: James Little
// Seneca Student ID: 028496123
// Seneca email: walittle@myseneca.ca
// Date of completion: 19/11/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include "Utilities.h"

namespace sdds{
    char Utilities::m_delimiter = ',';
//member functions
    void Utilities::setFieldWidth(size_t newWidth){

        if(newWidth > m_widthField){
            m_widthField = newWidth;
        }
    }

    size_t Utilities::getFieldWidth() const{
        return m_widthField;
    }
    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more){
        //changed from stringstream method for ms3. version from ms1/ms2 returns a false at the end of a line, and only first line from txt is added.  m_firstStation never gets set so += doest work
        
        
        std::string localString = str;

        localString.erase(0, next_pos);

        if(str[next_pos] == getDelimiter()){
            more = false;
            throw "   ERROR: token at first.\n";

        }else{

        char delimiter = getDelimiter();
        if(localString.find_first_of(delimiter) == std::string::npos){
            //set false, but not error - l
            more = false;
        }

        std::stringstream ss(localString);

        getline(ss, localString, delimiter);

        next_pos += localString.length() + 1;
        setFieldWidth(localString.length());
        }
        return localString;
    }
//class functions
    void Utilities::setDelimiter(char newDelimiter){
        m_delimiter = newDelimiter;
    }
    char Utilities::getDelimiter(){
        return m_delimiter;
    }
    std::string&  Utilities::ltrim(std::string& str){
        const char* t = " \t\n\r\f\v";
        str.erase(0, str.find_first_not_of(t));
        return str;
    }
    std::string& Utilities::rtrim(std::string& str){
        const char* t = " \t\n\r\f\v";
        str.erase(str.find_last_not_of(t) + 1);
        return str;
    }
    std::string& Utilities::fullTrim(std::string& str){
        str = rtrim(ltrim(str));
        return str;
    }

}
