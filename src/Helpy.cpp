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
    map<string, int> what = {{"schedule", 10}, {"classes", 13}, {"uc", 16}, {"student", 19}}; 

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
