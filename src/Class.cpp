#include "Class.h"

Class::Class(string classCode, Schedule schedule) : 
             classCode_(classCode), schedule_(schedule) {}

string Class::get_classCode() const{
    return classCode_;
}

Schedule Class::get_schedule() const{
    return schedule_;
}

void Class::add_student(int studentCode, string studentName){
    students_.insert({studentCode, studentName});
}

bool Class::equals(Class c){
    return (c.get_classCode() == classCode_);
}

bool Class::operator<(Class c){
    return (classCode_ < c.get_classCode());
}

