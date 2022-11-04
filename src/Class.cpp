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

map<string,int> Class::get_occupation() const{
    return occupation_;
}

vector<pair<int, string>> Class::get_students() const{
    return students_;
}
void Class::print_students(bool by_code, bool descending) const{
    vector<pair<int, string>> temp = students_;

    if (by_code){ // ordenar por código
        if (descending){
            reverse(temp.begin(), temp.end());
        }

        for (const auto& info : temp){
            cout << "up" << info.first << "   " << info.second << endl;
        }
    }
    else{ // ordenar por nome
        sort(temp.begin(), temp.end(), order_by_name);

        if (descending){
            reverse(temp.begin(), temp.end());
        }

        for (const auto& info : temp){
            cout << "up" << info.first << "   " << info.second << endl;  
        }
    }
}

void Class::add_student(int studentCode, const string& studentName, const string& ucCode){
    bool found = false;
    
    // pesquisa binária
    int lower = 0, upper = (int) students_.size() - 1;

    while (lower <= upper){
        int mid = (lower + upper) / 2;

        if (students_[mid].first < studentCode){
            lower = mid + 1;
        }
        else if (students_[mid].first > studentCode){
            upper = mid - 1;
        }
        else{
            found = true;
            break;
        }
    }

    if (!found){
        students_.push_back({studentCode, studentName});
        occupation_[ucCode]++;
    }
    
    sort(students_.begin(), students_.end());
}

void Class::remove_student(string studentName){
    for(auto it = students_.begin(); it != students_.end(); it++){
        if(it->second == studentName){
            students_.erase(it);
            break;
        }
    }
}

bool Class::equals(Class c){
    return (c.get_classCode() == classCode_);
}

bool Class::operator<(const Class& c) const{
    return (classCode_ < c.get_classCode());
}

int Class::size() const{
    return students_.size();
}

