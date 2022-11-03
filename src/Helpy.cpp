#include "Helpy.h"
#include <fstream>
#include <sstream>
#include <iostream>

map<string, int> Helpy::command = {{"display", 1}, {"print", 1}, {"show", 1}, 
                                   {"remove", 100}, {"add",200}};
map<string, int> Helpy::target = {{"uc", 6}, {"class", 8}, {"student", 10}, {"all", 22}};
map<string, int> Helpy::what = {{"schedule", 24}, {"classes", 27}, {"class", 27}, {"ucs", 30}, {"uc", 30}, {"students", 33},{"student", 33}};

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
    cout << "Which mode would you prefer?" << endl << endl;
a0: cout << "* Guided" << endl;
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
        cout << endl << "Invalid command! Please choose one of the following:" << endl << endl;
        goto a0;
    }       
}

                                ///         ADVANCED MODE       ///
void Helpy::advanced_mode(){
    /*-----LER COMANDOS-----*/
    cout << endl << "Hello! How can I be of assistance?" << endl;

b1: string s1, s2, s3; 
    bool valid = false;

    cin >> s1; lowercase(s1);

    if (s1 == "quit" || s1 == "no"  || s1 == "die"){
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
            cout << "Please type the code (upXXXXXXXXX) of the desired student"<<endl;
            string st; cin >>st;
            cout << "Please type the code of the class you want to remove" << endl;
            string cl; cin >> cl; lowercase(cl, true);
            queuer.push(Request(s1,s3,st,cl));
            log(Request(s1,s3,st,cl), "Fuck this");

            break;
        }
        case(140) : { // remove student uc
            cout << "Please type the code (upXXXXXXXXX) of the desired student"<<endl;
            string st; cin >>st;
            cout << "Please type the code of the uc you want to remove" << endl;
            string cl; cin >> cl; lowercase(cl, true);
            queuer.push(Request(s1,s3,st,cl));

            break;
        }
        case(240) : { //add uc to student
            cout << "Please type the code (upXXXXXXXXX) of the desired student"<<endl;
            string st; cin >>st;
            cout << "Please type the code of the uc you want to add" << endl;
            string cl; cin >> cl; lowercase(cl, true);
            cout << "Please type the code of the class you want to add the uc to" << endl;
            string f; cin >> f; lowercase(f, true);
            queuer.push(Request(s1,s3,st,cl,f));
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
b2: cout << endl;
    cout << "* Display" << endl;
    cout << "* Add" << endl;
    cout << "* Remove" << endl;
    cout << "* Quit" << endl;
    cout << endl;

    string s1, s2, s3, s4; 
    bool valid = false;

    cin >> s1; lowercase(s1);
    if (s1 == "quit"){
        goto e2;
    }
    else if (s1 == "display"){
        cout << endl;
        cout << "* All" << endl;
        cout << "* Class" << endl;
        cout << "* Student" << endl;
        cout << "* UC" << endl;
        cout << endl;
    }
    else{
        goto d1;
    }

    cin >> s2; lowercase(s2);

    if(s2 == "class"){
        cout << endl;
        cout << "* Schedule" << endl;
        cout << "* Students" << endl;
        cout << endl;
    }
    else if (s2 == "student"){
        cout << endl;
        cout << "* Classes" << endl;
        cout << "* Schedule" << endl;
        cout << "* UCs" << endl;
        cout << endl;
    }
    else if (s2 == "uc"){
        cout << endl;
        cout << "* Classes" << endl;
        cout << "* Students" << endl;
        cout << "* Schedule" << endl;
        cout << endl;
    }
    else if (s2 == "all"){
        cout << endl;
        cout << "* Classes" << endl;
        cout << "* Students" << endl;
        cout << "* UCs" << endl;
        cout << endl;
    }
    else if (s2 == "quit"){
        goto e2;
    }
    else{
        goto d1;
    }

    cin >> s3; lowercase(s3);
    
    if (s3 == "quit"){
        goto e2;
    }

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
            cout << "Please type the code (upXXXXXXXXX) of the desired student."<<endl;
            string st; cin >>st;
            cout << "Please type the code of the class you want to remove." << endl;
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
d1:     default : {
            cout << endl << "Invalid command! Please, try again." << endl;
            goto b2;
        }
    }

    cout << endl << "Anything else? (Yes/No)" << endl;
    cin >> s4; lowercase(s4);
    if (s4 == "yes" || s4 == "y"){
        goto b2;
    }

e2: cout << endl << "See you next time!" << endl;
}

