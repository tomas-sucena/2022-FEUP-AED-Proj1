#include "Helpy.h"
#include <fstream>
#include <sstream>

map<string, int> Helpy::command = {{"display", 1}, {"print", 1}, {"show", 1}, 
                                   {"remove", 2}, {"add",3}};
map<string, int> Helpy::target = {{"uc", 6}, {"class", 8}, {"student", 10}, {"all", 12}};
map<string, int> Helpy::what = {{"schedule", 24}, {"classes", 27}, {"ucs", 30}, {"students", 33}};

// função auxiliar usada para tratar dos comandos
void lowercase(string& s, bool uppercase = false){
    for (char& c : s){
        c = (uppercase) ? toupper(c) : tolower(c);
    }
}

Helpy::Helpy(set<Student>& students, vector<UC>& UCs, vector<Class>& classes): 
             all_students(students), all_UCs(UCs), all_classes(classes){}

void Helpy::terminal(){
    cout << "Which mode would you prefer?" << endl << endl;
a1: cout << "* Guided" << endl;
    cout << "* Advanced" << endl << endl;

    string line; getline(cin, line);
    lowercase(line);

    istringstream line_(line);
    string temp;

    bool valid = false;
    while (line_ >> temp){  
        if (temp == "guided"){
            guided_mode();

            valid = true;
            break;
        }
        else if (temp == "advanced"){
            advanced_mode();

            valid = true;
            break;
        }
    }     

    if (!valid){
        cout << "Invalid command! Please choose one of the following:" << endl << endl;
        goto a1;
    }       
}

                                ///         ADVANCED MODE       ///
void Helpy::advanced_mode(){
    /*-----LER COMANDOS-----*/
    cout << endl << "Hello! How can I be of assistance?" << endl;

b1: string s1, s2, s3; 
    bool valid = false;

    cin >> s1; lowercase(s1);
    if (s1 == "quit" || s1 == "no"){
        goto e1;
    }

    cin >> s2;
    lowercase(s2);

    if(s1 == "process" && s2 == "queue"){
        processQueue();
        cout << "Queue has been processed" << endl;
        goto b1;
    }

    cin >> s3;
    lowercase(s3);

    // processar o comando    
    switch (command[s1] + target[s2] + what[s3]){
        case(31) : {
            display_uc_schedule(valid);

            break;
        }
        case(33) : {
            display_class_schedule(valid);

            break;
        }
        case(34) : {
            display_uc_classes(valid);

            break;
        }
        case (35) : {
            display_student_schedule(valid);

            break;
        }
        case(38) : {
            display_student_classes(valid);

            break;
        }
        case(39) : { // remove student classes
            cout << "Please type the code (upXXXXXXXXX) of the desired student"<<endl;
            string st; cin >>st;
            cout << "Please type the code of the class you want to remove" << endl;
            string cl; cin >> cl;
            queuer.push(Request(s1,s2,s3,st,cl));

            break;
        }
        case(40) : {
            display_uc_students(valid);

            break;
        }
        case(41) : {
            display_student_ucs(valid);

            break;
        }
        case(42) : {
            display_class_students(valid);

            break;
        }
        case(46) : {
            display_all_students();

            break;
        }
        default : {
            cout << endl << "Invalid command! Please, type another command." << endl;
            goto b1;
        }
    }

    cout << endl << "Anything else?" << endl;
    goto b1;

e1: cout << endl << "See you next time!" << endl;
}

                            ///             GUIDED MODE             ////

void Helpy::guided_mode(){

    /*-----LER COMANDOS-----*/
    cout << endl << "Hello! How can I be of assistance?" << endl;
    cout << endl;
    cout << "* Display" << endl;
    cout << "* Quit" << endl;
    cout << endl;

b2: string s1, s2, s3; 
    bool valid = false;

    cin >> s1; lowercase(s1);
    if (s1 == "quit" || s1 == "no"){
        goto e2;
    }
    else if (s1 == "display"){
        cout << endl;
        cout << "* UC" << endl;
        cout << "* Class" << endl;
        cout << "* Student" << endl;
        cout << endl;
    }

    cin >> s2; lowercase(s2);

    cout << endl;
    cout << "* Classes" << endl;
    cout << "* Schedule" << endl;
    cout << "* UCs" << endl;
    cout << endl;

    cin >> s3; lowercase(s3);

    // processar o comando    
    switch (command[s1] + target[s2] + what[s3]){
        case(31) : {
            display_uc_schedule(valid);

            break;
        }
        case(33) : {
            display_class_schedule(valid);

            break;
        }
        case(34) : {
            display_uc_classes(valid);

            break;
        }
        case (35) : {
            display_student_schedule(valid);

            break;
        }
        case(38) : {
            display_student_classes(valid);

            break;
        }
        case(39) : { // remove student classes
            cout << "Please type the code (upXXXXXXXXX) of the desired student"<<endl;
            string st; cin >>st;
            cout << "Please type the code of the class you want to remove" << endl;
            string cl; cin >> cl;
            queuer.push(Request(s1,s2,s3,st,cl));

            break;
        }
        case(40) : {
            display_uc_students(valid);

            break;
        }
        case(41) : {
            display_student_ucs(valid);

            break;
        }
        case(42) : {
            display_class_students(valid);

            break;
        }
        case(46) : {
            display_all_students();

            break;
        }
        default : {
            cout << endl << "Invalid command! Please, type another command." << endl;
            goto b2;
        }
    }

    cout << endl << "Anything else?" << endl;
    goto b2;

e2: cout << endl << "See you next time!" << endl;
}


