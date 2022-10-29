#include "Block.h"

map<string, int> week = {{"Monday", 2}, {"Tuesday", 3}, {"Wednesday", 4},
                         {"Thursday", 5}, {"Friday", 6}}; 
                         
Block::Block(string code, string weekday, string startHour, string duration, string type) :
             code_(code), weekday_(weekday), type_(type) {
    startHour_ = stof(startHour);
    endHour_ = stof(startHour) + stof(duration);
}

string Block::get_code(){
    return code_;
}

string Block::get_weekday(){
    return weekday_;
}

float Block::get_startHour(){
    return startHour_;
}

float Block::get_endHour(){
    return endHour_;
}

string Block::get_type(){
    return type_;
}

bool Block::operator<(Block b){
    if (this->get_weekday() == b.get_weekday()){
        return (this->get_startHour() < b.get_startHour());
    }
    
    return (week[this->get_weekday()] < week[b.get_weekday()]);
}