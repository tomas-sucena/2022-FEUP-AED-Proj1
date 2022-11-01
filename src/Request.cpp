#include "Request.h"

Request::Request(string a, string b, string c, string d, string e) : type(a), target(b), what(c), stupid(d), name(e) {};

string Request::get_type() const{
    return type;
}
string Request::get_target() const{
    return target;
}
string Request::get_what() const{
    return what;
}
string Request::get_stupid() const{
    return stupid;
}
string Request::get_name() const{
    return name;
}