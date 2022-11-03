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

        // dias da semana
        static map<string, int> week;
    
    public:
        // constructor
        Block(string code, string weekday, string startHour, 
              string duration, string type);


        // methods
        string get_code() const;
        string get_weekday() const;
        float get_startHour() const;
        float get_endHour() const;
        string get_type() const;

        bool operator<(const Block& b) const; // overloading
};

#endif