void Helpy::display_uc_schedule(bool& valid) const{
    cout << endl << "Understood. Please select the desired UC." << endl;

    string uc; cin >> uc;
    lowercase(uc, true);

    for (UC u : all_UCs){
        if (u.get_UcCode() == uc){
            cout << endl << "The UC " << "\033[1m" << uc << 
            "\033[0m" << " has the following schedule:" << endl;

            u.get_schedule().print();

            valid = true;
            break;
        } 
    }

    if (!valid){
        cout << endl << "I'm sorry, but that UC does not exist." << endl;
    }
}

void Helpy::display_uc_classes(bool& valid) const{
    cout << endl << "Understood. Please select the desired UC." << endl;

    string uc; cin >> uc;
    lowercase(uc, true);
    
    for (UC u : all_UCs){
        if (u.get_UcCode() == uc){
            cout << endl << "The UC " << "\033[1m" << uc << 
            "\033[0m" << " has the following classes:" << endl;

            u.print_classes();

            valid = true;
            break;
        } 
    }

    if (!valid){
        cout << endl << "I'm sorry, but that UC does not exist." << endl;
    }
}

void Helpy::display_uc_students(bool& valid) const{

    // ordenação por código ou nome
    cout << endl << "Would you like to order the students by code (upXXXXXXXXX) or by name?" << endl;
    
    cin.ignore();
        
a1: string line; getline(cin, line);
    lowercase(line);

    istringstream line_(line);
    string temp;

    short by_code = 2;

    while (line_ >> temp){      
        lowercase(temp);

        if (temp == "code"){
            by_code = 1; 
            break;
        }
        else if (temp == "name"){
            by_code = 0;
            break;
        }
    }

    if (by_code == 2){
        cout << endl << "Invalid command. Please, try again." << endl
                << "Would you like to order the students by code (upXXXXXXXXX) or by name?" << endl;
        goto a1;
    }

    // ordenação ascendente ou descendente
a2: cout << endl << "And would you like to sort them in ascending or descending order?" << endl;

    getline(cin, line);
    lowercase(line);

    istringstream line2_(line);

    short descending = 2;

    while (line2_ >> temp){ 
        if (temp == "descending"){
            descending = 1; 
            break;
        }
        else if (temp == "ascending"){
            descending = 0;
            break;
        }
    }

    if (descending == 2){
        cout << "Invalid command. Please, try again." << endl;
        goto a2;
    }

    // escolher a UC
    cout << endl << "Understood. Please select the desired UC." << endl;

    string ucCode; cin >> ucCode;
    lowercase(ucCode, true);

    for (UC u : all_UCs){
        if (u.get_UcCode() == ucCode){
            cout << endl << "The UC " << "\033[1m" << ucCode << 
            "\033[0m" << " has the following students:" << endl;

            u.print_students(by_code, descending);

            valid = true;
            break;
        } 
    }

    if (!valid){
        cout << endl << "I'm sorry, but that UC does not exist." << endl;
    }
}

void Helpy::display_class_schedule(bool& valid) const{
    cout << endl << "Understood. Please select the desired class." << endl;

    string classCode; cin >> classCode;

    for (Class c : all_classes){
        if (c.get_classCode() == classCode){
            cout << endl << "The class " << "\033[1m" << classCode << 
            "\033[0m" << " has the following schedule:" << endl;

            c.get_schedule().print();

            valid = true;
            break;
        } 
    }

    if (!valid){
        cout << endl << "I'm sorry, but that class does not exist." << endl;
    }
}