/*-----FUNÇÕES DE IMPRESSÃO-----*/
void Helpy::display_uc_schedule(bool& valid) const{
a1: cout << endl << "Please type the code (L.EICXXX) of the desired UC." << endl;

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
        goto a1;
    }
}

void Helpy::display_uc_classes(bool& valid) const{
a2: cout << endl << "Please type the code (L.EICXXX) of the desired UC." << endl;

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
        goto a2;
    }
}

void Helpy::display_uc_students(bool& valid) const{
    cin.ignore();

    // ordenação por código ou nome
a3: cout << endl << "How would you like to order the students? (Code/Name)" << endl;
        
    string line; getline(cin, line);
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
        cout << endl << "Invalid command. Please, try again." << endl;
        goto a3;
    }

    // ordenação ascendente ou descendente
a4: cout << endl << "How would you like to sort them? (Ascending/Descending)" << endl;

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
        goto a4;
    }

    // escolher a UC
a5: cout << endl << "Please type the code (L.EICXXX) of the desired UC." << endl;

    string ucCode; cin >> ucCode;
    lowercase(ucCode, true);

    for (UC u : all_UCs){
        if (u.get_UcCode() == ucCode){
            cout << endl << "The UC " << "\033[1m" << ucCode << 
            "\033[0m" << " has the following students:" << endl << endl;

            u.print_students(by_code, descending);

            valid = true;
            break;
        } 
    }

    if (!valid){
        cout << endl << "I'm sorry, but that UC does not exist." << endl;
        goto a5;
    }
}

void Helpy::display_class_schedule(bool& valid) const{
a6: cout << endl << "Please type the code (XLEICXX) of the desired class." << endl;

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
        goto a6;
    }
}

void Helpy::display_class_students(bool& valid) const{
    cin.ignore();

    // ordenação por código ou nome
a7: cout << endl << "How would you like to order the students? (Code/Name)" << endl;
        
    string line; getline(cin, line);
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
        cout << endl << "Invalid command. Please, try again." << endl;
        goto a7;
    }

    // ordenação ascendente ou descendente
a8: cout << endl << "How would you like to sort them? (Ascending/Descending)" << endl;

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
        cout << endl << "Invalid command. Please, try again." << endl;
        goto a8;
    }

    // escolher a turma
a9: cout << endl << "Please type the code (XLEICXX) of the desired class." << endl;

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
        goto a9;
    }
}

void Helpy::display_student_schedule(bool& valid) const{
    cin.ignore();

a10:cout << endl << "Please write the code (upXXXXXXXXX) or the name of the desired student." << endl;

    string inp; getline(cin, inp);
    lowercase(inp);

    for (Student s : all_students){
        string smol = s.get_studentName();
        lowercase(smol);

        if (s.get_studentCode() == inp || smol == inp){
            cout << endl << "The student " << "\033[1m" << s.get_studentName() << "\033[0m" 
            << " (up" << s.get_studentCode() << ')' << " has the following schedule:" << endl;

            s.get_schedule().print();

            valid = true;
            break;
        }
    }

    if (!valid){
        cout << endl << "I'm sorry, but that student code is not valid." << endl;
        goto a10;
    }
}

void Helpy::display_student_classes(bool& valid) const{
    cin.ignore();

a11:cout << endl << "Understood. Please write the code (upXXXXXXXXX) of the desired student." << endl;

    string inp; getline(cin, inp);
    lowercase(inp);

    for (Student s : all_students){
        string smol = s.get_studentName();
        lowercase(smol);

        if (s.get_studentCode() == inp || smol == inp){
            cout << endl << "The student " << "\033[1m" << s.get_studentName() << "\033[0m" 
            << " (up" << s.get_studentCode() << ')' << " belongs to the following classes:" << endl;

            s.print_classes();

            valid = true;
            break;
        }
    }

    if (!valid){
        cout << endl << "I'm sorry, but that student code is not valid." << endl;
        goto a11;
    }
}

