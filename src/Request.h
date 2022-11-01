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
    string get_type() const;
    string get_target() const;
    string get_what() const;
    string get_stupid() const;
    string get_name() const;
};


#endif