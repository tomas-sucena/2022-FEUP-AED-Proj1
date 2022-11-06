#include "UC.h"

/**
 * @brief construct a new UC::UC object
 * @param ucCode code of the UC
 * @param classes classes that belong to that UC
 */
UC::UC(string ucCode, map<string, set<string>> classes) :
       ucCode_(ucCode), classes_(classes) {}

/**
 * @brief construct a new UC::UC object
 * @param ucCode code of the UC
 * @param classes classes that belong to the UC
 * @param schedule schedule of all the classes that belong to the UC
 */
UC::UC(string ucCode, map<string, set<string>> classes, Schedule schedule) :
       ucCode_(ucCode), classes_(classes), schedule_(schedule) {};

/**
 * @brief prints the classes of the UC
 * complexity = n
 */
void UC::print_classes(){
    for (const auto& p : classes_){
        cout << p.first << endl;
    }
}

/**
 * @brief returns the code of the UC
 * @return string with the code of the UC
 */
string UC::get_ucCode() const{
    return ucCode_;
}

/**
 * @brief returns all the classes of the UC
 * @return set<string> with all the classes of the UC
 */
map<string, set<string>> UC::get_classes() const{
    return classes_;
}

/**
 * @brief removes a determined class from the UC
 * complexity = n
 * @param classCode code of the class that will be removed from the UC
 */
void UC::remove_class(string classCode){
    for(auto iter = classes_.begin(); iter != classes_.end();){
        if (iter->first == classCode){
            iter = classes_.erase(iter);
        }
        else{
            iter++;
        }
    }
}

/**
 * @brief prints all the students enrolled in the UC
 * complexity = n*log(n)
 * @param by_code true if ordered by student code; false if ordered by student name
 * @param descending true if in descending order; false if in ascending order
 */
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

/**
 * @brief adds a student to the UC
 * complexity = n*log(n)
 * @param studentCode code (upXXXXXXXXX) of the student
 * @param studentName name of the student
 */
void UC::add_student(int studentCode, string studentName, string classCode){
    students_.push_back({studentCode, studentName});
    sort(students_.begin(), students_.end());

    classes_[classCode].insert(studentName);
}

/**
 * @brief removes a student from the UC
 * complexity = n*log(n)
 * @param studentName name of the student
 */
void UC::remove_student(const int& studentCode){
    string studentName;

    // pesquisa binária
    int lower = 0, upper = (int) students_.size() - 1;

    int res = 0;
    while (lower <= upper){
        int mid = (lower + upper) / 2;

        if (students_[mid].first < studentCode){
            lower = mid + 1;
        }
        else if (students_[mid].first > studentCode){
            upper = mid - 1;
        }
        else{
            res = mid;
            studentName = students_[mid].second;

            break;
        }
    }

    students_.erase(students_.begin() + res);

    // remover o estudante da contagem de alunos em cada turma
    for (auto& p : classes_){
        if (p.second.erase(studentName) > 0) {
            break;
        }
    }
}

/**
 * @brief sets the schedule of the UC
 * @param schedule schedule of the UC
 */
void UC::set_schedule(Schedule schedule){
    schedule_ = schedule;
}

/**
 * @brief returns the schedule of the UC
 * @return Schedule with the schedule of the UC
 */
Schedule UC::get_schedule(){
    return schedule_;
}

/**
 * @brief compares two pairs
 * @param p1 first pair
 * @param p2 second pair
 * @return true if the string of the first pair comes before the string of the second pair
 * @return false if the string of the second pair comes before the string of the first pair
 */
bool foo(const pair<int, string> p1, const pair<int, string> p2){
    return (p1.second < p2.second);
}
