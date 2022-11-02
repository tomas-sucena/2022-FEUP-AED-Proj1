#include "UC.h"

// função auxiliar usada na ordenação do students_
bool foo(const pair<int, string> p1,
                   const pair<int, string> p2){
    return (p1.second < p2.second);
}

UC::UC(string ucCode, set<string> classes) : 
       ucCode_(ucCode), classes_(classes) {}

UC::UC(string ucCode, set<string> classes, Schedule schedule) :
       ucCode_(ucCode), classes_(classes), schedule_(schedule) {};

void UC::print_classes(){
    for (string anime : classes_){
        cout << anime << endl;
    }
}

string UC::get_UcCode(){
    return ucCode_;
}

set<string> UC::get_classes() const{
    return classes_;
}

void UC::remove_class(string classCode){
    for(auto kanna = classes_.begin(); kanna != classes_.end();){
        if (*kanna == classCode){
            kanna = classes_.erase(kanna);
        }
        else{
            kanna++;
        }
    }
}

void UC::print_students(bool by_code, bool descending) const{
    vector<pair<int, string>> temp = students_;

    if (by_code){ // ordenar por código
        if (descending){
            reverse(temp.begin(), temp.end());
        }

        for (auto info : temp){
            cout << "up" << info.first << "   " << info.second << endl;
        }
    }
    else{ // ordenar por nome
        sort(temp.begin(), temp.end(), foo);

        if (descending){
            reverse(temp.begin(), temp.end());
        }

        for (auto info : temp){
            cout << "up" << info.first << "   " << info.second << endl;
        }
    }
}

void UC::add_student(int studentCode, string studentName){
    students_.push_back({studentCode, studentName});
    sort(students_.begin(), students_.end());
}

void UC::add_schedule(Schedule schedule){
    schedule_ = schedule;
}

Schedule UC::get_schedule(){
    return schedule_;
}