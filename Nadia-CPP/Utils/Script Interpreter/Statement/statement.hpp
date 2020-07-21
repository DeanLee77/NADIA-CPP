//
//  statement.hpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 4/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef statement_hpp
#define statement_hpp

#include <stdio.h>
#include <vector>
#include <memory>

#include "expression.hpp"
using namespace std;
class Stmt
{
public:
    virtual ~Stmt(){ };
    
    template<typename T>
    class Visitor;
    
    class Block_Stmt;
    class Expression_Stmt;
    class Function_Stmt;
    class If_Stmt;
    class Print_Stmt;
    class Return_Stmt;
    class Let_Stmt;
    class Var_Stmt;
    class While_Stmt;
    
    
    template<typename T>
    T accept(Visitor<T>* visitor);
};
template<typename T>
class Stmt::Visitor
{
public:
    virtual T visitBlockStmt(Stmt::Block_Stmt* stmt) =0;
    virtual T visitExpressionStmt(Stmt::Expression_Stmt* stmt) =0;
    virtual T visitFunctionStmt(Stmt::Function_Stmt* stmt) =0;
    virtual T visitIfStmt(Stmt::If_Stmt* stmt) =0;
    virtual T visitPrintStmt(Stmt::Print_Stmt* stmt) =0;
    virtual T visitReturnStmt(Stmt::Return_Stmt* stmt) =0;
    virtual T visitLetStmt(Stmt::Let_Stmt* stmt) =0;
    virtual T visitVarStmt(Stmt::Var_Stmt* stmt) =0;
    virtual T visitWhileStmt(Stmt::While_Stmt* stmt) =0;
};

class Stmt::Block_Stmt : public Stmt
{
public:
    Block_Stmt(vector<shared_ptr<Stmt*>>& statements);
    const vector<shared_ptr<Stmt*>> statements;
    
    template<typename T>
    T accept(Stmt::Visitor<T>* visitor);
    
};

template<typename T>
T Stmt::Block_Stmt::accept(Stmt::Visitor<T>* visitor)
{
    return visitor->visitBlockStmt(this);
}

class Stmt::Expression_Stmt : public Stmt
{
public:
    const Expr* expression;
    Expression_Stmt(Expr* expression);
    ~Expression_Stmt();
    template<typename T>
    T accept(Stmt::Visitor<T>* visitor);
};

template<typename T>
T Stmt::Expression_Stmt::accept(Stmt::Visitor<T>* visitor)
{
    return visitor->visitExpressionStmt(this);
}

class Stmt::Function_Stmt : public Stmt
{
public:
    const Interpreter_Token name;
    const vector<shared_ptr<Interpreter_Token>> params;
    const vector<shared_ptr<Stmt*>> body;
    
    Function_Stmt(Interpreter_Token& name, vector<shared_ptr<Interpreter_Token>>& params, vector<shared_ptr<Stmt*>>& body);
    
    template<typename T>
    T accept(Stmt::Visitor<T>* visitor);
    
};

template<typename T>
T Stmt::Function_Stmt::accept(Stmt::Visitor<T>* visitor)
{
    return visitor->visitFunctionStmt(this);
}

class Stmt::If_Stmt : public Stmt
{
public:
    const Expr* condition;
    const Stmt* thenBranch;
    const Stmt* elseBranch;
    If_Stmt(Expr* condition, Stmt* thenBranch, Stmt* elseBranch);
    ~If_Stmt();
    template<typename T>
    T accept(Stmt::Visitor<T>* visitor);
};

template<typename T>
T Stmt::If_Stmt::accept(Stmt::Visitor<T>* visitor)
{
    return visitor->visitIfStmt(this);
}

class Stmt::Print_Stmt : public Stmt
{
public:
    const Expr* expression;
    Print_Stmt(Expr* expression);
    ~Print_Stmt();
    template<typename T>
    T accept(Stmt::Visitor<T>* visitor);
};

template<typename T>
T Stmt::Print_Stmt::accept(Stmt::Visitor<T>* visitor)
{
    return visitor->visitPrintStmt(this);
}

class Stmt::Return_Stmt : public Stmt
{
public:
    const Interpreter_Token keyword;
    const Expr* value;
    Return_Stmt(Interpreter_Token& keyword, Expr* value);
    ~Return_Stmt();
    template<typename T>
    T accept(Stmt::Visitor<T>* visitor);
};

template<typename T>
T Stmt::Return_Stmt::accept(Stmt::Visitor<T>* visitor)
{
    return visitor->visitReturnStmt(this);
}

class Stmt::Let_Stmt : public Stmt
{
public:
    const Interpreter_Token name;
    const Expr* initializer;
    
    Let_Stmt(Interpreter_Token& name, Expr* initializer);
    ~Let_Stmt();
    template<typename T>
    T accept(Stmt::Visitor<T>* visitor);
};

template<typename T>
T Stmt::Let_Stmt::accept(Stmt::Visitor<T>* visitor)
{
    return visitor->visitLetStmt(this);
}

class Stmt::Var_Stmt : public Stmt
{
public:
    const Interpreter_Token name;
    const Expr* initializer;
    
    Var_Stmt(Interpreter_Token& name, Expr* initializer);
    ~Var_Stmt();
    template<typename T>
    T accept(Stmt::Visitor<T>* visitor);
};

template<typename T>
T Stmt::Var_Stmt::accept(Stmt::Visitor<T>* visitor)
{
    return visitor->visitVarStmt(this);
}

class Stmt::While_Stmt : public Stmt
{
public:
    const Expr* condition;
    const Stmt* body;
    
    While_Stmt(Expr* condition, Stmt* body);
    ~While_Stmt();
    template<typename T>
    T accept(Stmt::Visitor<T>* visitor);
};

template<typename T>
T Stmt::While_Stmt::accept(Stmt::Visitor<T>* visitor)
{
    return visitor->visitWhileStmt(this);
}

template<typename T>
T Stmt::accept(Stmt::Visitor<T>* visitor)
{
    const type_info& className = typeid(*this);
    
    if(className == typeid(Stmt::Block_Stmt))
    {
        return const_cast<Stmt::Block_Stmt*>(dynamic_cast<Stmt::Block_Stmt*>(this))->accept(visitor);
    }
    else if(className == typeid(Stmt::Expression_Stmt))
    {
        return dynamic_cast<Stmt::Expression_Stmt*>(this)->accept(visitor);
    }
    else if(className == typeid(Stmt::Function_Stmt))
    {
        return dynamic_cast<Stmt::Function_Stmt*>(this)->accept(visitor);
    }
    else if(className ==typeid(Stmt::If_Stmt))
    {
        return dynamic_cast<Stmt::If_Stmt*>(this)->accept(visitor);
    }
    else if(className ==typeid(Stmt::Print_Stmt))
    {
        return dynamic_cast<Stmt::Print_Stmt*>(this)->accept(visitor);
    }
    else if(className ==typeid(Stmt::Return_Stmt))
    {
        return dynamic_cast<Stmt::Return_Stmt*>(this)->accept(visitor);
    }
    else if(className ==typeid(Stmt::Let_Stmt))
    {
        return dynamic_cast<Stmt::Let_Stmt*>(this)->accept(visitor);
    }
    else if(className ==typeid(Stmt::Var_Stmt))
    {
       return dynamic_cast<Stmt::Var_Stmt*>(this)->accept(visitor);
    }
    else if(className ==typeid(Stmt::While_Stmt))
    {
      return dynamic_cast<Stmt::While_Stmt*>(this)->accept(visitor);
    }
    return *static_cast<T*>(nullptr);
}

#endif /* statement_hpp */
