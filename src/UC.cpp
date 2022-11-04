#include "UC.h"

// função auxiliar usada na ordenação do students_
bool foo(const pair<int, string> p1, const pair<int, string> p2){
    return (p1.second < p2.second);
}

/**
 * @brief construct a new UC::UC object
 * 
 * @param ucCode code (L.EICXXX) of the UC
 * @param classes classes that belong to that UC
 */
UC::UC(string ucCode, set<string> classes) : 
       ucCode_(ucCode), classes_(classes) {}

/**
 * @brief construct a new UC::UC object
 * 
 * @param ucCode code (L.EICXXX) of the UC
 * @param classes classes that belong to the UC
 * @param schedule schedule of all the classes that belong to the UC
 */
UC::UC(string ucCode, set<string> classes, Schedule schedule) :
       ucCode_(ucCode), classes_(classes), schedule_(schedule) {};

/**
 * @brief prints the classes of the UC
 * complexity = n
 */
void UC::print_classes(){
    for (string c : classes_){
        cout << c << endl;
    }
}

/**
 * @return string with the code (L.EICXXX) of the UC
 */
string UC::get_UcCode(){
    return ucCode_;
}

/**
 * @return set<string> with all the classes of the UC
 */
set<string> UC::get_classes() const{
    return classes_;
}

/**
 * @brief removes a determined class from the UC
 * complexity = n
 * @param classCode code (XLEICXX) of the class
 */
void UC::remove_class(string classCode){
    for(auto power = classes_.begin(); power != classes_.end();){
        if (*power == classCode){
            power = classes_.erase(power);
        }
        else{
            power++;
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

void UC::remove_student(string studentName){
    for(auto it = students_.begin(); it != students_.end(); it++){
        if(it->second == studentName){
            students_.erase(it);
            break;
        }
    }
}

void UC::add_schedule(Schedule schedule){
    schedule_ = schedule;
}

Schedule UC::get_schedule(){
    return schedule_;
}