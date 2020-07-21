//
//  expression.hpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 9/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef expression_hpp
#define expression_hpp

#include <stdio.h>
#include <typeinfo>
#include <any>
#include <vector>
#include <string>
#include "interpreter_token.hpp"

using namespace std;
//typedef variant<string, int, double, float, bool, char> literVariant;

class Expr
{
public:
    Expr(){ };
    virtual ~Expr() { };
    template <typename T>
    class Visitor;
    
    class Assign_Expr;
    class Binary_Expr;
    class Call_Expr;
    class Grouping_Expr;
    class Literal_Expr;
    class Logical_Expr;
    class Unary_Expr;
    class Variable_Expr;
    
    template<typename T>
    T accept(Expr::Visitor<T>* visitor);
};

template <typename T>
class Expr::Visitor
{
public:
    virtual T visitAssignExpr(Expr::Assign_Expr* assign) = 0;
    virtual T visitBinaryExpr(Expr::Binary_Expr* binary) = 0;
    virtual T visitCallExpr(Expr::Call_Expr* expr) = 0;
    virtual T visitGroupingExpr(Expr::Grouping_Expr* group) = 0;
    virtual T visitUnaryExpr(Expr::Unary_Expr* unary) = 0;
    virtual T visitLogicalExpr(Expr::Logical_Expr* logical) = 0;
    virtual T visitLiteralExpr(Expr::Literal_Expr* literal) = 0;
    virtual T visitVariableExpr(Expr::Variable_Expr* var) = 0;
     
};

class Expr::Assign_Expr : public Expr
{
public:
    const Interpreter_Token name;
    const Expr* value;
    Assign_Expr(Interpreter_Token& name, Expr* value);
    ~Assign_Expr();
    template<typename T>
    T accept(Expr::Visitor<T>* visitor);
    
};

class Expr::Binary_Expr : public Expr
{
public:
    const Expr* left;
    const Interpreter_Token operatorToken;
    const Expr* right;
    Binary_Expr(Expr* inputLeft, Interpreter_Token& inputOperatorToken, Expr* inputRight);
    ~Binary_Expr();
    template<typename T>
    T accept(Expr::Visitor<T>* visitor);
};

class Expr::Call_Expr : public Expr
{
public:
    const Expr* callee;
    const Interpreter_Token paren;
    const vector<shared_ptr<Expr>> arguments;
    Call_Expr(Expr* callee, Interpreter_Token& paren, vector<shared_ptr<Expr>> arguments);
    ~Call_Expr();
    template<typename T>
    T accept(Expr::Visitor<T>* visitor);
};

class Expr::Grouping_Expr : public Expr
{
public:
    const Expr* expression;
    Grouping_Expr(Expr* inputExpression);
    ~Grouping_Expr();
    template<typename T>
    T accept(Expr::Visitor<T>* visitor);
};

class Expr::Literal_Expr: public Expr
{
public:
    const any literal;
    Literal_Expr(any inputLiteral);
        
    template<typename T>
    T accept(Expr::Visitor<T>* visitor);
};

class Expr::Logical_Expr : public Expr
{
public:
    const Expr* left;
    const Interpreter_Token operatorToken;
    const Expr* right;
    
    Logical_Expr(Expr* left, Interpreter_Token& operatorToken, Expr* right);
    ~Logical_Expr();
    template<typename T>
    T accept(Expr::Visitor<T>* visitor);
};

class Expr::Unary_Expr : public Expr
{
public:
    const Interpreter_Token operatorToken;
    const Expr* right;
    Unary_Expr(Interpreter_Token& inputOperatorToken, Expr* inputRight);
    ~Unary_Expr();
    template<typename T>
    T accept(Expr::Visitor<T>* visitor);
};

class Expr::Variable_Expr: public Expr
{
public:
    const Interpreter_Token name;
    Variable_Expr(Interpreter_Token& name);
    
    template<typename T>
    T accept(Expr::Visitor<T>* visitor);
};

template<typename T>
T Expr::accept(Expr::Visitor<T>* visitor)
{
    const type_info& className = typeid(*this);
    
    if(className == typeid(Expr::Binary_Expr))
    {
        return const_cast<Expr::Binary_Expr*>(dynamic_cast<Expr::Binary_Expr*>(this))->accept(visitor);
    }
    else if(className == typeid(Expr::Grouping_Expr))
    {
        return dynamic_cast<Expr::Grouping_Expr*>(this)->accept(visitor);
    }
    else if(className == typeid(Expr::Literal_Expr))
    {
        return dynamic_cast<Expr::Literal_Expr*>(this)->accept(visitor);
    }
    else if(className ==typeid(Expr::Unary_Expr))
    {
        return dynamic_cast<Expr::Unary_Expr*>(this)->accept(visitor);
    }
    
    return *static_cast<T*>(nullptr);
}

template<typename T>
T Expr::Assign_Expr::accept(Expr::Visitor<T>* visitor)
{
    return visitor->visitAssignExpr(this);
}

template <typename T>
T Expr::Binary_Expr::accept(Expr::Visitor<T>*visitor)
{
    return visitor->visitBinaryExpr(this);
}

template<typename T>
T Expr::Call_Expr::accept(Expr::Visitor<T>* visitor)
{
    return visitor->visitCallExpr(this);
}

template <typename T>
T Expr::Grouping_Expr::accept(Expr::Visitor<T>* visitor)
{
    return visitor->visitGroupingExpr(this);
}

template <typename T>
T Expr::Literal_Expr::accept(Expr::Visitor<T>* visitor)
{
    return visitor->visitLiteralExpr(this);
}

template<typename T>
T Expr::Logical_Expr::accept(Expr::Visitor<T>* visitor)
{
    return visitor->visitLogicalExpr(this);
}

template <typename T>
T Expr::Unary_Expr::accept(Expr::Visitor<T>* visitor)
{
    return visitor->visitUnaryExpr(this);
}

template<typename T>
T Expr::Variable_Expr::accept(Expr::Visitor<T>* visitor)
{
    return visitor->visitVariableExpr(this);
}

#endif /* expression_hpp */
