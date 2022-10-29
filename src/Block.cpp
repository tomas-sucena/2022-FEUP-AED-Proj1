#include "Block.h"

Block::Block(string classCode, string weekday, string start, string duration, string type) :
             classCode_(classCode), weekday_(weekday), type_(type) {
    start_ = stof(start);
    end_ = start_ + stof(duration);
}