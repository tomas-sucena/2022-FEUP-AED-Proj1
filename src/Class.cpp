#include "Class.h"

Class::Class(string ClassCode) : ClassCode_(ClassCode) {}

string Class::get_ClassCode(){
    return ClassCode_;
}

bool Class::equals(Class anime){
    return (anime.get_ClassCode() == ClassCode_);
}

bool Class::operator<(Class c){
    return (ClassCode_ < c.get_ClassCode());
}

