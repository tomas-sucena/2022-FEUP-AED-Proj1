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
        set<string> classes_;
        vector<pair<int, string>> students_; // ordenado por código
        Schedule schedule_;

    public:
        // constructor
        UC(string ucCode, set<string> classes);
        UC(string ucCode, set<string> classes, Schedule schedule);

        // methods
        string get_UcCode();
        
        set<string> get_classes() const;
        void print_classes();
        void add_class(string classCode);
        void remove_class(string classCode);

        void print_students(bool by_code, bool descending) const;
        void add_student(int studentCode, string studentName);

        void add_schedule(Schedule schedule);
        Schedule get_schedule();
};

#endif
