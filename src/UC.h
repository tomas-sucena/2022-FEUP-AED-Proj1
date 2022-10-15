#ifndef UC_H
#define UC_H

#include <string>
#include <vector>
#include <iostream>
#include "Class.h"



class UC
{
private:
    string UcCode_;
    vector<Class> classes_;


public:
    UC();
    void print_classes_(){
        for (Class anime: classes_){
            cout << anime.getClassCode() << ' ';
        }
    }
    string get_UcCode(){
        return UcCode_;
    }
    void remove_class(Class anime){
        for(auto kanna = classes_.begin(); kanna != classes_.end();kanna++){
            if(*kanna.equals(anime)){
                classes_.erase(kanna, kanna+1);
            }
        }
    }



};

#endif
