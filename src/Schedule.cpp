#include "Schedule.h"

Schedule::Schedule(){}

Schedule::Schedule(list<Block> blocks) : blocks_(blocks) {
    blocks_.sort();
}