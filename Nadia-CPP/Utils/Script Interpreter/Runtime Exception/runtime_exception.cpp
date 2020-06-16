//
//  runtime_exception.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 15/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "runtime_exception.hpp"

Interpreter_Runtime_Exception::Interpreter_Runtime_Exception(string message) : message(message)
{
    
}

Interpreter_Runtime_Exception::Interpreter_Runtime_Exception() :message("")
{
    
}
