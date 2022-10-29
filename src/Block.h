#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <string>

using namespace std;

class Block{
    private:
        string code_;
        string weekday_;
        float startHour_;
        float end_;
        string type_;
    
    public:
        // constructor
        Block(string code, string weekday, string startHour, 
              string duration, string type);

        // methods
        float get_startHour();
};

#endif