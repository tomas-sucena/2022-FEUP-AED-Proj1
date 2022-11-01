#include "Student.h"

Student::Student(string studentCode, string studentName) : studentCode_(studentCode), studentName_(studentName){}

string Student::get_studentCode() const{
    return studentCode_;
}

string Student::get_studentName() const{
    return studentName_;
}

Schedule Student::get_schedule() const{
    return schedule_;
}

void Student::set_UcperClass(map<string, list<string>> sub){
    UcperClass = sub;
}

void Student::set_Ucs(){
    
}

void Student::set_Schedule(Schedule a){
    schedule_ = a;
}

void Student::print_classes() const{
    for (auto info : UcperClass){
        cout << info.first << endl;
    }
}
