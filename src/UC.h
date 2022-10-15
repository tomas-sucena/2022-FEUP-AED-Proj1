#ifndef UC_H
#define UC_H

#include <string>
#include <vector>
#include <iostream>
#include "Class.h"

using namespace std;

class UC
{
private:
    string UcCode_;
    vector<Class> classes_;

public:
    // constructor
    UC(string UcCode, vector<Class> classes);

    // methods
    void print_classes_();
    string get_UcCode();
    void remove_class(Class anime);
};

#endif
