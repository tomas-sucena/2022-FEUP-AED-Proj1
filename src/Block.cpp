#include "Block.h"

map<string, int> Block::week = {{"Monday", 2}, {"Tuesday", 3}, {"Wednesday", 4},
                                {"Thursday", 5}, {"Friday", 6}}; 

Block::Block(string code, string weekday, string startHour, string duration, string type) :
             code_(code), weekday_(weekday), type_(type) {
    startHour_ = stof(startHour);
    endHour_ = stof(startHour) + stof(duration);
}

bool Block::operator<(const Block& b) const{
    if (get_weekday() == b.get_weekday()){
        return (get_startHour() < b.get_startHour());
    }
    
    return (week[get_weekday()] < week[b.get_weekday()]);
}

string Block::get_code() const{
    return code_;
}

string Block::get_weekday() const{
    return weekday_;
}

float Block::get_startHour() const{
    return startHour_;
}

float Block::get_endHour() const{
    return endHour_;
}

string Block::get_type() const{
    return type_;
}
