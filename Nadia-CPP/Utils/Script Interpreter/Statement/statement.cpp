//
//  statement.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 4/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "statement.hpp"

Stmt::Block_Stmt:: Block_Stmt(vector<shared_ptr<Stmt*>>& statements): statements(statements)
{
    
}

Stmt::Expression_Stmt::Expression_Stmt(Expr* expression) : expression(expression)
{
    
}

Stmt::Expression_Stmt::~Expression_Stmt()
{
    delete expression;
}
Stmt::Function_Stmt::Function_Stmt(Interpreter_Token& name, vector<shared_ptr<Interpreter_Token>>& params, vector<shared_ptr<Stmt*>>& body): name(name), params(params), body(body)
{
    
}

Stmt::If_Stmt::If_Stmt(Expr* condition, Stmt* thenBranch, Stmt* elseBranch): condition(condition), thenBranch(thenBranch), elseBranch(elseBranch)
{
    
}

Stmt::If_Stmt::~If_Stmt()
{
    delete condition;
    delete thenBranch;
    delete elseBranch;
}

Stmt::Print_Stmt::Print_Stmt(Expr* expression): expression(expression)
{
    
}

Stmt::Print_Stmt::~Print_Stmt()
{
    delete expression;
}

Stmt::Return_Stmt::Return_Stmt(Interpreter_Token& keyword, Expr* value): keyword(keyword), value(value)
{
    
}

Stmt::Return_Stmt::~Return_Stmt()
{
    delete value;
}

Stmt::Let_Stmt::Let_Stmt(Interpreter_Token& name, Expr* initializer): name(name), initializer(initializer)
{
    
}

Stmt::Let_Stmt::~Let_Stmt()
{
    delete initializer;
}

Stmt::Var_Stmt::Var_Stmt(Interpreter_Token& name, Expr* initializer): name(name), initializer(initializer)
{
    
}

Stmt::Var_Stmt::~Var_Stmt()
{
    delete initializer;
}

Stmt::While_Stmt::While_Stmt(Expr* condition, Stmt* body): condition(condition), body(body)
{
    
}

Stmt::While_Stmt::~While_Stmt()
{
    delete condition;
    delete body;
}


