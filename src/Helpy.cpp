#include "Helpy.h"
#include <fstream>
#include <sstream>
#include <iostream>

// cores para o output
#define RESET   "\033[0;m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define BOLD    "\033[1m"
#define BREAK   "- - - - - - - - - - - - - - - - - - - - -"


map<string, int> Helpy::command = {{"display", 1}, {"print", 1}, {"show", 1}, {"modify", 0}, {"remove", 100}, {"add",200}};
map<string, int> Helpy::target = {{"uc", 6}, {"class", 8}, {"student", 10}, {"students", 10}, {"all", 22}, {"remove", 100}, {"add",200}};
map<string, int> Helpy::what = {{"schedule", 24}, {"classes", 27}, {"class", 27}, {"ucs", 30}, {"uc", 30}, {"students", 33}, {"student", 33}, {"zero", 0}};

// função auxiliar usada para tratar dos comandos
void lowercase(string& s, bool uppercase = false){
    for (char& c : s){
        c = (uppercase) ? toupper(c) : tolower(c);
    }
}

// função auxiliar usada para ordenar os estudantes por código
bool order_bycode(const Student s1, const Student s2){
    return (s1.get_studentCode() < s2.get_studentCode());
}


Helpy::Helpy(vector<Student>& students, vector<UC>& UCs, vector<Class>& classes, 
             map<string, list<Block>>& c_blocks, map<string, list<Block>>& u_blocks) : 
             all_students(students), all_UCs(UCs), all_classes(classes), 
             class_blocks(c_blocks), uc_blocks(u_blocks) {}

void Helpy::terminal(){
a0: cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "Which mode would you prefer?" << endl << endl;
    cout << "* Guided" << endl;
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
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << RED << "Invalid command! Please, try again." << RESET << endl;
        goto a0;
    }       
}

                                ///         ADVANCED MODE       ///
void Helpy::advanced_mode(){
    /*-----LER COMANDOS-----*/
b1: cout << endl << YELLOW << BREAK << RESET << endl;
    cout << endl << "How can I be of assistance?" << endl;

    string s1, s2, s3;
    istringstream s_;

    cin >> s1; lowercase(s1);

    if (s1 == "quit" || s1 == "no" || s1 == "die"){
        goto e1;
    }

    cin >> s2;
    lowercase(s2);

    if(s1 == "process" && s2 == "queue"){
        processQueue();
        cout << endl << "Queue has been processed" << endl;
        goto t1;
    }

    cin >> s3;
    lowercase(s3);
  
    // processar o comando    
    if(!process_command(s1, s2, s3)){
        goto b1;
    }

t1: cout << endl << YELLOW << BREAK << RESET << endl;
    cout << endl << "Anything else? (Yes/No)" << endl;

    s1.clear(); getline(cin >> ws, s1);
    lowercase(s1);

    s_.clear(); s_.str(s1);

    while (s_ >> s1){
        if (s1 == "yes" || s1 == "y"){
            goto b1;
        }
    }

e1: cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "See you next time!" << endl;
}

                            ///             GUIDED MODE             ////
void Helpy::guided_mode(){
    /*-----LER COMANDOS-----*/
b2: cout << endl << YELLOW << BREAK << RESET << endl;
    cout << endl << "Hello! How can I be of assistance?" << endl;
    cout << endl;
    cout << "* Display" << endl;
    cout << "* Add" << endl;
    cout << "* Remove" << endl;
    cout << "* Process" << endl;
    cout << "* Quit" << endl;
    cout << endl;

    string s1, s2, s3;
    s3 = "zero";

    istringstream s_;

    cin >> s1; lowercase(s1);
    if (s1 == "display"){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << "* All" << endl;
        cout << "* Class" << endl;
        cout << "* Student" << endl;
        cout << "* UC" << endl;
        cout << endl;
    }
    else if (s1 == "add"){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << "* Student" << endl;
        cout << endl;
    }
    else if (s1 == "remove"){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << "* Student" << endl;
        cout << endl;
    }
    else if (s1 == "process"){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << "* Queue" << endl;
        cout << "* Quit" << endl;
        cout << endl;
    }
    else if (s1 == "quit"){
        goto e2;
    }
    else{ // erro
        process_command(s1, s2, s3);
        goto b2;
    }

    cin >> s2; lowercase(s2);

    if (s1 == "process" && s2 == "queue"){
        processQueue();
        cout << endl << "Queue has been processed" << endl;
        goto t2;
    }
    else if (command[s1] == 200 && s2 == "student"){ // s1 -> add
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << "* UC" << endl;
        cout << endl;
    }
    else if (command[s1] == 100 && s2 == "student"){ // s1 -> remove
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << "* UC" << endl;
        cout << "* Class" << endl;
        cout << endl;
    }
    else if (s2 == "class"){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << "* Schedule" << endl;
        cout << "* Students" << endl;
        cout << endl;
    }
    else if (s2 == "student"){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << "* Classes" << endl;
        cout << "* Schedule" << endl;
        cout << "* UCs" << endl;
        cout << endl;
    }
    else if (s2 == "uc"){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << "* Classes" << endl;
        cout << "* Students" << endl;
        cout << "* Schedule" << endl;
        cout << endl;
    }
    else if (s2 == "all"){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << "* Classes" << endl;
        cout << "* Students" << endl;
        cout << "* UCs" << endl;
        cout << endl;
    }
    else if (s2 == "quit"){
        goto e2;
    }
    else{ // erro
        process_command(s1, s2, s3);
        goto b2;
    }

    cin >> s3; lowercase(s3);
    
    if (s3 == "quit"){
        goto e2;
    }

    // processar o comando
    if(!process_command(s1, s2, s3)){
        goto b2;
    }

t2: cout << endl << YELLOW << BREAK << RESET << endl;
    cout << endl << "Anything else? (Yes/No)" << endl;

    s1.clear(); getline(cin >> ws, s1);
    lowercase(s1);

    s_.clear(); s_.str(s1);

    while (s_ >> s1){
        if (s1 == "yes" || s1 == "y"){
            goto b2;
        }
    }

e2: cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "See you next time!" << endl;
}

