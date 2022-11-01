#ifndef UC_H
#define UC_H

#include <iostream>
#include <string>
#include <set>
#include "Schedule.h"

using namespace std;

class UC {
    private:
        string ucCode_;
        set<string> classes_;
        set<pair<int, string>> students_;
        Schedule schedule_;

    public:
        // constructor
        UC(string ucCode, set<string> classes);
        UC(string ucCode, set<string> classes, Schedule schedule);

        // methods
        void print_classes();
        string get_UcCode();

        void add_class(string classCode);
        void remove_class(string classCode);

        void add_student(int studentCode, string studentName);

        void add_schedule(Schedule schedule);
        Schedule get_schedule();
};

#endif
