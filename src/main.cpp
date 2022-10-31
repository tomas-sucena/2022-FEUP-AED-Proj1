#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

#include "UC.h"
#include "Class.h"
#include "Student.h"

using namespace std;

// overloadings
bool operator<(const Student& s1, const Student& s2){
    return (s1.get_studentName() < s2.get_studentName());
}

bool operator<(const Block& b1, const Block& b2){
    if (b1.get_weekday() == b2.get_weekday()){
        return (b1.get_startHour() < b2.get_startHour());
    }
    
    return (Block::week[b1.get_weekday()] < Block::week[b2.get_weekday()]);
}

// função auxiliar usada para tratar dos comandos
void lowercase(string& s){
    for (char& c : s){
        c = tolower(c);
    }
}

int main(){
    /*-----LER FICHEIROS-----*/
    // ler o 1º ficheiro
    ifstream classes_per_uc("../classes_per_uc.csv");

    string line; getline(classes_per_uc, line); // ignorar o cabeçalho

    map<string, set<string>> mappy;
    
    while (getline(classes_per_uc, line)){
        istringstream line_(line);

        string ucCode, classCode;

        // ler o UcCode
        getline(line_, ucCode, ',');

        // ler o ClassCode
        getline(line_, classCode, '\r');

        mappy[ucCode].insert(classCode);
    }

    vector<UC> all_UCs;
    for (auto it = mappy.begin(); it != mappy.end(); it++){
        UC uc(it->first, it->second);

        all_UCs.push_back(uc);
    }

    // ler o 2º ficheiro
    ifstream classes("../classes.csv");

    getline(classes, line); // ignorar o cabeçalho

    map<string, list<Block>> uc_blocks, class_blocks;

    while (getline(classes, line)){
        istringstream line_(line);

        string classCode, ucCode, weekday, 
               startHour, duration, type;

        // ler a ClassCode
        getline(line_, classCode, ',');

        // ler o UcCode
        getline(line_, ucCode, ',');

        // ler o Weekday
        getline(line_, weekday, ',');

        // ler a StartHour
        getline(line_, startHour, ',');

        // ler a Duration
        getline(line_, duration, ',');

        // ler o Type
        getline(line_, type, '\r');

        uc_blocks[ucCode].push_back(Block(classCode, weekday, startHour, duration, type));
        class_blocks[classCode].push_back(Block(ucCode, weekday, startHour, duration, type));
    }

    // atualizar o vetor de UCs
    for (UC& uc : all_UCs){
        uc.add_schedule(Schedule(uc_blocks[uc.get_UcCode()]));
    }

    vector<Class> all_classes;
    for (auto it = class_blocks.begin(); it != class_blocks.end(); it++){
        all_classes.push_back(Class(it->first, Schedule(it->second)));
    }

    // ler o 3º ficheiro
    ifstream students_classes("../students_classes.csv");
    
    getline(students_classes, line); // ignorar o cabeçalho

    map<pair<string, string>, 
        map<string, list<string>>> student_info;

    while (getline(students_classes, line)){
        istringstream line_(line);

        string studentCode, studentName, 
               ucCode, classCode;
        
        // ler o StudentCode
        getline(line_, studentCode,',');
        
        // ler o StudentName
        getline(line_, studentName,',');

        // ler o UcCode
        getline(line_, ucCode,',');

        // ler a ClassCode
        getline(line_, classCode,'\r');

        student_info[{studentCode, studentName}]
                    [classCode].push_back(ucCode);
    }

    set<Student> all_students;
    for (auto info : student_info){
        Student s(info.first.first, info.first.second);
        
        list<Block> blocks;

        // criar o horário do aluno
        for (auto m : info.second){
            int year = (m.first)[0] - '0';
            int num = ((m.first[5] - '0') * 10 + (m.first[6] - '0'));
            
            Class& c = all_classes[15 * (year - 1) + (num - 1)];

            auto it = m.second.begin();
            for (Block& b : c.get_schedule().get_blocks()){
                if (b.get_code() == *it){
                    blocks.push_back(b);
                    it++;
                }

                if (it == m.second.end()){break;}
            }
        }
        
        s.set_UcperClass(info.second);
        s.set_Schedule(Schedule(blocks));

        all_students.insert(s);
    }


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
        case(14) : { // display UC schedule
            cout << endl << "Understood. Please select the desired UC." << endl;

            string uc; cin >> uc;

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

            break;
        }
        case(16) : { // display class schedule
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

            break;
        }
        case(17) : { // display UC classes
            cout << endl << "Understood. Please select the desired UC." << endl;

            string uc; cin >> uc;
            
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

            break;
        }
        case(18) : { // display student schedule
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

            break;
        }
        case(21) : { // display student classes
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
