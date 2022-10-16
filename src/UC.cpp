#include "UC.h"

UC::UC(string UcCode, set<string> classes) : 
    UcCode_(UcCode), classes_(classes) {}

void UC::print_classes(){
    for (string anime : classes_){
        cout << anime << endl;
    }
}

void UC::remove_class(string anime){
    for(auto kanna = classes_.begin(); kanna != classes_.end();){
        if (*kanna == anime){
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