bool Helpy::process_command(string& s1, string& s2, string& s3){
    switch (command[s1] + target[s2] + what[s3]){
        case(31) : {
            display_uc_schedule();
            break;
        }
        case(33) : {
            display_class_schedule();
            break;
        }
        case(34) : {
            display_uc_classes();
            break;
        }
        case(35) : {
            display_student_schedule();
            break;
        }
        case(38) : {
            display_student_classes();
            break;
        }
        case(40) : {
            display_uc_students();
            break;
        }
        case(41) : {
            display_student_ucs();
            break;
        }
        case(42) : {
            display_class_students();
            break;
        }
        case(50) : {
            display_all_classes();
            break;
        }
        case(53) : {
            display_all_ucs();
            break;
        }
        case(56) : {
            display_all_students();
            break;
        }
        case(137) : { // remove student classes
            remove_student_classes(s1, s2, s3);
            break;
        }
        case(140) : { // remove student uc
            remove_student_ucs(s1, s2, s3);
            break;
        }
        case(240) : { //add uc to student
            add_student_uc(s1, s2, s3);
            break;
        }
        default : {
            cout << endl << YELLOW << BREAK << RESET << endl;
            cout << endl << RED << "Invalid command! Please, type another command." << RESET << endl;

            return false;
        }
    }

    return true;
}


/*-----FUNÇÕES DE IMPRESSÃO-----*/

/**
 * @brief displays the schedule of a determined UC
 * complexity = n^3
 */
void Helpy::display_uc_schedule() const{
a1: cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "Please type the code (L.EICXXX) of the desired UC." << endl;

    string uc; cin >> uc;
    lowercase(uc, true);
    bool valid = false;

    for (UC u : all_UCs){
        if (u.get_ucCode() == uc){
            cout << endl << YELLOW << BREAK << RESET << endl << endl;
            cout << "The UC " << BOLD << uc << RESET << " has the following schedule:" << endl << endl;

            u.get_schedule().print();

            valid = true;
            break;
        } 
    }

    if (!valid){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << RED << "I'm sorry, but that UC does not exist." << RESET << endl;
        goto a1;
    }
}

/**
 * @brief displays the classes of a determined UC
 * complexity = n^3
 */
void Helpy::display_uc_classes() const{
a2: cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "Please type the code (L.EICXXX) of the desired UC." << endl;

    string uc; cin >> uc;
    lowercase(uc, true);

    bool valid = false;
    
    for (UC u : all_UCs){
        if (u.get_ucCode() == uc){
            cout << endl << YELLOW << BREAK << RESET << endl << endl;
            cout << "The UC " << BOLD << uc << RESET << " has the following classes:" << endl << endl;

            u.print_classes();

            valid = true;
            break;
        } 
    }

    if (!valid){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << RED << "I'm sorry, but that UC does not exist." << RESET << endl;
        goto a2;
    }
}

/**
 * @brief displays the students of a determined UC
 * complexity = n^3*log(n)
 */
void Helpy::display_uc_students() const{
    // ordenação por código ou nome
a3: cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "How would you like to order the students? (Code/Name)" << endl;
        
    string line; getline(cin >> ws, line);
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
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << RED << "Invalid command! Please, try again." << RESET << endl;
        goto a3;
    }

    // ordenação ascendente ou descendente
