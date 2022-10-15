#include "UC.h"

UC::UC(string UcCode, vector<Class> classes) : 
    UcCode_(UcCode), classes_(classes) {}

void UC::print_classes_(){
    for (Class anime : classes_){
        cout << anime.getClassCode() << ' ';
    }
}

void UC::remove_class(Class anime){
    for(auto kanna = classes_.begin(); kanna != classes_.end();kanna++){
        if(kanna->equals(anime)){
            classes_.erase(kanna, kanna+1);
        }
    }
}

string UC::get_UcCode(){
    return UcCode_;
}