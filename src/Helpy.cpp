#include "Helpy.h"
#include <fstream>
#include <sstream>

map<string, int> Helpy::command = {{"display", 1}, {"print", 1}, {"show", 1}, 
                                   {"remove", 100}, {"add",200}};
map<string, int> Helpy::target = {{"uc", 6}, {"class", 8}, {"student", 10}, {"all", 12}};
map<string, int> Helpy::what = {{"schedule", 24}, {"classes", 27}, {"class", 27}, {"ucs", 30}, {"uc", 30}, {"students", 33}};

// função auxiliar usada para tratar dos comandos
void lowercase(string& s, bool uppercase = false){
    for (char& c : s){
        c = (uppercase) ? toupper(c) : tolower(c);
    }
}

Helpy::Helpy(vector<Student> students, vector<UC> UCs, vector<Class> classes, 
             map<string, list<Block>> c_blocks, map<string, list<Block>> u_blocks) : 
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
        case(46) : {
            display_all_students();

            break;
        }
        case(137) : { // remove student classes
            cout << "Please type the code (upXXXXXXXXX) of the desired student"<<endl;
            string st; cin >>st;
            cout << "Please type the code of the class you want to remove" << endl;
            string cl; cin >> cl; lowercase(cl, true);
            queuer.push(Request(s1,s2,s3,st,cl));

            break;
        }
        case(140) : { // remove student uc
            cout << "Please type the code (upXXXXXXXXX) of the desired student"<<endl;
            string st; cin >>st;
            cout << "Please type the code of the uc you want to remove" << endl;
            string cl; cin >> cl; lowercase(cl, true);
            queuer.push(Request(s1,s2,s3,st,cl));

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
        case(46) : {
            display_all_students();

            break;
        }
    d1: default : {
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
a2: cout << endl << "Please type the code (L.EICXXX) of the desired UC." << endl;

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
        goto a2;
    }
}

void Helpy::display_uc_classes(bool& valid) const{
a3: cout << endl << "Please type the code (L.EICXXX) of the desired UC." << endl;

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
        goto a3;
    }
}

void Helpy::display_uc_students(bool& valid) const{

    // ordenação por código ou nome
a4: cout << endl << "How would you like to order the students? (Code/Name)" << endl;
    
    cin.ignore();
        
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
        goto a4;
    }

    // ordenação ascendente ou descendente
a5: cout << endl << "How would you like to sort them? (Ascending/Descending)" << endl;

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
        goto a5;
    }

    // escolher a UC
a6: cout << endl << "Please type the code (L.EICXXX) of the desired UC." << endl;

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
        goto a6;
    }
}

void Helpy::display_class_schedule(bool& valid) const{
a7: cout << endl << "Please type the code (XLEICXX) of the desired class." << endl;

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
        goto a7;
    }
}

void Helpy::display_class_students(bool& valid) const{
    // ordenação por código ou nome
a8: cout << endl << "How would you like to order the students? (Code/Name)" << endl;
    
    cin.ignore();
        
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
        goto a8;
    }

    // ordenação ascendente ou descendente
a9: cout << endl << "How would you like to sort them? (Ascending/Descending)" << endl;

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
        goto a9;
    }

    // escolher a turma
a10:cout << endl << "Please type the code (XLEICXX) of the desired class." << endl;

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
        goto a10;
    }
}

void Helpy::display_student_schedule(bool& valid) const{
a11:cout << endl << "Please write the code (upXXXXXXXXX) of the desired student." << endl;
    
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
        goto a11;
    }
}

void Helpy::display_student_classes(bool& valid) const{
a12:cout << endl << "Understood. Please write the code (upXXXXXXXXX) of the desired student." << endl;

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
        goto a12;
    }
}

