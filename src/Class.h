#ifndef CLASS_H
#define CLASS_H

#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include "Schedule.h"

using namespace std;

class Class {
    private:
        string classCode_;
        vector<pair<int, string>> students_; // ordenado por código
        Schedule schedule_;

    public:
        // constructor
        Class(string classCode, Schedule schedule);

        // methods
        string get_classCode() const;
        Schedule get_schedule() const;
        void print_students(bool by_code, bool descending) const;

        void add_student(int studentCode, string studentName);
        int size() const;

        bool equals(Class anime);
        bool operator<(Class c);
};

#endif