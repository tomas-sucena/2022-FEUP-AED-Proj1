#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

class Block{
    private:
        string code_;
        string weekday_;
        float startHour_;
        float endHour_;
        string type_;
    
    public:
        // constructor
        Block(string code, string weekday, string startHour, 
              string duration, string type);

        // methods
        string get_code();
        string get_weekday();
        float get_startHour();
        float get_endHour();
        string get_type();
        
        bool operator<(Block b);        
};

#endif