void Helpy::display_all_classes() const{
    set<string> all_classes_set;

    for (Class c : all_classes){
        all_classes_set.insert(c.get_classCode());
    }

a12:cout << endl << "What classes would u like to see?" << endl << endl;
    cout << "All" << endl;
    cout << "First Year (first)" << endl;
    cout << "Second Year (second)" << endl;
    cout << "Third Year (third)" << endl << endl;

    string temp; cin >> temp; lowercase(temp);

    if (temp == "all"){
        for (string class_code : all_classes_set){
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
        cout << endl << "Invalid command. Please, try again." << endl;
        goto a12;
    }
}

void Helpy::display_all_ucs() const{
    set<string> all_ucs_set;

    for (UC u : all_UCs){
        all_ucs_set.insert(u.get_UcCode());
    }

a13:cout << endl << "What UCs would you like to see?" << endl << endl;
    cout << "All" << endl;
    cout << "First Year (first)" << endl;
    cout << "Second Year (second)" << endl;
    cout << "Third Year (third)" << endl << endl;

    string temp; cin >> temp; lowercase(temp);

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
        cout << endl << "Invalid command. Please, try again." << endl;
        goto a13;
    }
}

void Helpy::display_all_students() const{
    cin.ignore();

    // ordenação por código ou nome
a14:cout << endl << "How would you like to order the students? (Code/Name)" << endl;
        
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
        cout << endl << "Invalid command. Please, try again." << endl;
        goto a14;
    }

    // ordenação ascendente ou descendente
a15:cout << endl << "How would you like to sort them? (Ascending/Descending)" << endl;

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
        cout << "Invalid command. Please, try again." << endl;
        goto a15;
    }

    // buscar condição
    int n = 0;

a16:cout << endl << "Would you like to filter the students by the number of UCs they are in? (Yes/No)" << endl;

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
            cout << endl << "Invalid command. Please, try again." << endl;
            goto a16;
        }
    }

    short cond = 3;
    if (filter){
a17:    cout << endl << "Would you like to see if students have less, more or exactly a number of UCs? (Less/More/Equal)" << endl;

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
            cout << endl << "Invalid command! Please, try again." << endl;
            goto a17;
        }

        cout << endl << "OK. Please type the number you want to use for filtering:"
             << endl;

        cin >> n;
    }

    // ordenar o all_students por código, se preciso
    if (by_code){
        sort(all_students.begin(), all_students.end(), order_bycode);
    }
        
    // imprimir todos os estudantes
    (filter) ? (cout << endl << "These are all the students that meet your criteria:") :
               (cout << endl << "These are all the students currently enrolled in LEIC:");
    cout << endl;

    if (descending){
        for (int i = (int) all_students.size() - 1; i >= 0; i--){
            Student s = all_students[i];

            int uc_num = (int) s.get_ucs().size();

            if (filter && cond == 0 && uc_num > n){
                cout << s.get_studentCode() << "  " << s.get_studentName() << endl;
                continue;
            }
            else if (filter && cond == 1 && uc_num < n){
                cout << s.get_studentCode() << "  " << s.get_studentName() << endl;
                continue;
            }
            else if (filter && cond == 2 && uc_num == n){
                cout << s.get_studentCode() << "  " << s.get_studentName() << endl;
                continue;
            }
            else if (!filter){
                cout << s.get_studentCode() << "  " << s.get_studentName() << endl; 
            }  
        }
    }
    else{
        for (Student s : all_students){
            int uc_num = (int) s.get_ucs().size();

            if (filter && cond == 0 && uc_num > n){
                cout << s.get_studentCode() << "  " << s.get_studentName() << endl;
                continue;
            }
            else if (filter && cond == 1 && uc_num < n){
                cout << s.get_studentCode() << "  " << s.get_studentName() << endl;
                continue;
            }
            else if (filter && cond == 2 && uc_num == n){
                cout << s.get_studentCode() << "  " << s.get_studentName() << endl;
                continue;
            }
            else if (!filter){
                cout << s.get_studentCode() << "  " << s.get_studentName() << endl;   
            }
        }
    }
}

void Helpy::display_student_ucs(bool& valid) const{
    cin.ignore();

a19:cout << endl << "Understood. Please write the code (upXXXXXXXXX) or the name of the desired student." << endl;
    
    string inp; getline(cin, inp);
    lowercase(inp);

    for (Student s : all_students){
        string smol = s.get_studentName();
        lowercase(smol);

        if (s.get_studentCode() == inp || smol == inp){
            cout << endl << "The student " << "\033[1m" << s.get_studentName() << "\033[0m" 
            << " (up" << s.get_studentCode() << ')' << " has the following UCs:" << endl;

            s.print_ucs();

            valid = true;
            break;
        }
    }

    if (!valid){
        cout << endl << "I'm sorry, but that student code is not valid." << endl;
        goto a19;
    }
}