a4: cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "How would you like to sort them? (Ascending/Descending)" << endl;

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
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << RED << "Invalid command! Please, try again." << RESET << endl;
        goto a4;
    }

    // escolher a UC
a5: cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "Please type the code (L.EICXXX) of the desired UC." << endl;

    string ucCode; cin >> ucCode;
    lowercase(ucCode, true);

    bool valid = false;

    for (UC u : all_UCs){
        if (u.get_ucCode() == ucCode){
            cout << endl << YELLOW << BREAK << RESET << endl << endl;
            cout << "The UC " << BOLD << ucCode << RESET << " has the following students:" << endl << endl;

            u.print_students(by_code, descending);

            valid = true;
            break;
        } 
    }

    if (!valid){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << RED << "I'm sorry, but that UC does not exist." << RESET << endl;
        goto a5;
    }
}

void Helpy::display_class_schedule() const{
a6: cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "Please type the code (XLEICXX) of the desired class." << endl;

    string classCode; cin >> classCode;
    bool valid = false;

    for (const Class& c : all_classes){
        if (c.get_classCode() == classCode){
            cout << endl << YELLOW << BREAK << RESET << endl << endl;
            cout << "The class " << BOLD << classCode << RESET << " has the following schedule:" << endl << endl;

            c.get_schedule().print();

            valid = true;
            break;
        } 
    }

    if (!valid){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << RED << "I'm sorry, but that class does not exist." << RESET << endl;
        goto a6;
    }
}

void Helpy::display_class_students() const{
    // ordenação por código ou nome
a7: cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "How would you like to order the students? (Code/Name)" << endl;
        
    string line; getline(cin >> ws, line);
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
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << RED << "Invalid command! Please, try again." << RESET << endl;
        goto a7;
    }

    // ordenação ascendente ou descendente
a8: cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "How would you like to sort them? (Ascending/Descending)" << endl;

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
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << RED << "Invalid command! Please, try again." << RESET << endl;
        goto a8;
    }

    // escolher a turma
a9: cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "Please type the code (XLEICXX) of the desired class." << endl;

    string classCode; cin >> classCode;
    lowercase(classCode, true);
    bool valid = false;

    for (const Class& c : all_classes){
        if (c.get_classCode() == classCode){
            cout << endl << YELLOW << BREAK << RESET << endl << endl;
            cout << "The class " << BOLD << classCode << RESET << " has the following students:" << endl << endl;

            c.print_students(by_code, descending);

            valid = true;
            break;
        } 
    }

    if (!valid){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << RED << "I'm sorry, but that class does not exist." << RESET << endl;
        goto a9;
    }
}

void Helpy::display_student_schedule() const{
a10:cout << endl << "Please write the code (upXXXXXXXXX) or the name of the desired student." << endl;

    string inp; getline(cin >> ws, inp);
    lowercase(inp);

    bool valid = false;

    for (const Student& s : all_students){
        string smol = s.get_studentName();
        lowercase(smol);

        if (s.get_studentCode() == inp || smol == inp){
            cout << endl << YELLOW << BREAK << RESET << endl << endl;
            cout << "The student " << BOLD << s.get_studentName() << RESET << " (up" << s.get_studentCode() << ')' << " has the following schedule:" << endl << endl;

            s.get_schedule().print();

            valid = true;
            break;
        }
    }

    if (!valid){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << RED << "I'm sorry, but that student does not exist." << RESET << endl;
        goto a10;
    }
}

void Helpy::display_student_classes() const{
a11:cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "Please write the code (upXXXXXXXXX) of the desired student." << endl;

    string inp; getline(cin >> ws, inp);
    lowercase(inp);

    bool valid = false;

    for (const Student& s : all_students){
        string smol = s.get_studentName();
        lowercase(smol);

        if (s.get_studentCode() == inp || smol == inp){
            cout << endl << YELLOW << BREAK << RESET << endl << endl;
            cout << "The student " << BOLD << s.get_studentName() << RESET << " (up" << s.get_studentCode() << ')' << " belongs to the following classes:" << endl << endl;

            s.print_classes();

            valid = true;
            break;
        }
    }

    if (!valid){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << RED << "I'm sorry, but that student does not exist." << RESET << endl;
        goto a11;
    }
}

