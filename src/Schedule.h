#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <iostream>
#include <list>
#include <vector>

using namespace std;

struct block{
    string UcCode, weekday, type;
    float start, end;
};

class Schedule{
    private:
        list<block> l;

    public:
        Schedule();
};

#endif