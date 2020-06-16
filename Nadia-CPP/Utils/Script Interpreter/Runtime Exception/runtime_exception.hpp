//
//  runtime_exception.hpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 15/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef runtime_exception_hpp
#define runtime_exception_hpp

#include <stdio.h>
#include <exception>
#include <string>

using namespace std;

class Interpreter_Runtime_Exception : public exception
{
    const char* what() const throw()
    {
        return message.c_str();
    }
protected:
    const string message;
    
public:
    Interpreter_Runtime_Exception(string message);
    Interpreter_Runtime_Exception();
    virtual ~Interpreter_Runtime_Exception(){ };
    
};
#endif /* runtime_exception_hpp */