void Helpy::display_all_classes() const{
    set<string> all_classes_set;

    for (const Class& c : all_classes){
        all_classes_set.insert(c.get_classCode());
    }

a12:cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "What classes would you like to see?" << endl << endl;
    cout << "* All" << endl;
    cout << "* First Year (first)" << endl;
    cout << "* Second Year (second)" << endl;
    cout << "* Third Year (third)" << endl << endl;

    string temp; cin >> temp; lowercase(temp);

    cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "The classes are the following:" << endl << endl;

    if (temp == "all"){
        for (const string& class_code : all_classes_set){
            cout << class_code << endl;
        }
    }
    else if (temp == "first"){
        for (string class_code : all_classes_set){
            if (class_code[0] == '1'){
                cout << class_code << endl;
            }
        }
    }
    else if (temp == "second"){
        for (string class_code : all_classes_set){
            if (class_code[0] == '2'){
                cout << class_code << endl;
            }
        }
    }
    else if (temp == "third"){
        for (string class_code : all_classes_set){
            if (class_code[0] == '3'){
                cout << class_code << endl;
            }
        }
    }
    else{
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << RED << "Invalid command. Please, try again." << RESET << endl;
        goto a12;
    }
}

void Helpy::display_all_ucs() const{
    set<string> all_ucs_set;

    for (UC u : all_UCs){
        all_ucs_set.insert(u.get_ucCode());
    }

a13:cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << endl << "What UCs would you like to see?" << endl << endl;
    cout << "* All" << endl;
    cout << "* First Year (first)" << endl;
    cout << "* Second Year (second)" << endl;
    cout << "* Third Year (third)" << endl << endl;

    string temp; cin >> temp; lowercase(temp);

    cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "The UCs are the following:" << endl << endl;

    if (temp == "all"){
        for (string uc_code : all_ucs_set){
            cout << uc_code << endl;
        }
    }
    else if (temp == "first"){
        for (string uc_code : all_ucs_set){
            if (int(uc_code[6]) == '0'){
                cout << uc_code << endl;
            }
        }
    }
    else if (temp == "second"){
        for (string uc_code : all_ucs_set){
            if (int(uc_code[6]) == '1'){
                cout << uc_code << endl;
            }
        }
    }
    else if (temp == "third"){
        for (string uc_code : all_ucs_set){
            if (int(uc_code[6]) == '2'){
                cout << uc_code << endl;
            }
        }
    }
    else{
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << RED << "Invalid command! Please, try again." << RESET << endl;
        goto a13;
    }
}

void Helpy::display_all_students() const{
    // ordenação por código ou nome
a14:cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "How would you like to order the students? (Code/Name)" << endl;
        
    string line; getline(cin >> ws, line);
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
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << RED << "Invalid command! Please, try again." << RESET << endl;
        goto a14;
    }

    // ordenação ascendente ou descendente
a15:cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "How would you like to sort them? (Ascending/Descending)" << endl;

    getline(cin, line);
    lowercase(line);

    line_.clear();
    line_.str(line);

    short descending = 2;

    while (line_ >> temp){ 
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
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << RED << "Invalid command! Please, try again." << RESET << endl;
        goto a15;
    }

    // buscar condição
    int number = 0;

a16:cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "Would you like to filter the students by the number of UCs they are in? (Yes/No)" << endl;

    getline(cin, line);
    lowercase(line);

    line_.clear(); 
    line_.str(line);

    bool filter = false;
    while (line_ >> temp){
        if (temp == "yes" || temp == "y"){
            filter = true;
            break;
        }
        else if(temp == "no" || temp == "n"){
            break;
        }
        else{
            cout << endl << YELLOW << BREAK << RESET << endl << endl;
            cout << RED << "Invalid command! Please, try again." << RESET << endl;
            goto a16;
        }
    }

    short cond = 3;
    if (filter){
a17:    cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << "Would you like to see if the students have less, more or exactly a number of UCs? (Less/More/Equal)" << endl;

        getline(cin, line);
        lowercase(line);

        line_.clear();
        line_.str(line);

        while (line_ >> temp){
            if (temp == "less"){
                cond = 1;
                break;
            }
            else if (temp == "more"){
                cond = 0;
                break;
            }
            else if (temp == "equal" || temp == "exactly"){
                cond = 2;
                break;
            }
        }

        if (cond == 3){
            cout << endl << YELLOW << BREAK << RESET << endl << endl;
            cout << RED << "Invalid command! Please, try again." << RESET << endl;
            goto a17;
        }

        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << "Please type the number you want to use for filtering:" << endl;

        cin >> number;
    }

    // ordenar o all_students por código, se preciso
    if (by_code){
        sort(all_students.begin(), all_students.end(), order_bycode);
    }
        
    // imprimir todos os estudantes
    cout << endl << YELLOW << BREAK << RESET << endl << endl;
    (filter) ? (cout << "These are all the students that meet your criteria:") :
               (cout << "These are all the students currently enrolled in LEIC:");
    cout << endl << endl;

    if (descending){
        for (int i = (int) all_students.size() - 1; i >= 0; i--){
            Student s = all_students[i];

            int uc_num = (int) s.get_ucs().size();

            if (filter && cond == 0 && uc_num > number){
                cout << s.get_studentCode() << "  " << s.get_studentName() << endl;
                continue;
            }
            else if (filter && cond == 1 && uc_num < number){
                cout << s.get_studentCode() << "  " << s.get_studentName() << endl;
                continue;
            }
            else if (filter && cond == 2 && uc_num == number){
                cout << s.get_studentCode() << "  " << s.get_studentName() << endl;
                continue;
            }
            else if (!filter){
                cout << s.get_studentCode() << "  " << s.get_studentName() << endl; 
            }  
        }
    }
    else{
        for (const Student& s : all_students){
            int uc_num = (int) s.get_ucs().size();

            if (filter && cond == 0 && uc_num > number){
                cout << s.get_studentCode() << "  " << s.get_studentName() << endl;
                continue;
            }
            else if (filter && cond == 1 && uc_num < number){
                cout << s.get_studentCode() << "  " << s.get_studentName() << endl;
                continue;
            }
            else if (filter && cond == 2 && uc_num == number){
                cout << s.get_studentCode() << "  " << s.get_studentName() << endl;
                continue;
            }
            else if (!filter){
                cout << s.get_studentCode() << "  " << s.get_studentName() << endl;   
            }
        }
    }
}

