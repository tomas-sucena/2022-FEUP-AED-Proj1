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
        map<string, set<string>> ucs_;
        Schedule schedule_;

    public:
        // constructor
        Class(string classCode, Schedule schedule);

        // methods
        string get_classCode() const;
        vector<pair<int, string>> get_students() const;
        map<string, set<string>> get_ucs() const;
        Schedule get_schedule() const;

        void print_students(bool by_code, bool descending) const;
        void add_student(int studentCode, const string& studentName, const string& ucCode);
        void remove_student(const string& studentName, const string& ucCode = "");

        bool operator<(const Class& c) const; // overloading
};

#endif