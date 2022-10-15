#include "Class.h"

Class::Class(string ClassCode) : ClassCode_(ClassCode) {}

string Class::get_classCode(){
    return ClassCode_;
}

bool Class::equals(Class anime){
    return (anime.get_classCode() == ClassCode_);
}

bool Class::operator<(Class c){
    return (ClassCode_ < c.get_classCode());
}

