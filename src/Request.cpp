#include "Request.h"

/**
 * @brief Construct a new Request:: Request object
 * 
 * @param a 
 * @param b 
 * @param c 
 * @param e
 */
Request::Request(string a, string b, string c, string e) : type(a), target(b), student_(c), cl_(e) {};

/**
 * @brief Construct a new Request:: Request object
 * 
 * @param a 
 * @param b 
 * @param c 
 * @param d 
 * @param e 
 */
Request::Request(string a, string b, string c, string d, string e) : type(a), target(b), student_(c), uc_(d), cl_(e) {};

/**
 * @brief returns the type of the request
 * @return string 
 */
string Request::get_type() const{
    return type;
}

/**
 * @brief returns the target of the request
 * @return string 
 */
string Request::get_target() const{
    return target;
}

/**
 * @brief returns the student 
 * @return string 
 */
string Request::get_student() const{
    return student_;
}

/**
 * @brief returns the UC
 * @return string 
 */
string Request::get_uc() const{
    return uc_;
}

/**
 * @brief returns the class
 * @return string 
 */
string Request::get_class() const{
    return cl_;
}