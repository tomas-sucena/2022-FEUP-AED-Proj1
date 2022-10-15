#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>

#include "UC.h"
#include "Class.h"

using namespace std;

int main(){
    ifstream classes_per_uc("../classes_per_uc.csv");

    string line; getline(classes_per_uc, line);
    
    map<string, vector<Class>> mappy;
    set<Class> all_classes;

    // ler o 1º ficheiro
    while (getline(classes_per_uc, line)){
        istringstream line_(line);

        // ler o código da Uc
        string UcCode, classCode;
        getline(line_, UcCode, ',');

        // ler o código da turma
        getline(line_, classCode, '\r');

        // dar update das turmas que têm a UC
        bool seen = false;
        for (Class c : all_classes){
            if (c.get_classCode() == classCode){
                mappy[UcCode].push_back(c);
                
                seen = true; break;
            }
        }

        if (!seen){
            Class c(classCode);

            all_classes.insert(c);
            mappy[UcCode].push_back(c);
        }
    }

    vector<UC> all_UCs;
    for (auto it = mappy.begin(); it != mappy.end(); it++){
        UC uc(it->first, it->second);

        all_UCs.push_back(uc);
    }

    // teste
    for (UC uc : all_UCs){
        cout << uc.get_UcCode() << endl;
        uc.print_classes();        
    }

}