void Helpy::display_class_students(bool& valid) const{
    // ordenação por código ou nome
    cout << endl << "Would you like to order the students by code (upXXXXXXXXX) or by name?" << endl;
    
    cin.ignore();
        
c1: string line; getline(cin, line);
    lowercase(line);

    istringstream line_(line);
    string temp;

    short by_code = 2;

    while (line_ >> temp){      
        lowercase(temp);

        if (temp == "code"){
            by_code = 1; 
            break;
        }
        else if (temp == "name"){
            by_code = 0;
            break;
        }
    }

    if (by_code == 2){
        cout << endl << "Invalid command. Please, try again." << endl
                << "Would you like to order the students by code (upXXXXXXXXX) or by name?" << endl;
        goto c1;
    }

    // ordenação ascendente ou descendente
c2: cout << endl << "And would you like to sort them in ascending or descending order?" << endl;

    getline(cin, line);
    lowercase(line);

    istringstream line2_(line);

    short descending = 2;

    while (line2_ >> temp){ 
        if (temp == "descending"){
            descending = 1; 
            break;
        }
        else if (temp == "ascending"){
            descending = 0;
            break;
        }
    }

    if (descending == 2){
        cout << "Invalid command. Please, try again." << endl;
        goto c2;
    }

    // escolher a turma
    cout << endl << "Understood. Please select the desired class." << endl;

    string classCode; cin >> classCode;
    lowercase(classCode, true);

    for (Class c : all_classes){
        if (c.get_classCode() == classCode){
            cout << endl << "The class " << "\033[1m" << classCode << 
            "\033[0m" << " has the following students:" << endl;

            c.print_students(by_code, descending);

            valid = true;
            break;
        } 
    }

    if (!valid){
        cout << endl << "I'm sorry, but that class does not exist." << endl;
    }
}

void Helpy::display_student_schedule(bool& valid) const{
    cout << endl << "Understood. Please write the code (upXXXXXXXXX) of the desired student." << endl;
    
    string studentCode; cin >> studentCode;

    for (Student s : all_students){
        if (s.get_studentCode() == studentCode){
            cout << endl << "The student " << "\033[1m" << s.get_studentName() << "\033[0m" 
            << " (up" << studentCode << ')' << " has the following schedule:" << endl;

            s.get_schedule().print();

            valid = true;
            break;
        }
    }

    if (!valid){
        cout << endl << "I'm sorry, but that student code is not valid." << endl;
    }
}

void Helpy::display_student_classes(bool& valid) const{
    cout << endl << "Understood. Please write the code (upXXXXXXXXX) of the desired student." << endl;

    string studentCode; cin >> studentCode;

    for (Student s : all_students){
        if (s.get_studentCode() == studentCode){
            cout << endl << "The student " << "\033[1m" << s.get_studentName() << "\033[0m" 
            << " (up" << studentCode << ')' << " belongs to the following classes:" << endl;

            s.print_classes();

            valid = true;
            break;
        }
    }

    if (!valid){
        cout << endl << "I'm sorry, but that student code is not valid." << endl;
    }
}

void Helpy::display_all_students() const{
    // ordenação por código ou nome
d1: cout << endl << "Would you like to order the students by code (upXXXXXXXXX) or by name?" << endl;
    
    cin.ignore();
        
    string line; getline(cin, line);
    lowercase(line);

    short by_code = 2;

    istringstream line_(line);
    string temp;

    while (line_ >> temp){           
        if (temp == "code"){
            by_code = 1; 
            break;
        }
        else if (temp == "name"){
            by_code = 0;
            break;
        }
    }

    if (by_code == 2){
        cout << "Invalid command. Please, try again." << endl;
        goto d1;
    }

    // imprimir todos os estudantes
    cout << endl << "Understood. These are all the students currently enrolled in LEIC:" << endl;

    for (Student s : all_students){
        (by_code) ? (cout << s.get_studentCode() << ' ' << s.get_studentName()) :
                    (cout << s.get_studentName() << " (up" << s.get_studentCode() << ')');
        cout << endl;
    }
}

void Helpy::display_student_ucs(bool& valid) const{
    cout <<endl << "Understood. Please write the code (upXXXXXXXXX) of the desired student." << endl;
    string studentCode; cin >> studentCode;

    for (Student s : all_students){
        if (s.get_studentCode() == studentCode){
            cout << endl << "The student " << "\033[1m" << s.get_studentName() << "\033[0m" 
            << " (up" << studentCode << ')' << " has the following UCs:" << endl;

            s.print_ucs();

            valid = true;
            break;
        }
    }

    if (!valid){
        cout << endl << "I'm sorry, but that student code is not valid." << endl;
    }
}

void Helpy::rewrite_file(){
    ofstream out("temp.csv");

    out << "StudentCode,StudentName,UcCode,ClassCode" << endl;

    for (Student s : all_students){
        string studentCode = s.get_studentCode();
        string studentName = s.get_studentName();

        for (pair<string, string> p : s.get_ucs()){
            out << studentCode << ',' << studentName 
                << p.first << ',' << p.second << '\r'
                << '\n';
        }
    }

    remove("../students_classes.csv");
    rename("temp.csv", "../students_classes.csv");
}

void Helpy::processQueue(){
    while(!queuer.empty()){
        Request sub = queuer.front();
    }
}