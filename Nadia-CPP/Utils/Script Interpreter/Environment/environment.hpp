//
//  environment.hpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 8/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef environment_hpp
#define environment_hpp

#include <stdio.h>
#include <string>
#include <map>
#include <any>

#include "interpreter_token.hpp"
#include "interpreter_runtime_error.hpp"
using namespace std;

class Environment
{
    map<shared_ptr<string>, shared_ptr<any>> values;
    
public:
    const Environment *enclosing;
    Environment();
    Environment(Environment& enclosing);
    Environment(Environment* enclosing);
    any get(Interpreter_Token& name);
    void assign(Interpreter_Token& name, any& value);
    void define(string& name, any& value);
};
#endif /* environment_hpp */
