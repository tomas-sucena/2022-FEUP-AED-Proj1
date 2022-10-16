#ifndef CLASS_H
#define CLASS_H

#include <iostream>
#include <string>

using namespace std;

class Class {
    private:
        string ClassCode_;

    public:
        // constructor
        Class(string ClassCode);

        // methods
        string get_ClassCode();
        bool equals(Class anime);
        bool operator<(Class c);
};

#endif