void Helpy::display_student_ucs() const{
a19:cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "Please write the code (upXXXXXXXXX) or the name of the desired student." << endl;
    
    string inp; getline(cin >> ws, inp);
    lowercase(inp);

    bool valid = false;

    for (Student s : all_students){
        string smol = s.get_studentName();
        lowercase(smol);

        if (s.get_studentCode() == inp || smol == inp){
            cout << endl << YELLOW << BREAK << RESET << endl << endl;
            cout << "The student " << BOLD << s.get_studentName() << RESET << " (up" << s.get_studentCode() << ')' << " has the following UCs:" << endl << endl;

            s.print_ucs();

            valid = true;
            break;
        }
    }

    if (!valid){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << RED << "I'm sorry, but that student does not exist." << RESET << endl;
        goto a19;
    }
}

void Helpy::remove_student_classes(string& s1, string& s2, string& s3){
a20:cout << endl << YELLOW << BREAK << RESET << endl;

    cout << endl << "Please type the code (upXXXXXXXXX) or the name of the desired student" << endl;

    string st; getline(cin >> ws, st);
    lowercase(st);

    bool valid = false;

    for (const Student& s : all_students){
        string smol = s.get_studentName();
        lowercase(smol);

        if (s.get_studentCode() == st || smol == st){
            st = s.get_studentCode();
            valid = true;

            break;
        }
    }

    if (!valid){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << RED << "I'm sorry, but that student does not exist." << RESET << endl;
        goto a20;
    }

    cout << "Please type the code of the class you want to remove" << endl;
    string cl; cin >> cl; lowercase(cl, true);
    queuer.push(Request(s1,s3,st,cl));
    log(Request(s1,s3,st,cl), "Fuck this");
}

void Helpy::remove_student_ucs(string& s1, string& s2, string& s3){
a21:cout << endl << YELLOW << BREAK << RESET << endl;

    cout << endl << "Please type the code (upXXXXXXXXX) or the name of the desired student" << endl;

    string st; getline(cin >> ws, st);
    lowercase(st);

    bool valid = false;

    for (const Student& s : all_students){
        string smol = s.get_studentName();
        lowercase(smol);

        if (s.get_studentCode() == st || smol == st){
            st = s.get_studentCode();
            valid = true;

            break;
        }
    }

    if (!valid){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << RED << "I'm sorry, but that student does not exist." << RESET << endl;
        goto a21;
    }

    cout << "Please type the code of the uc you want to remove" << endl;
    string cl; cin >> cl; lowercase(cl, true);
    queuer.push(Request(s1,s3,st,cl));
}

void Helpy::add_student_uc(string& s1, string& s2, string& s3){
a22:cout << endl << YELLOW << BREAK << RESET << endl;

    cout << endl << "Please type the code (upXXXXXXXXX) or the name of the desired student" << endl;

    string st; getline(cin >> ws, st);
    lowercase(st);

    bool valid = false;

    for (const Student& s : all_students){
        string smol = s.get_studentName();
        lowercase(smol);

        if (s.get_studentCode() == st || smol == st){
            st = s.get_studentCode();
            valid = true;

            break;
        }
    }

    if (!valid){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << RED << "I'm sorry, but that student does not exist." << RESET << endl;
        goto a22;
    }

    cout << "Please type the code of the uc you want to add" << endl;
    string cl; cin >> cl; lowercase(cl, true);
    cout << "Please type the code of the class you want to add the uc to" << endl;
    string f; cin >> f; lowercase(f, true);
    queuer.push(Request(s1,s3,st,cl,f));
}


