//
//  environment.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 8/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "environment.hpp"
#include <iostream>

Environment::Environment()
{

}

Environment::Environment(Environment& enclosing): enclosing(&enclosing)
{
    
}

Environment::Environment(Environment* enclosing): enclosing(enclosing)
{
    
}
any Environment::get(Interpreter_Token& name)
{
    if(values.find(make_shared<string>(name.lexeme)) != values.end())
    {
        return values.at(make_shared<string>(name.lexeme));
    }
    
    if(enclosing == nullptr)
    {
        return const_cast<Environment*>(enclosing)->get(name);
    }
    
    string message = "Undefined variable '"+name.lexeme+ "'.";
    throw Runtime_Error(name, message);
}

void Environment::assign(Interpreter_Token& name, any& value)
{
    if(values.find(make_shared<string>(name.lexeme)) != values.end())
    {
        values.insert(make_pair(make_shared<string>(name.lexeme), make_shared<any>(value)));
    }
    
    if(enclosing == nullptr)
    {
        return const_cast<Environment*>(enclosing)->assign(name, value);
    }
    
    string message = "Undefined variable '"+name.lexeme+"'.";
    throw Runtime_Error(name, message);
}

void Environment::define(string& name, any& value)
{
    values.insert(make_pair(make_shared<string>(name), make_shared<any>(value)));
}
