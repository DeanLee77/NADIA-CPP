//
//  script_engine_callable.hpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 12/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef script_engine_callable_hpp
#define script_engine_callable_hpp

#include <stdio.h>
#include <any>
#include <vector>
#include <memory>

using namespace std;

class Interpreter;
class Eval_Interpreter;

class Script_Engine_Callable 
{
public:
    virtual int arity() = 0;
    virtual any call(Eval_Interpreter& interpreter, vector<shared_ptr<any>>& arguments) = 0;
    virtual any call(Interpreter& interpreter, vector<shared_ptr<any>>& arguments) = 0;
    virtual string toString() = 0;
};
#endif /* script_engine_callable_hpp */
