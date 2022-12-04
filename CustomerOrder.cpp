// Name: James Little
// Seneca Student ID: 028496123
// Seneca email: walittle@myseneca.ca
// Date of completion: 26/11/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "CustomerOrder.h"

#include "Utilities.h"

namespace sdds {

size_t CustomerOrder::m_widthField{0};

CustomerOrder::CustomerOrder(){}
CustomerOrder::CustomerOrder(std::string s){

    Utilities util1;
    size_t next_pos{0};

    bool more{true};

    
    m_name = util1.extractToken(s, next_pos, more); //extract and trim name of customer
    m_name = util1.fullTrim(m_name);
    m_product = util1.extractToken(s, next_pos, more);//extract and trim product name
    m_product = util1.fullTrim(m_product);

    m_cntItem = count(s.begin(), s.end(), Utilities::getDelimiter()) - 1; //count items using the delimiters starting at beginning of string


    std::vector<Item*> items;

    while(more){
        std::string tempItem = util1.extractToken(s, next_pos, more);
        tempItem = util1.fullTrim(tempItem); //trim the white space before pushing in to vector
        items.push_back(new Item(tempItem));
    }
    //new array of pointers to items, length of m_cntItem
    m_lstItem = new Item*[m_cntItem];

    size_t i{0};
    //add item to list of items
        std::for_each(items.begin(), items.end(), [&](Item* item){
            m_lstItem[i] = item;
            i++;
        });

    size_t tempfield = util1.getFieldWidth();
    m_widthField = std::max(tempfield, m_widthField);
}
CustomerOrder::CustomerOrder(const CustomerOrder& order){
        throw "ERROR: Cannot make copies."; //wont actually show this msg in current test, but was getting 'libc++abi: terminating' and abort without any msg.  Keep it for other possible tests anyways
}

CustomerOrder::CustomerOrder(CustomerOrder&& order) noexcept{
    *this = std::move(order);
}
CustomerOrder& CustomerOrder::operator= (CustomerOrder&& order) noexcept{
    
    if(this != &order){
        for (size_t i = 0; i < m_cntItem; i++) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
        m_name = order.m_name;
        m_product = order.m_product;
        m_cntItem = order.m_cntItem;
        m_lstItem = order.m_lstItem;

        order.m_name = "";
        order.m_product = "";
        order.m_cntItem = 0;
        order.m_lstItem = nullptr;
    }
    return *this;
}
bool CustomerOrder::isOrderFilled(){
    bool filled{true};
    for(size_t i = 0; i < m_cntItem; i++){
        filled = m_lstItem[i]->m_isFilled;
        if(!filled){
            return filled;
        }
    }
    return filled;
}
bool CustomerOrder::isItemFilled(const std::string& itemName) const{
    bool filled{true};
    for(size_t i = 0; i < m_cntItem; i++){
        if(m_lstItem[i]->m_itemName == itemName){
            filled = m_lstItem[i]->m_isFilled;
            return filled;
        }

    }
    return filled;
}
void CustomerOrder::fillItem(Station& station, std::ostream& os){
    std::for_each(m_lstItem, (m_lstItem + m_cntItem), [&](Item* item){
        if(station.getItemName() == item->m_itemName){
            if(station.getQuantity() > 0){
                item->m_serialNumber = station.getNextSerialNumber();
                item->m_isFilled = true;
                station.updateQuantity();
                os << "    Filled " << m_name;
                os << ", " << m_product;
                os << " [" << item->m_itemName << "]" << std::endl;
            }
            else{
                os << "    Unable to fill " << m_name;
                os << ", " << m_product;
                os << " [" << item->m_itemName << "]" << std::endl;
            }
        }
    });
}
void CustomerOrder::display(std::ostream& os) const{
    os << m_name;
    os << " - " << m_product << '\n';

    std::for_each(m_lstItem, (m_lstItem + m_cntItem), [&](Item* item){
        os << "[" << std::setw(6) << std::setfill('0') << item->m_serialNumber << "] ";
        os << std::setfill(' ')<< std::setw(CustomerOrder::m_widthField);
        os << std::left << item->m_itemName;
        os << " - ";
        if(item->m_isFilled){
            os << "FILLED";
        }
        else{
            os << "TO BE FILLED";
        }
        os << std::endl;
    });
}
CustomerOrder::~CustomerOrder(){
    for(size_t i = 0; i < m_cntItem; i++){
        delete m_lstItem[i]; //delete pointers to items in array
        m_lstItem[i] = nullptr; // make nullptr while iterating through array, before deleting list
    }
    delete [] m_lstItem; // delete list
}

}