void Helpy::display_all_students() const{
    // ordenação por código ou nome
a13:cout << endl << "How would you like to order the students? (Code/Name)" << endl;
    
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
        goto a13;
    }

    // buscar condição
    int n = 0;

    cout << endl << "Would you like to filter the students by the number of UCs they are in? (Yes/no)" 
         << endl;

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
    }

    bool less = false;
    if (filter){
        cout << endl << "OK. Would you like to see if students have less or more than a number of UCs?"
             << endl;

        getline(cin, line);
        lowercase(line);

        line_.clear();
        line_.str(line);

        while (line_ >> temp){
            if (temp == "less"){
                less = true;
                break;
            }
            else if (temp == "more"){
                break;
            }
        }
        
        line_.clear();

        cout << endl << "OK. Please type the number you want to use for filtering:"
             << endl;

        cin >> n;
    }
        
    // imprimir todos os estudantes
    cout << endl << "These are all the students currently enrolled in LEIC:" << endl;

    for (Student s : all_students){
        if (less && (int) s.get_ucs().size() < n){
            (by_code) ? (cout << s.get_studentCode() << ' ' << s.get_studentName()) :
                        (cout << s.get_studentName() << " (up" << s.get_studentCode() << ')');
            cout << endl;
        }
        else if (!less && (int) s.get_ucs().size() > n){
            (by_code) ? (cout << s.get_studentCode() << ' ' << s.get_studentName()) :
                        (cout << s.get_studentName() << " (up" << s.get_studentCode() << ')');
            cout << endl;
        }
    }
}

void Helpy::display_student_ucs(bool& valid) const{
a15:cout << endl << "Understood. Please write the code (upXXXXXXXXX) of the desired student." << endl;
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
        goto a15;
    }
}

/*-----FUNÇÕES DA FILA-----*/
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
        queuer.pop();
        if(sub.get_type() == "add"){
            add(sub);
        } else if (sub.get_type() == "remove"){
            rem(sub);
        } else {
            change(sub);
        }
    }
}

void Helpy::rem(Request sub){
    bool valid = false;
    if(sub.get_what() == "uc"){
        for(Student& s : all_students){
            if(s.get_studentCode() == sub.get_stupid()){
                valid = true;
                map<string, string> a = s.get_ucs();
                if(a.find(sub.get_name()) != a.end()){
                    auto it = a.find(sub.get_name());
                    s.print_ucs();
                    a.erase(it);
                    s.set_ucs(a);
                    s.print_ucs();
                    string uc_ = sub.get_name();
                    lowercase(uc_,true);
                    //falta remover o estudante da uc
                    cout << "UC-" << uc_ << " has sucessfully been removed from " << sub.get_stupid() << endl;
                } else {
                    string uc_ = sub.get_name();
                    lowercase(uc_,true);
                    cout << "The selected student (" << sub.get_stupid() << ") does not have the selected UC (" << uc_ <<")" << endl;
                    cout << "Aborting Request" << endl;  
                }
            }
        }
    } else if(sub.get_what() == "class"){
        for(Student& s: all_students){
            if (s.get_studentCode() == sub.get_stupid())
            {
                valid = true;
                set<string> cl = s.get_classes();
                if(cl.find(sub.get_name()) != cl.end()){
                  cl.erase(sub.get_name());
                  map<string, string> a = s.get_ucs();
                  for(auto i: a){
                    if(i.second == sub.get_name()){
                        a.erase(i.first); // isto remove a class do estudante
                    }
                }
                int year = sub.get_name()[0] - '0';
                int num = (sub.get_name()[5] - '0') * 10 + (sub.get_name()[6] - '0');
                Class& c = all_classes[(year - 1) * 16 + (num - 1)];
                c.remove_student(s.get_studentName()); // remover o estudante da class
                cout << "The student has been removed from the selected class" << endl;
                } else {
                    string y = sub.get_name();
                    lowercase(y,true);
                    cout << "The selected student (" << sub.get_stupid() << ") is not in the selected class (" << y <<")" << endl;
                    cout << "Aborting Request" << endl;  
                }
            }
            
        }
    }
    if(!valid){
            cout << "The selected student (" << sub.get_stupid() << ") does not exist in this database" << endl;
    }
}

void Helpy::add(Request sub){}

void Helpy::change(Request sub){}

void Helpy::update_schedule(Student& s){
    list<Block> hi;
    for(auto it = s.get_ucs().begin(); it != s.get_ucs().end(); it++){
        for(Block& b : class_blocks[it->second]){
            if (b.get_code() == it->first)
            {
                hi.push_back(b);
            }
        }
    }
    s.set_Schedule(Schedule(hi));

}