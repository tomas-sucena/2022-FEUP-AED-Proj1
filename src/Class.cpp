#include "Class.h"

Class::Class(string classCode) : classCode_(classCode) {}

string Class::get_ClassCode(){
    return classCode_;
}

bool Class::equals(Class c){
    return (c.get_ClassCode() == classCode_);
}

bool Class::operator<(Class c){
    return (classCode_ < c.get_ClassCode());
}

