#include "Schedule.h"

/**
 * @brief Construct a new Schedule:: Schedule object
 */
Schedule::Schedule(){}

/**
 * @brief Construct a new Schedule:: Schedule object
 * complexity = n*log(n)
 * @param blocks list of blocks containing classes (aulas)
 */
Schedule::Schedule(list<Block> blocks) : blocks_(blocks) {
    blocks_.sort();
}

/**
 * @brief returns all the blocks of the schedule
 * @return list<Block> with all the blocks of the schedule
 */
list<Block> Schedule::get_blocks() const{
    return blocks_;
}

/**
 * @brief prints the schedule
 * complexity = n
 */
void Schedule::print(){
    for (auto it = blocks_.begin(); it != blocks_.end(); it++){
        cout << it->get_weekday() << ": " << it->get_code() << ' ' << 
        it->get_type() << " -> " << to_hours(it->get_startHour()) << '-' 
        << to_hours(it->get_endHour()) << endl;
    }
}

/**
 * @brief converts the StartHour and the EndHour of a block to time values
 * @param time float number that represents a particular time value
 * @return string with a time value
 */
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