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
#include <vector>
#include <iomanip>
#include "Station.h"


namespace sdds{


size_t Station::id_generator = 0;
size_t Station::m_widthField = 0;

Station::Station(std::string s){

    Utilities utility;
    size_t next_pos = 0;

    //set true, for more tokens to extract
    bool more = true;

    //while(more){

        try{
            m_itemName = utility.extractToken(s, next_pos, more);
    //sets the station widthfield to greatest length that has been extracted for name
            size_t tempfield = utility.getFieldWidth();
            if(tempfield > m_widthField){
                m_widthField = tempfield;
            }
    //trim
            m_itemName = utility.fullTrim(m_itemName);

    //get serial num. Extract token/conver to int    
            m_serialNum = std::stoi(utility.extractToken(s, next_pos, more));
    //get items in stock.  Extract token/conver to int
            m_itemsInStock = std::stoi(utility.extractToken(s, next_pos, more));
    //extract and trim description
            m_stationDescription = utility.extractToken(s, next_pos, more);
            m_stationDescription = utility.fullTrim(m_stationDescription);
    //only generate new id if all tokens have been successfully retrieved
            m_stationId = ++id_generator;
        }
        catch(const char* msg){
            more = false;
            next_pos = 0;
            std::cout << msg;

        }catch(...){
            more = false;
            next_pos = 0;
            std::cout <<"Error:  Other error" << std::endl;

        }
   // }

}

const std::string& Station::getItemName() const{
    return m_itemName;
}

size_t Station::getNextSerialNumber(){

    size_t serial = m_serialNum++;
    return serial;

}

size_t Station::getQuantity() const{
    return m_itemsInStock;
}

void Station::updateQuantity(){
    if(m_itemsInStock >= 1){
        --m_itemsInStock;
    }
}

void Station::display(std::ostream& os, bool full) const{
    int width = Station::m_widthField;
    
        os << std::setw(3) << std::right << std::setfill('0') << m_stationId << std::setfill(' ');
        os << " | " << std::left << std::setw(width) << m_itemName;
        os << " | " << std::right << std::setfill('0') << std::setw(6) << m_serialNum << std::setfill(' ');
        os << " | "; 
    if(full){
        os <<  std::right  << std::setw(4) << m_itemsInStock;
        os << " | " << std::left << m_stationDescription;
    }
        os << std::endl;
    
}
    
}