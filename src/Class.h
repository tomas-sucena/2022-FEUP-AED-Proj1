#ifndef CLASS_H
#define CLASS_H

#include <iostream>
#include <string>
#include <set>
#include "Schedule.h"

using namespace std;

class Class {
    private:
        string classCode_;
        set<pair<int, string>> students_;
        Schedule schedule_;

    public:
        // constructor
        Class(string classCode, Schedule schedule);

        // methods
        string get_classCode() const;
        Schedule get_schedule() const;
        void print_students() const;

        void add_student(int studentCode, string studentName);

        bool equals(Class anime);
        bool operator<(Class c);
};

#endif