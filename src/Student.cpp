#include "Student.h"

Student::Student(string studentCode, string studentName) :
        studentCode_(studentCode), studentName_(studentName){}

string Student::get_studentCode() const{
    return studentCode_;
}

string Student::get_studentName() const{
    return studentName_;
}

void Student::set_UcperClass(map<string, list<string>> class_uc){
    UcperClass = class_uc;
}

void Student::set_Uc(){
    for (auto list_ : UcperClass){
        for(auto uc : list_.second){
        studentUC_.insert(uc);
        }
    }
}

Schedule Student::get_schedule() const{
    return schedule_;
}

void Student::set_Schedule(Schedule a){
    schedule_ = a;
}

void Student::print_classes() const{
    for (auto info : UcperClass){
        cout << info.first << endl;
    }
}

void Student::print_ucs() const{
    for (auto info : studentUC_){
        cout << info << endl;
    }
}
