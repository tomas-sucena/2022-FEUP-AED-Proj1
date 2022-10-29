#include "Block.h"

Block::Block(string code, string weekday, string startHour, string duration, string type) :
             code_(code), weekday_(weekday), type_(type) {
    startHour_ = stof(startHour);
    end_ = startHour_ + stof(duration);
}

bool operator<(Block b1, Block b2){
    return (b1.get_startHour() < b2.get_startHour());
}