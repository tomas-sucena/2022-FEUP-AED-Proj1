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
        map<string, list<string>> UcperClass;
        set<string> studentUC_;
        Schedule schedule_;

    public:
        // constructor
        Student(string studentCode, string studentName);

        bool operator<(const Student& s1) const;
        
        // methods
        string get_studentCode() const;
        string get_studentName() const;
        Schedule get_schedule() const;

        void set_UcperClass(map<string, list<string>> sub);
        void set_Uc();
        void set_Schedule(Schedule a);

        void print_classes() const;
        void print_ucs() const;
};

#endif