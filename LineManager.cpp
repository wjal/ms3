#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>

#include "LineManager.h"
#include "Utilities.h"


namespace sdds {

LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations){

    std::ifstream assemblyLine(file);

     //read til end of assembly line file

        Utilities utility; //new utilities object to extract tokens (workstations)
        
        size_t next_pos{0};

        std::string tempLine;
        std::string leftStationName; //name of station on left hand side of each line
        std::string rightStationName; //name station on right hand side of line (if no station on right hand side, the one on left is the last station)

        Workstation* leftStation{nullptr};//station on left hand side of each line in the file
        Workstation* rightStation{nullptr};//station on right hand side of each line in the file (will be next station)
        
        
        int i = 0;
        while(getline(assemblyLine, tempLine)){
            bool more{true};
            leftStationName = utility.extractToken(tempLine, next_pos, more);
            //check for and return station from vector of workstations parameter if matches the name extracted from file
            leftStation = *std::find_if(stations.begin(), stations.end(), [&](Workstation* workstation){
                return workstation->getItemName() == leftStationName;        
            });
            //add to active line
            
            
            if(tempLine[next_pos - 1] == utility.getDelimiter()){
                more = true;
            }
            std::cout << tempLine[next_pos - 1] <<std::endl;
            std::cout<< "left station: " << leftStation->getItemName() << std::endl;
            m_activeLine.push_back(leftStation);

            if(more){//check if last station or not
                rightStationName = utility.extractToken(tempLine, next_pos, more);
                
                //check for and return station from vector of stations param if matches name extracted from right hand of line from tempLine (assemblyLine file)
                rightStation = *std::find_if(stations.begin(), stations.end(), [&](Workstation* workstation){
                    return workstation->getItemName() == rightStationName;    
                });
                std::cout << "here after more" <<std::endl;
                std::cout << more << std::endl;
                //set the 'next station' for the each station 
                leftStation->setNextStation(rightStation);
                std::cout << "here after set" <<std::endl;
                
            }
            std::cout << "post more check" <<std::endl;
            i++;
            std::cout << "times through: " << i << std::endl;
            more = true;
        } //done while loop of reading assemblyLine file
        //find first station in assembly line
        Workstation* temp{nullptr}; //acts as first station while searching. setting to null makes sure that last station is returned first in for_each/find_if algorithm. work backwards using getNextStation to return the station before until first station.
        std::for_each(stations.begin(), stations.end(), [&](Workstation* station1){
            temp = *std::find_if(stations.begin(), stations.end(), [&](Workstation* station2){
                return station2->getNextStation() == temp; //first time will be nullptr, so returns last, with no rightHand station in string from assemblyLine file
            });
        });
    m_firstStation = temp;
    m_cntCustomerOrder = g_pending.size(); //set customer order count to the size of pending orders
    assemblyLine.close();
}
void LineManager::reorderStations(){


}
bool LineManager::run(std::ostream& os){

    bool allOrdersAccounted{false}; //accounts for all orders being filled 

    static size_t i{0}; //keep track of all iterations of run()
    os << "Line Manager Iteration: " << i + 1 << std::endl;
    i++;

    //if pending isnt empty move front to m_firstStation
    
    if(!g_pending.empty()){
        *m_firstStation += std::move(g_pending.front());
        g_pending.pop_front();
    }
    //one fill for each station in active line
    std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation* station){
        station->fill(os);
    });
    //attempt to move order for each station in active line
    std::for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation* station){
        station->attempToMoveOrder();
    });
    if(m_cntCustomerOrder == (g_completed.size() + g_incomplete.size())){ //every order placed in incomplete or completed queue sums to what was pending after file loaded in constructor
        allOrdersAccounted = true;
    }

return allOrdersAccounted;
    
}
void LineManager::display(std::ostream& os) const{

    if(!m_activeLine.empty()){
        for(auto i = m_activeLine.begin(); i < m_activeLine.end(); i++){
            (*i)->display(os);
        }
    }
}

}