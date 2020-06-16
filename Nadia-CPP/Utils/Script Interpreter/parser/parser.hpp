//
//  parser.hpp
//  Nadia-CPP
//
//  Created by Dean Lee on 10/3/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef parser_hpp
#define parser_hpp

#include <iostream>
#include <stdio.h>
#include <vector>
#include <optional>

#include "interpreter_token.hpp"
#include "expression.hpp"
#include "statement.hpp"
using namespace std;

class Script_Engine;

class Parser
{
    vector<shared_ptr<Interpreter_Token>> tokens;
    int current  = 0;
    Expr* expression();
    Stmt* declaration();
    Stmt* statement();
    Stmt* forStatement();
    Stmt* ifStatement();
    Stmt* printStatement();
    Stmt* returnStatement();
    Stmt* expressionStatement();
    Stmt::Function_Stmt* function(string& kind);
    vector<shared_ptr<Stmt*>> block();
    Expr* assignment();
    Expr* logicalOr();
    Expr* logicalAnd();
    Stmt* varDeclaration();
    Stmt* whileStatement();
    Expr* equality();
    
    template<typename T>
    bool match(T arg);
    template<typename T, typename ...Ts>
    bool match(T first, Ts... args);
    
    bool check(Token_Type& type);
    Interpreter_Token advance();
    Interpreter_Token previous();
    Interpreter_Token peek();
    bool isAtEnd();
    Expr* comparison();
    Expr* addition();
    Expr* multiplication();
    Expr* unary();
    Expr* finishCall(Expr* callee);
    Expr* call();
    Expr* primary();
    Interpreter_Token consume(Token_Type& type, string& message);
    class ParseError;
    ParseError error(Interpreter_Token& token, string& message);
    void synchronize();
    
public:
    Parser(vector<shared_ptr<Interpreter_Token>> inputTokens);
    vector<shared_ptr<Stmt*>> parse();
};

template<>
inline bool Parser::match<Token_Type>(Token_Type arg)
{
    if(check(arg))
    {
        advance();
        return true;
    }
    return false;
};

template<typename T, typename ...Ts>
bool Parser::match(T first, Ts... args)
{
    return match(first) || match(args...);
};

class Parser::ParseError : public runtime_error
{
public:
    ParseError(): runtime_error("runtime error"){}
    ParseError(string message): runtime_error(message){}
};

#endif /* parser_hpp */
