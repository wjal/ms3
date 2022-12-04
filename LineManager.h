#ifndef LINE_MANAGER_H
#define LINE_MANAGER_H
#include <vector>
#include "Workstation.h"

namespace sdds{
class LineManager{
private:
    std::vector<Workstation*> m_activeLine;  //the collection of workstations for the current assembly line.
    size_t m_cntCustomerOrder;  //the total number of CustomerOrder objects
    Workstation* m_firstStation; //points to the first active station on the current line
public:
    LineManager(const std::string& file, const std::vector<Workstation*>& stations); //receives reference to file namewhich identifies active stations on assembly line, and the collection of workstations available to config assembly line
    void reorderStations(); //reorders workstations present in m_activeLine and stores reordered in same instance variable
    bool run(std::ostream& os); //one iteration of operations in all workstations in current assemly line.  keeps track of current iteration number, inserts into os iteration num, moves order at front of global g_pending queue to m_firstStation and remove it from g_pending queue.  exectues one fill for station, attempts to move order down line, return true if all customerorder have been filled, false if not
    void display(std::ostream& os) const;  //displays all active stations on the asemly line in current order
};
}

#endif //LINE_MANAGER_H