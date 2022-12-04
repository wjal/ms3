#ifndef WORKSTATION_H
#define WORKSTATION_H

#include <deque>
#include "CustomerOrder.h" //also links Station.h

namespace sdds {
    extern std::deque<CustomerOrder> g_pending; //holds the orders to be placed onto the assembly line at the first station.
    extern std::deque<CustomerOrder> g_completed;  // holds the orders that have been removed from the last station and have been completely filled.
    extern std::deque<CustomerOrder> g_incomplete;  //holds the orders that have been removed from the last station and could not be filled completely.
class Workstation : public Station {
private:
    std::deque<CustomerOrder> m_orders{};
    Workstation* m_pNextStation{};
public:
    Workstation(const std::string str); //send string parameter to station constructor
    Workstation(const Workstation& wStation) = delete; // copy not allowed. delete copy constructor
    Workstation& operator=(const Workstation& wStation) = delete; // copy not allowed. delete copy assignment
    Workstation(Workstation&& wStation); // move not allowed. delete move constructor
    Workstation operator=(Workstation&& wStation); // move not allowed. delete move assignment
    void fill(std::ostream& os); //if m_orders queue is not empty, fill order at front of queue
    bool attempToMoveOrder(); //if m_orders is not empty attempt to move order at front of queue.  no next station, move to g_completed or g_incomplete
    void setNextStation(Workstation* station = nullptr); //sets parameter as next station.  nullptr is default
    Workstation* getNextStation() const; //returns next station
    void display(std::ostream& os) const; //display itemName and itemName at next station.  or end of line if no next station
    Workstation& operator+=(CustomerOrder&& newOrder); //add new customer order to the back of m_orders queue and then return workstation
    ~Workstation(); 
};




}


#endif //WORKSTATION_H