//
//  script_engine_function.hpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 15/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef script_engine_function_hpp
#define script_engine_function_hpp

#include <stdio.h>
#include <vector>

#include "statement.hpp"
#include "script_engine_callable.hpp"
#include "return.hpp"
#include "environment.hpp"

class Script_Engine_Function : public Script_Engine_Callable
{
    const Stmt::Function_Stmt declaration;
    const Environment closure;
public:
    Script_Engine_Function(Stmt::Function_Stmt declaration, Environment closure);
    any call(Interpreter& interpreter, vector<shared_ptr<any>>& arguments) override;
    any call(Eval_Interpreter& interpreter, vector<shared_ptr<any>>& arguments) override;
    int arity() override;
    string toString() override;

};
#endif /* script_engine_function_hpp */
