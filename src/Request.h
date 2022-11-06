#ifndef REQUEST_H
#define REQUEST_H

#include <string>
using namespace std;

class Request
{
private:
    string type;
    string target;
    string student_;
    string uc_;
    string cl_;

public:
    Request(string a, string b, string c, string e);
    Request(string a, string b, string c, string d, string e);
    string get_type() const;
    string get_target() const;
    string get_student() const;
    string get_uc() const;
    string get_class() const;
};

#endif