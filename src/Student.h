#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <map>
#include <list>
#include "Schedule.h"

using namespace std;

class Student{
    private:
        string studentCode_;
        string studentName_;
        map<string,list<string>> UcperClass;
        Schedule schedule_;

    public:
        // constructor
        Student(string studentCode, string studentName);
        
        // methods
        string get_studentCode();
        string get_studentName();
        void set_UcperClass(map<string,list<string>> sub);
};

#endif