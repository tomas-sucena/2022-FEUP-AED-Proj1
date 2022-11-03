#include "Request.h"

Request::Request(string a, string b, string c, string d) : type(a), target(b), student_(c), uc_(d) {};

Request::Request(string a, string b, string c, string d, string e) : type(a), target(b), student_(c), uc_(d), cl_(e) {};

string Request::get_type() const{
    return type;
}
string Request::get_target() const{
    return target;
}
string Request::get_student() const{
    return student_;
}
string Request::get_uc() const{
    return uc_;
}
string Request::get_class() const{
    return cl_;
}