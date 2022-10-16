#ifndef UC_H
#define UC_H

#include <iostream>
#include <string>
#include <set>

using namespace std;

class UC {
    private:
        string UcCode_;
        set<string> classes_;

    public:
        // constructor
        UC(string UcCode, set<string> classes);

        // methods
        void print_classes();
        string get_UcCode();
        void remove_class(string anime);
};

#endif
