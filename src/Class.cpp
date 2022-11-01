#include "Class.h"

// função auxiliar usada na ordenação do students_
bool order_by_name(const pair<int, string> p1,
                   const pair<int, string> p2){
    return (p1.second < p2.second);
}

Class::Class(string classCode, Schedule schedule) : 
             classCode_(classCode), schedule_(schedule) {}

string Class::get_classCode() const{
    return classCode_;
}

Schedule Class::get_schedule() const{
    return schedule_;
}

void Class::print_students(bool by_code, bool descending) const{
    vector<pair<int, string>> temp = students_;

    if (by_code){ // ordenar por código
        if (descending){
            reverse(temp.begin(), temp.end());
        }

        for (auto info : temp){
            cout << info.first << " (" << info.second << 
            ')' << endl;
        }
    }
    else{ // ordenar por nome
        sort(temp.begin(), temp.end(), order_by_name);

        if (descending){
            reverse(temp.begin(), temp.end());
        }

        for (auto info : temp){
            cout << info.second << " up(" << info.first << 
            ")" << endl;  
        }
    }
}

void Class::add_student(int studentCode, string studentName){
    /*
    // pesquisa binária
    int lower = 0, upper = (int) students_.size() - 1;

    int res = 0;
    while (lower <= upper){
        int mid = (lower + upper) / 2;

        if (students_[mid].first < studentCode){
            lower = mid + 1;
        }
        else{
            upper = mid - 1;
            res = mid;
        }
    }

    students_.insert(students_.begin() + res, {studentCode, studentName});*/
    students_.push_back({studentCode, studentName});
    sort(students_.begin(), students_.end());
}

bool Class::equals(Class c){
    return (c.get_classCode() == classCode_);
}

bool Class::operator<(Class c){
    return (classCode_ < c.get_classCode());
}

