#include "UC.h"

UC::UC(string ucCode, set<string> classes) : 
       ucCode_(ucCode), classes_(classes) {}

UC::UC(string ucCode, set<string> classes, Schedule schedule) :
       ucCode_(ucCode), classes_(classes), schedule_(schedule) {};

void UC::print_classes(){
    for (string anime : classes_){
        cout << anime << endl;
    }
}

string UC::get_UcCode(){
    return ucCode_;
}

void UC::remove_class(string classCode){
    for(auto kanna = classes_.begin(); kanna != classes_.end();){
        if (*kanna == classCode){
            kanna = classes_.erase(kanna);
        }
        else{
            kanna++;
        }
    }
}

void UC::add_schedule(Schedule schedule){
    schedule_ = schedule;
}

Schedule UC::get_schedule(){
    return schedule_;
}