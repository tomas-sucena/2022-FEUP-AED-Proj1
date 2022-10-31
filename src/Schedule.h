#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <iostream>
#include <list>
#include <vector>
#include "Block.h"

using namespace std;

class Schedule{
    private:
        list<Block> blocks_;

    public:
        // constructors
        Schedule();
        Schedule(list<Block> blocks);

        // methods
        list<Block> get_blocks() const;
        void print();
        string to_hours(float time);
};

#endif