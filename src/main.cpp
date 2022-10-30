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

    /*-----LER COMANDOS-----*/
    map<string, int> command = {{"display", 1}, {"print", 1}, {"show", 1}, {"request", 2}};
    map<string, int> target = {{"UC", 3}, {"class", 5}, {"student", 7}, {"all", 9}};
    map<string, int> what = {{"schedule", 10}, {"classes", 13}, {"UC", 16}, {"student", 19}}; 

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
        case(17) : {
            cout << endl << "Understood. Please select the desired UC." << endl;

            string uc; cin >> uc;
            
            for (UC u : all_UCs){
                if (u.get_UcCode() == uc){
                    cout << endl << "The UC " << "\033[1m" << uc << 
                    "\033[0m" << " has the following classes:" << endl;

                    u.print_classes();
                    valid = true;
                } 
            }

            if (!valid){
                cout << endl << "I'm sorry, but that UC does not exist." << endl;
            }

            break;
        }
        case(14) : {
            cout << endl << "Understood. Please select the desired UC." << endl;

            string uc; cin >> uc;

            for (UC u : all_UCs){
                if (u.get_UcCode() == uc){
                    cout << endl << "The UC " << "\033[1m" << uc << 
                    "\033[0m" << " has the following schedule:" << endl;

                    u.get_schedule().print();
                    valid = true;
                } 
            }

            if (!valid){
                cout << endl << "I'm sorry, but that UC does not exist." << endl;
            }

            break;
        }
        case(16) : {
            cout << endl << "Understood. Please select the desired class." << endl;

            string classCode; cin >> classCode;

            for (Class c : all_classes){
                if (c.get_classCode() == classCode){
                    cout << endl << "The class " << "\033[1m" << classCode << 
                    "\033[0m" << " has the following schedule:" << endl;

                    c.get_schedule().print();
                    valid = true;
                } 
            }

            if (!valid){
                cout << endl << "I'm sorry, but that class does not exist." << endl;
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
