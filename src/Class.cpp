#include "Class.h"

Class::Class(string ClassCode) : ClassCode_(ClassCode) {}

string Class::get_ClassCode(){
    return ClassCode_;
}

bool Class::equals(Class c){
    return (c.get_ClassCode() == ClassCode_);
}

bool Class::operator<(Class c){
    return (ClassCode_ < c.get_ClassCode());
}

