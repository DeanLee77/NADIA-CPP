//
//  runtime_error.hpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 3/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef interpreter_runtime_error_hpp
#define interpreter_runtime_error_hpp

#include <stdio.h>
#include <stdexcept>
#include "interpreter_token.hpp"
using namespace std;

class Runtime_Error : public runtime_error
{
public:
    const Interpreter_Token token;
    Runtime_Error(Interpreter_Token& token, string& message);
    string getMessage();
};
#endif /* interpreter_runtime_error_hpp */
