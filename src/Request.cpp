#include "Request.h"

/**
 * @brief Construct a new Request:: Request object
 * @param a type of the request
 * @param b target of the request
 * @param c code of the student
 * @param d code of the target of the request
 */
Request::Request(string a, string b, string c, string e) : type_(a), target_(b), student_(c), cl_(e) {};

/**
 * @brief Construct a new Request:: Request object
 * @param a type of the request
 * @param b target of the request
 * @param c code of the student
 * @param d code of the UC
 * @param e code of the class
 */
Request::Request(string a, string b, string c, string d, string e) : type_(a), target_(b), student_(c), uc_(d), cl_(e) {};

/**
 * @brief returns the type of the request
 * @return string with the type of the request
 */
string Request::get_type() const{
    return type_;
}

/**
 * @brief returns the target of the request
 * @return string with the target of the request
 */
string Request::get_target() const{
    return target_;
}

/**
 * @brief returns the code of the student
 * @return string with the code of the student
 */
string Request::get_student() const{
    return student_;
}

/**
 * @brief returns the code of the UC
 * @return string with the code of the UC
 */
string Request::get_uc() const{
    return uc_;
}

/**
 * @brief returns the code of the class
 * @return string with the code of the class
 */
string Request::get_class() const{
    return cl_;
}