/*-----FUNÇÕES DA FILA-----*/
void Helpy::rewrite_file(){
    fstream out;
    out.open("../students_classes.csv", ios::out);
    out << "StudentCode,StudentName,UcCode,ClassCode" << endl;

    for (Student s : all_students){
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
                    list<Block> blocks;
                    for (auto it = s.get_ucs().begin(); it != s.get_ucs().end(); it++){
                        for(Block b : class_blocks[it->second]){
                            if (b.get_code() == it->first)
                            {
                                blocks.push_back(b);
                            }
                        }
                    }
                    s.set_Schedule(Schedule(blocks));

                    string uc_ = sub.get_uc();
                    lowercase(uc_,true);
                    
                    cout << "UC-" << uc_ << " has sucessfully been removed from " << sub.get_student() << endl;
                } else {
                    string uc_ = sub.get_uc();
                    lowercase(uc_,true);
                    cout << "The selected student (" << sub.get_student() << ") does not have the selected UC (" << uc_ <<")" << endl;
                    cout << "Aborting Request" << endl;  
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
                        for(Block b : class_blocks[it->second]){
                            if (b.get_code() == it->first)
                            {
                                blocks.push_back(b);
                            }
                        }
                    }
                    s.set_Schedule(Schedule(blocks));
                cout << "The student has been removed from the selected class" << endl;
                } else {
                    string y = sub.get_uc();
                    lowercase(y,true);
                    cout << "The selected student (" << sub.get_student() << ") is not in the selected class (" << y <<")" << endl;
                    cout << "Aborting Request" << endl;  
                }
            }
            
        }
    }
    if(!valid){
            cout << "The selected student (" << sub.get_student() << ") does not exist in this database" << endl;
    }
}

void Helpy::add(Request sub){
    for(Student& s: all_students){
        if(s.get_studentCode() == sub.get_student()){
            map<string, string> a = s.get_ucs();
            if(a.find(sub.get_uc()) != a.end()){
                log(sub, "Failed because student already has selected uc");
                return;
            }
            int year = sub.get_class()[0] - '0';
            int num = (sub.get_class()[5] - '0') * 10 + (sub.get_class()[6] - '0');
            Class& c = all_classes[(year - 1) * 16 + (num - 1)];
            string conf = is_valid(s,c,sub.get_uc());
            if(conf == "yes"){
                if(s.get_classes().find(sub.get_class()) != s.get_classes().end()){
                    s.add_class(sub.get_class());
                    c.add_student(stoi(s.get_studentCode()), s.get_studentName());
                }
                a[sub.get_uc()] = sub.get_class();
                int num = (sub.get_uc()[6] - '0') * 10 + (sub.get_class()[7] - '0') - 1;
                UC& u = all_UCs[num];
                u.add_student(stoi(s.get_studentCode()), s.get_studentName());
                list<Block> blocks;
                for (auto it = s.get_ucs().begin(); it != s.get_ucs().end(); it++){
                    for(Block b : class_blocks[it->second]){
                        if (b.get_code() == it->first)
                        {
                            blocks.push_back(b);
                        }
                    }
                }
                s.set_Schedule(Schedule(blocks));
                break;
            } else {
                log(sub, conf);
                return;
            }
        }
    }
}

void Helpy::change(Request sub){}

string Helpy::is_valid(Student s, Class cl, string uc){
    if(cl.size() >= 30){
        return "Failed due to exceeding class limit";
    }
    Schedule st = s.get_schedule();
    Schedule c = cl.get_schedule();
    for(Block b: c.get_blocks()){
        if((b.get_type() == "TP" || b.get_type() == "PL") && b.get_code() == uc){
            for(Block su: st.get_blocks()){
                if((su.get_type() == "TP" || su.get_type() == "PL") && ((su.get_startHour() >= b.get_startHour() && su.get_startHour() < b.get_endHour()) || (su.get_endHour() > b.get_startHour() && su.get_endHour() <= b.get_endHour()))){
                    return "Failed due to Schedule overlap";
                }
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
    } else {
        f<<"Failed to " << r.get_type() << ' ' << r.get_uc() << "to class " << r.get_class() << " on student " << r.get_student() <<':' << s << endl;
    }
    f.close();
}

