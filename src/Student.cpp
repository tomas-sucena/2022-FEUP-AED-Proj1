#include "Student.h"

/**
 * @brief Construct a new Student:: Student object
 * @param studentCode code of the student
 * @param studentName name of the student
 */
Student::Student(string studentCode, string studentName) :
                 studentCode_(studentCode), studentName_(studentName){}

/**
 * @brief returns the code of the student
 * @return string with the code of the student
 */
string Student::get_studentCode() const{
    return studentCode_;
}

/**
 * @brief returns the name of the student
 * @return string with the name of the student
 */
string Student::get_studentName() const{
    return studentName_;
}

/**
 * @brief returns all the UCs the student is enrolled in and the respective class
 * @return map<string, string> with all the UCs the student is enrolled in and the respective class
 */
map<string, string> Student::get_ucs() const{
    return ucs_;
}

/**
 * @brief returns all the classes the student is in
 * @return set<string> with all the classes the student is in
 */
set<string> Student::get_classes() const{
    return classes_;
}

/**
 * @brief returns the schedule of the student
 * @return Schedule with the schedule of the student
 */
Schedule Student::get_schedule() const{
    return schedule_;
}

/**
 * @brief adds an UC to the student
 * @param ucCode code of the UC that will be added
 * @param classCode code of the class of the UC that will be added
 */
void Student::add_uc(string ucCode, string classCode){
    ucs_[ucCode] = classCode;
}

/**
 * @brief adds a class to the student
 * @param classCode code of the class that will be added
 */
void Student::add_class(string classCode){
    classes_.insert(classCode);
}

/**
 * @brief removes a class from the student
 * ;complexity = O(log(n))
 * @param classCode code of the class that will be removed
 * @return number of classes erased
 */
int Student::remove_class(const string& classCode){
    return (int) classes_.erase(classCode);
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
 * ;complexity = O(n)
 */
void Student::print_classes() const{
    for (string classCode : classes_){
        cout << classCode << endl;
    }
}

/**
 * @brief prints all the UCs the student is enrolled in
 * ;complexity = O(n)
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
 * ;complexity = o(n)
 */
void Student::set_uc(){
    for(auto it : ucs_){
        uc_.insert(it.first);
    }
}

/**
 * @brief returns the UCs the student is enrolled in
 * @return set<string> with the UCs the student is enrolled in
 */
set<string> Student::get_uc() const{
    return uc_;
}

/**
 * @brief compares a student to other student
 * @param s student to be compared to
 * @return true if the name of the student comes first alphabetically
 * @return false if the name of the student to be compared to comes first alphabetically
 */
bool Student::operator<(const Student& s) const{
    return (studentName_ < s.get_studentName());
}
