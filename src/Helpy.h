#ifndef HELPY_H
#define HELPY_H

#include <set>
#include <vector>
#include <map>
#include "Student.h"
#include "Block.h"
#include "UC.h"
#include "Class.h"
#include "Schedule.h"


class Helpy
{
private:
    set<Student> all_students;
    vector<UC> all_UCs;
    vector<Class> all_classes;
    
public:
    Helpy(set<Student> students, vector<UC> UCs, vector<Class> classes);
    void terminal();

};


#endif