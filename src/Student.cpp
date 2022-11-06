#include "Student.h"

/**
 * @brief Construct a new Student:: Student object
 * 
 * @param studentCode code (upXXXXXXXXX) of the student
 * @param studentName name of the student
 */
Student::Student(string studentCode, string studentName) :
                 studentCode_(studentCode), studentName_(studentName){}

/**
 * @brief returns the code (upXXXXXXXXX) of the student
 * @return string 
 */
string Student::get_studentCode() const{
    return studentCode_;
}

/**
 * @brief returns the student name
 * @return string 
 */
string Student::get_studentName() const{
    return studentName_;
}

/**
 * @brief returns all the UCs the student is enrolled in
 * @return map<string, string> 
 */
map<string, string> Student::get_ucs() const{
    return ucs_;
}

/**
 * @brief returns all the classes the student is in
 * @return set<string> 
 */
set<string> Student::get_classes() const{
    return classes_;
}

/**
 * @brief returns the schedule of the student
 * @return Schedule 
 */
Schedule Student::get_schedule() const{
    return schedule_;
}

/**
 * @brief adds an UC to the student
 * @param ucCode code (L.EICXXX) of the UC that will be added
 * @param classCode code (XLEICXX) of the class of the UC that will be added
 */
void Student::add_uc(string ucCode, string classCode){
    ucs_[ucCode] = classCode;
}

/**
 * @brief adds a class to the student
 * @param classCode code (XLEICXX) of the class that will be added
 */
void Student::add_class(string classCode){
    classes_.insert(classCode);
}

/**
 * @brief sets the schedule of the student
 * @param a schedule of the student
 */
void Student::set_Schedule(Schedule a){
    schedule_ = a;
}

/**
 * @brief prints all the classes the student is in
 * complexity = n
 */
void Student::print_classes() const{
    for (string classCode : classes_){
        cout << classCode << endl;
    }
}

/**
 * @brief prints all the UCs the student is enrolled in
 * complexity = n
 */
void Student::print_ucs() const{
    for (auto info : ucs_){
        cout << info.first << endl;
    }
}

/**
 * @brief sets the map containing the relation between the UCs and classes of the student
 * @param sub map containing the relation between the UCs and classes of the student
 */
void Student::set_ucs(map<string,string> sub){
    ucs_ = sub;
}

/**
 * @brief sets the UCs of the student
 * complexity = n
 */
void Student::set_uc(){
    for(auto it : ucs_){
        uc_.insert(it.first);
    }
}

/**
 * @brief returns the UCs the student is enrolled in
 * @return set<string> 
 */
set<string> Student::get_uc() const{
    return uc_;
}

bool Student::operator<(const Student& s) const{
    return (studentName_ < s.get_studentName());
}