/*-----FUNÇÕES DA FILA-----*/
void Helpy::rewrite_file(){
    ofstream out("../csv/students_classes.csv", std::ofstream::trunc);

    out << "StudentCode,StudentName,UcCode,ClassCode" << endl;

    for (const Student& s : all_students){
        string studentCode = s.get_studentCode();
        string studentName = s.get_studentName();

        for (pair<string, string> p : s.get_ucs()){
            out << studentCode << ',' << studentName << ','
                << p.first << ',' << p.second << '\r'
                << '\n';
        }
    }

    out.close();
}

void Helpy::processQueue(){
    while(!queuer.empty()){
        Request sub = queuer.front();
        queuer.pop();
        if(sub.get_type() == "add"){
            add(sub);
        } else if (sub.get_type() == "remove"){
            rem(sub);
        } else {
            change(sub);
        }
    }

    rewrite_file();
}

void Helpy::rem(Request sub){
    bool valid = false;
    if(sub.get_target() == "uc"){
        for(Student& s : all_students){
            if(s.get_studentCode() == sub.get_student()){
                valid = true;
                map<string, string> a = s.get_ucs();

                auto it = a.find(sub.get_uc());

                if(it != a.end()){
                    a.erase(it);
                    s.set_ucs(a);

                    // criar o novo horário do estudante
                    list<Block> blocks = s.get_schedule().get_blocks();

                    auto iit = blocks.begin();
                    for (; iit != blocks.end(); iit++){
                        if (iit->get_code() == sub.get_uc()){
                            break;
                        }
                    }

                    blocks.erase(iit);
                    s.set_Schedule(Schedule(blocks));

                    // remover o estudante da UC
                    int dec = sub.get_uc()[6] - '0',
                        unit = sub.get_uc()[7] - '0';

                    UC& u = all_UCs[dec * 5 + (unit - 1)];
                    u.remove_student(stoi(s.get_studentCode()));

                    cout << endl << YELLOW << BREAK << RESET << endl << endl;
                    cout << "UC-" << u.get_ucCode() << " has sucessfully been removed from " << sub.get_student() << endl;

                    break;
                }
                else {
                    log(sub, "Failed because the student does not have the selected UC");
                    cout << RED << "Failed, see logs for more information"<< RESET << endl;
                    return;
                }
            }
        }
    } else if(sub.get_target() == "class"){
        for(Student& s: all_students){
            if (s.get_studentCode() == sub.get_student())
            {
                valid = true;
                set<string> cl = s.get_classes();
                if(cl.find(sub.get_uc()) != cl.end()){
                  cl.erase(sub.get_uc());
                  map<string, string> a = s.get_ucs();
                  for(auto i: a){
                    if(i.second == sub.get_uc()){
                        int num = (i.first[0] == 'L') ? (i.first[6] - '0') * 10 + (i.first[7] - '0') - 1 : all_UCs.size()-1;
                        UC& u = all_UCs[num];
                        u.add_student(stoi(s.get_studentCode()), s.get_studentName());
                        a.erase(i.first); // isto remove a class do estudante
                    }
                }
                int year = sub.get_uc()[0] - '0';
                int num = (sub.get_uc()[5] - '0') * 10 + (sub.get_uc()[6] - '0');
                Class& c = all_classes[(year - 1) * 16 + (num - 1)];
                c.remove_student(s.get_studentName()); // remover o estudante da class
                list<Block> blocks;
                    for (auto it = s.get_ucs().begin(); it != s.get_ucs().end(); it++){
                        for(const Block& b : class_blocks[it->second]){
                            if (b.get_code() == it->first)
                            {
                                blocks.push_back(b);
                            }
                        }
                    }
                    s.set_Schedule(Schedule(blocks));
                cout << "The student has been removed from the selected class" << endl;
                } else {
                    log(sub, "Failed because the student is not in the selected Class");
                    cout << RED << "Failed, see logs for more information"<< RESET <<  endl;
                    return;
                }
            }
            
        }
    }
    if(!valid){
        log(sub, "The selected student does not exist");
        cout << RED << "Failed, see logs for more information"<< RESET << endl;
    }
}

