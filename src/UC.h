#ifndef UC_H
#define UC_H

#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include "Schedule.h"

using namespace std;

class UC {
    private:
        string ucCode_;
        map<string, set<string>> classes_;
        vector<pair<int, string>> students_; // ordenado por código
        Schedule schedule_;

    public:
        // constructor
        UC(string ucCode, map<string, set<string>> classes);
        UC(string ucCode, map<string, set<string>> classes, Schedule schedule);

        // methods
        string get_ucCode() const;
        
        map<string, set<string>> get_classes() const;
        void print_classes();
        void add_class(string classCode);
        void remove_class(string classCode);

        void print_students(bool by_code, bool descending) const;
        void add_student(int studentCode, string studentName, string classCode);
        void remove_student(const int& studentCode);

        void set_schedule(Schedule schedule);
        Schedule get_schedule();
};

#endif
