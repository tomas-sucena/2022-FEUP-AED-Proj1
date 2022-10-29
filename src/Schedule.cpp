#include "Schedule.h"

Schedule::Schedule(){}

Schedule::Schedule(list<Block> blocks) : blocks_(blocks) {
    blocks_.sort();
}

void Schedule::print(){
    for (auto it = blocks_.begin(); it != blocks_.end(); it++){
        cout << it->get_weekday() << ": " << it->get_code() << ' ' << 
        it->get_type() << " -> " << it->get_startHour() << '-' << it->get_endHour() << endl;
    }
}