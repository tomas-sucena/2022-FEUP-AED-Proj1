#include "Schedule.h"

Schedule::Schedule(){}

Schedule::Schedule(list<Block> blocks) : blocks_(blocks) {
    blocks_.sort();
}

list<Block> Schedule::get_blocks() const{
    return blocks_;
}

void Schedule::print(){
    for (auto it = blocks_.begin(); it != blocks_.end(); it++){
        cout << it->get_weekday() << ": " << it->get_code() << ' ' << 
        it->get_type() << " -> " << to_hours(it->get_startHour()) << '-' 
        << to_hours(it->get_endHour()) << endl;
    }
}

string Schedule::to_hours(float time){
    istringstream time_(to_string(time));

    string hour, min;

    getline(time_, hour, '.');
    getline(time_, min);

    if (min == ""){ 
        return (hour + ":00");
    }

    min = to_string(int(stof("0." + min) * 60));

    if (min.size() < 2){
        min = "0" + min;
    }

    return (hour + ":" + min);
}