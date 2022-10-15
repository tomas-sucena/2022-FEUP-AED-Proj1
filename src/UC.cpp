#include "UC.h"

UC::UC(string UcCode, vector<Class> classes) : 
    UcCode_(UcCode), classes_(classes) {}

void UC::print_classes(){
    for (Class anime : classes_){
        cout << anime.get_classCode() << ' ';
    }
}

void UC::remove_class(Class anime){
    for(auto kanna = classes_.begin(); kanna != classes_.end();){
        if (kanna->equals(anime)){
            kanna = classes_.erase(kanna);
        }
        else{
            kanna++;
        }
    }
}

string UC::get_UcCode(){
    return UcCode_;
}