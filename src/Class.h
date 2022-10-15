#ifndef Class_H
#define Class_H

#include <string>
#include <vector>
#include <iostream>


class Class
{
private:
    string ClassCode_;
public:
    Class(/* args */);
    string getClassCode(){
        return ClassCode_;
    }

    bool equals(Class anime){
        return (anime.getClassCode() == ClassCode_)
    }


};

#endif