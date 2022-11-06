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
        set<string> uc_;
        Schedule schedule_;

    public:
        // constructor
        Student(string studentCode, string studentName);
        
        // methods
        string get_studentCode() const;
        string get_studentName() const;
        map<string, string> get_ucs() const;
        set<string> get_classes() const;
        Schedule get_schedule() const;
        set<string> get_uc() const;

        void set_Schedule(Schedule a);
        void set_ucs(map<string,string> sub);
        void set_uc();

        void add_uc(string ucCode, string classCode);
        void add_class(string classCode);

        int remove_class(const string& classCode);

        void print_classes() const;
        void print_ucs() const;

        bool operator<(const Student& s) const; // overloading
};

#endif