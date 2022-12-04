#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

#include "Workstation.h"

namespace sdds{

    std::deque<CustomerOrder> g_pending = {}; //holds the orders to be placed onto the assembly line at the first station.
    std::deque<CustomerOrder> g_completed = {};  // holds the orders that have been removed from the last station and have been completely filled.
    std::deque<CustomerOrder> g_incomplete = {};

    Workstation::Workstation(const std::string str):Station(str){}//send string parameter to station constructor
    
    void Workstation::fill(std::ostream& os){
        if(!m_orders.empty()){
            m_orders.front().fillItem(*this, os); //if m_orders queue is not empty, fill the order at front of queue, using fillItem from customerOrder module.
        }
    }
    bool Workstation::attempToMoveOrder(){

        bool moved{false};

        if(!m_orders.empty()){
            if(m_orders.front().isItemFilled(getItemName())){ //check item at front of the queue is filled
                if(getNextStation() != nullptr){ //there is a next station in line
                    *m_pNextStation += std::move(m_orders.front()); //move item at front of queue to the next station (if there is)
                    m_orders.pop_front(); // remover the order from front of the orders queue
                    moved = true;
                }else{ //no next station in the line
                    if(m_orders.front().isOrderFilled()){//order at front of queue is filled
                        g_completed.push_back(std::move(m_orders.front())); //item is filled, no next station, and order is filled
                    }else{
                        g_incomplete.push_back(std::move(m_orders.front()));//item is filled, no next station, and order is not filled
                    }
                }
            }else{
                if(this->getQuantity() < 1){ //no items in stock 
                    if(getNextStation() != nullptr){ //theres a next station
                        *m_pNextStation += std::move(m_orders.front());  //move order at front of queue to next station
                        m_orders.pop_front();  //remove order from front of queue
                        moved = true;
                    }else{ //stock left no next station
                        g_incomplete.push_back(m_orders.front()); //item is not fille, push order at front of queue to incomplete queue 
                    }
                }
            }
            
        }
        return moved;
    }
    void Workstation::setNextStation(Workstation* station){
        if(m_pNextStation != nullptr){
            delete m_pNextStation;
        }
        m_pNextStation = station; 
    }
    Workstation* Workstation::getNextStation() const{
        return m_pNextStation;
    }
    void Workstation::display(std::ostream& os) const{
        os << getItemName() << "-->";
        if(getNextStation() != nullptr){
            os << m_pNextStation->getItemName(); //display next item of next station if there is another
        }else{
            os << "End of Line";  //no next station
        }
        os << '\n';
    }
    Workstation& Workstation::operator+=(CustomerOrder&& newOrder){
        std::cout << " here" << std::endl;
        m_orders.push_back(std::move(newOrder)); // adds new Customer Order to the back of the order queue
        std::cout << " here" << std::endl;
        return *this;
    }
    Workstation::~Workstation(){

    }







}
