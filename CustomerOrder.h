// Name: James Little
// Seneca Student ID: 028496123
// Seneca email: walittle@myseneca.ca
// Date of completion: 26/11/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#define _CRT_SECURE_NO_WARNINGS
#ifndef CUSTOMER_ORDER_H
#define CUSTOMER_ORDER_H

#include "Station.h"

namespace sdds{

    struct Item {
    std::string m_itemName;
    size_t m_serialNumber{0};
    bool m_isFilled{false};

	Item(const std::string& src) : m_itemName(src) {};
};

class CustomerOrder {
private:
    std::string m_name{};
    std::string m_product{};
    size_t m_cntItem{};
    Item** m_lstItem{};
public:
//class variable 
    static size_t m_widthField;
//member functions
    CustomerOrder();
    CustomerOrder(std::string str);
    CustomerOrder(const CustomerOrder& order);
    CustomerOrder& operator= (const CustomerOrder& order) = delete;
    CustomerOrder& operator= (CustomerOrder&& order) noexcept;
    CustomerOrder(CustomerOrder&& order) noexcept;
    bool isOrderFilled();
    bool isItemFilled(const std::string& itemName) const;
    void fillItem(Station& station, std::ostream& os);
    void display(std::ostream& os) const;
    ~CustomerOrder();
};


}


#endif