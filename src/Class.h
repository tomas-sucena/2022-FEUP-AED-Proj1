#ifndef CLASS_H
#define CLASS_H

#include <iostream>
#include <string>

using namespace std;

class Class {
    private:
        string classCode_;

    public:
        // constructor
        Class(string classCode);

        // methods
        string get_ClassCode();
        bool equals(Class anime);
        bool operator<(Class c);
};

#endif