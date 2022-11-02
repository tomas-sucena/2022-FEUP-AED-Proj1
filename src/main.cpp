#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <set>

#include "UC.h"
#include "Class.h"
#include "Student.h"
#include "Helpy.h"

using namespace std;

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
        map<string, string>> student_info;

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
                    [ucCode] = classCode;

        // adicionar estudante à UC
        int dec = ucCode[6] - '0',
            unit = ucCode[7] - '0';

        UC& u = all_UCs[dec * 5 + (unit - 1)];

        u.add_student(stoi(studentCode), studentName);
    }

    set<Student> all_students;
    for (auto info : student_info){
        string studentCode = info.first.first;
        string studentName = info.first.second;

        Student s(studentCode, studentName);

        // criar o horário do estudante
        list<Block> blocks;

        for (pair<string, string> p : info.second){
            string ucCode = p.first,
                   classCode = p.second;

            s.add_uc(ucCode, classCode);
            s.add_class(classCode);

            // adicionar estudante à turma
            int year = classCode[0] - '0';
            int num = (classCode[5] - '0') * 10 + (classCode[6] - '0');

            Class& c = all_classes[(year - 1) * 16 + (num - 1)];

            c.add_student(stoi(studentCode), studentName);

            for (Block& b : c.get_schedule().get_blocks()){
                if (b.get_code() == ucCode){
                    blocks.push_back(b);
                    break;
                }
            }
        }

        s.set_Schedule(Schedule(blocks));

        all_students.insert(s);
    }

    // handling terminal things
    Helpy hi = Helpy(all_students, all_UCs, all_classes);
    hi.terminal();
}
