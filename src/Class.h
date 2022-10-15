#ifndef CLASS_H
#define CLASS_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Class {
    private:
        string ClassCode_;

    public:
        // constructor
        Class(string ClassCode);

        // methods
        string get_classCode();
        bool equals(Class anime);
        bool operator<(Class c);
};

#endif