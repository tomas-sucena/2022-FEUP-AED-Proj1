#include "Helpy.h"
#include <fstream>
#include <sstream>

// função auxiliar usada para tratar dos comandos
void lowercase(string& s, bool uppercase = false){
    for (char& c : s){
        c = (uppercase) ? toupper(c) :
                          tolower(c);
    }
}

Helpy::Helpy(set<Student> students, vector<UC> UCs, vector<Class> classes): 
             all_students(students), all_UCs(UCs), all_classes(classes){}

void Helpy::terminal(){
    /*-----LER COMANDOS-----*/
    map<string, int> command = {{"display", 1}, {"print", 1}, {"show", 1}, {"request", 2}};
    map<string, int> target = {{"uc", 3}, {"class", 5}, {"student", 7}, {"all", 9}};
    map<string, int> what = {{"schedule", 10}, {"classes", 13}, {"uc", 16}, {"students", 19}}; 

    cout << "Hello! How can I be of assistance?" << endl;

b:  string s1, s2, s3; 
    bool valid = false;

    cin >> s1; lowercase(s1);
    if (s1 == "quit" || s1 == "no"){
        goto e;
    }

    cin >> s2 >> s3;
    lowercase(s2); lowercase(s3);

    // processar o comando    
    switch (command[s1] + target[s2] + what[s3]){
        case(14) : {
            display_uc_schedule(valid);

            break;
        }
        case(16) : {
            display_class_schedule(valid);

            break;
        }
        case(17) : {
            display_uc_classes(valid);

            break;
        }
        case(18) : {
            display_student_schedule(valid);

            break;
        }
        case(21) : {
            display_student_classes(valid);

            break;
        }
        case(25) : {
            // ordenação por código ou por nome
            cout << endl << "Would you like to order the students by code (upXXXXXXXXX) or by name?" << endl;
            
            cin.ignore();
             
        c2: string line; getline(cin, line);
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
                goto c2;
            }

            // ordenação ascendente ou descendente
        c3: cout << endl << "And would you like to sort them in ascending or descending order?" << endl;

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
                goto c3;
            }

            display_class_students(valid, (bool) by_code, (bool) descending);

            break;
        }
        case(29) : {
        c1: cout << endl << "Would you like to order the students by code (upXXXXXXXXX) or by name?" << endl;
            
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
                goto c1;
            }

            display_all_students((bool) by_code);

            break;
        }
        default : {
            cout << endl << "Invalid command! Please, type another command." << endl;
            goto b;
        }
    }

    cout << endl << "Anything else?" << endl;
    goto b;

e:  cout << endl << "See you next time!" << endl;
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

void Helpy::display_class_students(bool& valid, bool by_code, bool descending) const{
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

void Helpy::display_all_students(bool by_code) const{
    cout << endl << "Understood. These are all the students currently enrolled in LEIC:" << endl;

    for (Student s : all_students){
        (by_code) ? (cout << s.get_studentCode() << ' ' << s.get_studentName()) :
                    (cout << s.get_studentName() << " (up" << s.get_studentCode() << ')');
        cout << endl;
    }
}
