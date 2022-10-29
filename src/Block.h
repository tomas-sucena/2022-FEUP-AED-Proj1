#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <string>

using namespace std;

class Block{
    private:
        string classCode_;
        string weekday_;
        float start_;
        float end_;
        string type_;
    
    public:
        // constructor
        Block(string classCode, string weekday, string start, 
              string duration, string type);
};

#endif