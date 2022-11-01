#include "Student.h"

Student::Student(string studentCode, string studentName) :
        studentCode_(studentCode), studentName_(studentName){}

string Student::get_studentCode() const{
    return studentCode_;
}

string Student::get_studentName() const{
    return studentName_;
}

map<string, string> Student::get_ucs() const{
    return ucs_;
}

set<string> Student::get_classes() const{
    return classes_;
}

Schedule Student::get_schedule() const{
    return schedule_;
}

void Student::add_uc(string ucCode, string classCode){
    ucs_[ucCode] = classCode;
}

void Student::add_class(string classCode){
    classes_.insert(classCode);
}

void Student::set_Schedule(Schedule a){
    schedule_ = a;
}

void Student::print_classes() const{
    for (string classCode : classes_){
        cout << classCode << endl;
    }
}

void Student::print_ucs() const{
    for (auto info : ucs_){
        cout << info.first << endl;
    }
}

bool Student::operator<(const Student& s) const{
    return (studentName_ < s.get_studentName());
}
