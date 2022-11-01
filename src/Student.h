#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <set>
#include "Schedule.h"

using namespace std;

class Student{
    private:
        string studentCode_;
        string studentName_;
        map<string, string> ucs_;
        set<string> classes_;
        Schedule schedule_;

    public:
        // constructor
        Student(string studentCode, string studentName);
        
        // methods
        string get_studentCode() const;
        string get_studentName() const;
        Schedule get_schedule() const;

        void add_uc(string ucCode, string classCode);
        void add_class(string classCode);
        void set_Schedule(Schedule a);

        void print_classes() const;
        void print_ucs() const;
};

#endif