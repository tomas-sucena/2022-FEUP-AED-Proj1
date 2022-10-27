#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

using namespace std;

class Student{
    private:
        string studentCode_;
        string studentName_;

    public:
        //constructor
        Student(string studentCode, string studentName);
        
        //methods
        string get_studentCode();
        string get_studentName();
};

#endif