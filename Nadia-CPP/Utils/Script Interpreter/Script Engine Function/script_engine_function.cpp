//
//  script_engine_function.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 15/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "script_engine_function.hpp"
#include "environment.hpp"
#include "interpreter.hpp"
#include "eval_interpreter.hpp"

Script_Engine_Function::Script_Engine_Function(Stmt::Function_Stmt declaration, Environment closure): declaration(declaration), closure(closure)
{
    
}

any Script_Engine_Function::call(Interpreter& interpreter, vector<shared_ptr<any>>& arguments)
{
    
    Environment environment(const_cast<Environment&>(closure));
    
    for(int i = 0; i < declaration.params.size(); i++)
    {
        environment.define(declaration.params[i]->lexeme, *arguments[i]);
    }
    
    try{
        interpreter.executeBlock(const_cast<vector<shared_ptr<Stmt*>>&>(declaration.body), environment);
    }
    catch(Return returnValue)
    {
        return returnValue.value;
    }
    
    
    return nullptr;
}

any Script_Engine_Function::call(Eval_Interpreter& interpreter, vector<shared_ptr<any>>& arguments)
{
    Environment environment(const_cast<Environment&>(closure));
    
    for(int i = 0; i < declaration.params.size(); i++)
    {
        environment.define(declaration.params[i]->lexeme, *arguments[i]);
    }
    
    try{
        interpreter.executeBlock(const_cast<vector<shared_ptr<Stmt*>>&>(declaration.body), environment);
    }
    catch(Return returnValue)
    {
        return returnValue.value;
    }
    
    
    return nullptr;
}

int Script_Engine_Function::arity()
{
    return static_cast<int>(declaration.params.size());
}

string Script_Engine_Function::toString()
{
    return "<fn "+declaration.name.lexeme+">";
}