void Helpy::add(Request sub){
    for(Student& s: all_students){
        if(s.get_studentCode() == sub.get_student()){
            map<string, string> s_ucs = s.get_ucs();

            if(s_ucs.find(sub.get_uc()) != s_ucs.end()){
                log(sub, "Failed because the student is already enrolled in the selected UC");
                cout << RED << "Failed, see logs for more information" << RESET << endl;
                return;
            }

            int year = sub.get_class()[0] - '0';
            int num = (sub.get_class()[5] - '0') * 10 + (sub.get_class()[6] - '0');

            Class& c = all_classes[(year - 1) * 16 + (num - 1)];

            string conf = is_valid(s,c,sub.get_uc());

            if(conf == "yes"){
                if(s.get_classes().find(sub.get_class()) == s.get_classes().end()){
                    s.add_class(sub.get_class());
                    c.add_student(stoi(s.get_studentCode()), s.get_studentName(), sub.get_uc());
                }

                // atualizar as UCs do estudante
                s_ucs[sub.get_uc()] = sub.get_class();
                s.set_ucs(s_ucs);

                // adicionar o estudante à UC
                int dec = sub.get_uc()[6] - '0',
                    unit = sub.get_uc()[7] - '0';

                UC& u = all_UCs[dec * 5 + (unit - 1)];
                u.add_student(stoi(s.get_studentCode()), s.get_studentName());

                // atualizar o horário do estudante
                list<Block> blocks = s.get_schedule().get_blocks();

                for (const Block& b : u.get_schedule().get_blocks()){
                    if (b.get_code() == sub.get_class()){
                        blocks.push_back(b);
                        break;
                    }
                }

                s.set_Schedule(Schedule(blocks));

                cout << GREEN << "Successfully added UC " << sub.get_uc() << " to class " << sub.get_class() <<" on student " << sub.get_student() << RESET << endl;
            }
            else {
                log(sub, conf);
                cout << RED << "Failed, see logs for more information"<< RESET << endl;
            }

            break;
        }
    }
}

void Helpy::change(Request sub){
    for(Student& s: all_students){
        if(s.get_studentCode() == sub.get_student()){
            set<string> student_uc = s.get_uc();
            map<string,string> a = s.get_ucs();
            for(string ucs : student_uc){
                int num = (ucs[0] == 'L') ? (ucs[6] - '0') * 10 + (ucs[7] - '0') - 1 : (int) all_UCs.size()-1;
                UC& u = all_UCs[num];
                set<string> uc_class = u.get_classes();
                if(uc_class.find(sub.get_class()) == uc_class.end()){
                    log(sub, "Not all UCs from previous class are taught at the new class");
                    cout << RED << "Failed, see logs for more information"<< RESET << endl;
                    return;
                }
            }
            map<string, string> pain;
            for(const auto& i: a){
                if(student_uc.find(i.first) != student_uc.end()){
                    pain[i.first] = sub.get_class();
                } else {
                    pain[i.first] = i.second;
                }
            }
            list<Block> blocks;
            for (auto it = s.get_ucs().begin(); it != s.get_ucs().end(); it++){
                for (const Block& b : class_blocks[it->second]){
                    if (b.get_code() == it->first)
                    {
                        blocks.push_back(b);
                    }
                }
            }
            Schedule student_schedule = Schedule(blocks);
            int year = sub.get_class()[0] - '0';
            int num = (sub.get_class()[5] - '0') * 10 + (sub.get_class()[6] - '0');
            Class& c = all_classes[(year - 1) * 16 + (num - 1)];
            string grief = is_valid_change(s, student_schedule, c, student_uc);
            if(grief == "yes"){
                s.set_ucs(pain);
                s.set_Schedule(student_schedule);
                //c.add_student(stoi(s.get_studentCode()), s.get_studentName());
                year = sub.get_uc()[0] - '0';
                num = (sub.get_uc()[5] - '0') * 10 + (sub.get_uc()[6] - '0');
                Class& o = all_classes[(year - 1) * 16 + (num - 1)];
                o.remove_student(s.get_studentName());
                cout << GREEN << "Successfully changed student " << sub.get_student() << " from class " << sub.get_uc() << " to class " << sub.get_class() << "." << RESET << endl;
            } else {
                log(sub, grief);
                cout << RED << "Failed, see logs for more information"<< RESET << endl;
                return;
            }
        }
    }
}

