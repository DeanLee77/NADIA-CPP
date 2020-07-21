//
//  string_handler.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 5/5/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "string_handler.hpp"

string String_Handler::stringTrim(string& str)
{
    string whitespace = " \n\r\t\f\v";
    str.erase(0, str.find_first_not_of(whitespace));
    str.erase(str.find_last_not_of(whitespace)+1);
    return str;
}

vector<string> String_Handler::stringSplit(string &str, char& delimiter)
{
    vector<string> tokens;
    string token;
    
    stringstream tokenStream(str);
    while(getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    
    return tokens;
}

