// Name: James Little
// Seneca Student ID: 028496123
// Seneca email: walittle@myseneca.ca
// Date of completion: 19/11/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#define _CRT_SECURE_NO_WARNINGS
#ifndef STATION_H
#define STATION_H

#include "Utilities.h"


namespace sdds{

class Station {
private:
//instance variables
    int m_stationId{};
    std::string m_itemName{};
    std::string m_stationDescription{};
    unsigned int m_serialNum{};
    unsigned int m_itemsInStock{};

    
public:
//class variables
    static size_t m_widthField;
    static size_t id_generator;
    Station(){}
    Station(std::string s);
    const std::string& getItemName() const;
    size_t getNextSerialNumber();
    size_t getQuantity() const;
    void updateQuantity();
    void display(std::ostream& os, bool full) const;
};

}

#endif