string Helpy::is_valid(Student s, Class& cl, string uc){
    if(cl.get_occupation()[uc].size() >= 30){
        return "Failed due to exceeding class limit";
    }
    Schedule st = s.get_schedule();
    Schedule c = cl.get_schedule();
    for(const Block& b: c.get_blocks()){
        if((b.get_type() == "TP" || b.get_type() == "PL") && b.get_code() == uc){
            for(const Block& su: st.get_blocks()){
                if((su.get_type() == "TP" || su.get_type() == "PL") && ((su.get_startHour() >= b.get_startHour() && su.get_startHour() < b.get_endHour()) || (su.get_endHour() > b.get_startHour() && su.get_endHour() <= b.get_endHour()))){
                    return "Failed due to Schedule overlap";
                }
            }
        }
    }
    /*
    int num = (uc[0] == 'L') ? (uc[6] - '0') * 10 + (uc[7] - '0') - 1 : all_UCs.size() - 1;
    UC& u = all_UCs[num];
    set<string> sub = u.get_classes();
    int dif = 0;
    for(auto cla = sub.begin() ; cla != sub.end(); cla++){
        int year = (*cla)[0] - '0';
        int nu = ((*cla)[5] - '0') * 10 + ((*cla)[6] - '0');
        int max = INT32_MIN;
        Class& g = all_classes[(year - 1) * 16 + (nu - 1)];
        for(auto pain = sub.begin(); pain != sub.end(); pain++){
            if(pain == cla){
                continue;
            }
            year = (*pain)[0] - '0';
            nu = ((*pain)[5] - '0') * 10 + ((*pain)[6] - '0');
            Class& o = all_classes[(year - 1) * 16 + (nu - 1)];
            dif = (&g == &cl) ? abs(g.get_occupation()[uc] - o.get_occupation()[uc]) + 1 : abs(g.get_occupation()[uc] - o.get_occupation()[uc]);
            if(&g == &cl){
                cout << "Same" << endl;
            }
            cout << g.get_occupation()[uc] << endl;
            cout << o.get_occupation()[uc] << endl;
            if(dif > max){
                max = dif;
            }
        }
        if(max >= 4){
            return "Failed due to class disequilibrium";
        }
    }*/

    return "yes";
}

string Helpy::is_valid_change(Student s, Schedule schedule_, Class& c, set<string> ucs){
    if(c.size() >= 30){
        return "Failed due to exceeding class limit";
    }
    for(Block& b: schedule_.get_blocks()){
        if(b.get_type() == "TP" || b.get_type() == "PL"){
            for(Block& su: schedule_.get_blocks()){
                if((su.get_type() == "TP" || su.get_type() == "PL") && (&b != &su) && ((su.get_startHour() >= b.get_startHour() && su.get_startHour() < b.get_endHour()) || (su.get_endHour() > b.get_startHour() && su.get_endHour() <= b.get_endHour()))){
                    return "Failed due to Schedule overlap";
                }
            }
        }
    }
    for(string uc: ucs){
        int num = (uc[0] == 'L') ? (uc[6] - '0') * 10 + (uc[7] - '0') - 1 : all_UCs.size() - 1;
        UC& u = all_UCs[num];
        set<string> sub = u.get_classes();
        int dif = 0;
        for(auto cla = sub.begin() ; cla != sub.end(); cla++){
            int year = (*cla)[0] - '0';
            int nu = ((*cla)[5] - '0') * 10 + ((*cla)[6] - '0');
            int max = INT32_MIN;
            Class& g = all_classes[(year - 1) * 16 + (nu - 1)];
            for(auto pain = sub.begin(); pain != sub.end(); pain++){
                if(pain == cla){
                    continue;
                }
                year = (*pain)[0] - '0';
                nu = ((*pain)[5] - '0') * 10 + ((*pain)[6] - '0');
                Class& o = all_classes[(year - 1) * 16 + (nu - 1)];
                dif = (&g == &c) ? abs(int(g.get_occupation()[uc].size() - o.get_occupation()[uc].size())) + 1 :
                                   abs(int(g.get_occupation()[uc].size() - o.get_occupation()[uc].size()));
                if(&g == &c){
                    cout << "Same" << endl;
                }
                cout << g.get_occupation()[uc].size() << endl;
                cout << o.get_occupation()[uc].size() << endl;
                if(dif > max){
                    max = dif;
                }
            }
            if(max >= 4){
                return "Failed due to class disequilibrium";
            }
        }
    }

    return "yes";
}

void Helpy::log(Request r, string s){
    fstream f;
    f.open("../Logs.txt", ios::app);
    if(r.get_type() == "remove"){
        f<<"Failed to " << r.get_type() <<' ' << r.get_uc() <<  " from student " << r.get_student() << ":" << s << endl;
    } else if(r.get_type() == "add") {
        f<<"Failed to " << r.get_type() << ' ' << r.get_uc() << " to class " << r.get_class() << " on student " << r.get_student() <<':' << s << endl;
    } else{
        f << "Failed to " << r.get_type() << ' ' << r.get_student() << " from class " << r.get_uc() << " to class " << r.get_class() << ':' << s << endl;
    }
    f.close();
}

