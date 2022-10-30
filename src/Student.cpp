#include "Student.h"

Student::Student(string studentCode, string studentName) : studentCode_(studentCode), studentName_(studentName){}

string Student::get_studentCode(){
    return studentCode_;
}

string Student::get_studentName(){
    return studentName_;
}

void Student::set_UcperClass(map<string,list<string>> sub){
    UcperClass = sub;
}

bool Student::operator<(Student s){
    return this->get_studentName() < s.get_studentName();
}