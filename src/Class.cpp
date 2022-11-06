#include "Class.h"

// função auxiliar usada na ordenação do students_
bool order_by_name(const pair<int, string> p1,
                   const pair<int, string> p2){
    return (p1.second < p2.second);
}

bool Class::equals(Class c){
    return (c.get_classCode() == classCode_);
}

bool Class::operator<(const Class& c) const{
    return (classCode_ < c.get_classCode());
}

/**
 * @brief Construct a new Class:: Class object
 * 
 * @param classCode code (XLEICXX) of the class
 * @param schedule schedule of the class
 */
Class::Class(string classCode, Schedule schedule) : 
             classCode_(classCode), schedule_(schedule) {}

/**
 * @brief returns the code (XLEICXX) of the class
 * @return string 
 */
string Class::get_classCode() const{
    return classCode_;
}

/**
 * @brief returns the schedule of the class
 * @return Schedule 
 */
Schedule Class::get_schedule() const{
    return schedule_;
}


map<string, set<string>> Class::get_occupation() const{
    return occupation_;
}

/**
 * @brief returns all the students that are in the class
 * @return vector<pair<int, string>> 
 */
vector<pair<int, string>> Class::get_students() const{
    return students_;
}

/**
 * @brief prints all the students that are in the class
 * complexity = n*log(n)
 * @param by_code true if ordered by student code; false if ordered by student name
 * @param descending true if in descending order; false if in ascending order
 */
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

/**
 * @brief adds a student to the class
 * complexity = n*log(n)
 * @param studentCode code (upXXXXXXXXX) of the student
 * @param studentName name of the student
 * @param ucCode code (L.EICXXX) of the UC
 */
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
        sort(students_.begin(), students_.end());

        occupation_[ucCode].insert(studentName);
    }
}

/**
 * @brief removes a student from the class
 * complexity = n
 * @param studentName 
 */
void Class::remove_student(string studentName){
    for(auto it = students_.begin(); it != students_.end(); it++){
        if(it->second == studentName){
            students_.erase(it);
            break;
        }
    }

    // remover o estudante da contagem de alunos em cada UC
    for (auto& p : occupation_){
        auto it = p.second.find(studentName);

        if (it != p.second.end()){
            p.second.erase(it);
            break;
        }
    }
}

/**
 * @brief returns the number of students that are in the class
 * @return int 
 */
int Class::size() const{
    return students_.size();
}
