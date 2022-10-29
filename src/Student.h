#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include "Schedule.h"

using namespace std;

class Student{
    private:
        string studentCode_;
        string studentName_;
        Schedule schedule_;

    public:
        // constructor
        Student(string studentCode, string studentName);
        
        // methods
        string get_studentCode();
        string get_studentName();
};

#endif