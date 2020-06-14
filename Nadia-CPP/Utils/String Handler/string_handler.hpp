//
//  string_handler.hpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 5/5/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef string_handler_hpp
#define string_handler_hpp

#include <string>
#include <vector>
#include <sstream>

using namespace std;
class String_Handler
{
public:
    static string stringTrim(string& str);
    static vector<string> stringSplit(string &str, char& delimiter);
    template<typename T>
    static string toString(T obj);
};

/*
 Please have a look at the following site: https://www.tutorialspoint.com/Why-can-Cplusplus-templates-only-be-implemented-in-the-header-file
 this site explains why template implementation needs to be placed in a header file.
 */
template<typename T>
string String_Handler::toString(T obj)
{
    ostringstream oss;
    if(typeid(obj) == typeid(bool))
    {
        oss << boolalpha << obj;
    }
    else{
        oss << obj;
    }
    
    return oss.str();
}

#endif /* string_handler_hpp */
