#ifndef REQUEST_H
#define REQUEST_H

#include <string>
using namespace std;

class Request
{
private:
    string type;
    string target;
    string what;
    string stupid;
    string name;

    
public:
    Request(string a, string b, string c, string d, string e);
};


#endif