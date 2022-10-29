#ifndef CLASS_H
#define CLASS_H

#include <iostream>
#include <string>
#include "Schedule.h"

using namespace std;

class Class {
    private:
        string classCode_;
        Schedule schedule_;

    public:
        // constructor
        Class(string classCode, Schedule schedule);

        // methods
        string get_classCode();
        Schedule get_schedule();

        bool equals(Class anime);
        bool operator<(Class c);
};

#endif