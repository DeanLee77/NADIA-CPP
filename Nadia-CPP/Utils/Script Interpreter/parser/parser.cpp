//
//  parser.cpp
//  Nadia-CPP
//
//  Created by Dean Lee on 10/3/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "parser.hpp"
#include "script_engine.hpp"

Parser::Parser(vector<shared_ptr<Interpreter_Token>> inputTokens) :tokens(inputTokens)
{
    
}

Expr* Parser::expression()
{
    return assignment();
}

Stmt* Parser::declaration()
{
    try{
        if(match(Token_Type::FUN))
        {
            string kind = "function";
            return function(kind);
        }
        if(match(Token_Type::VAR))
        {
            return varDeclaration();
        }
        return statement();
    }
    catch(ParseError error){
        synchronize();
        return new Stmt();
    }
}
Stmt* Parser::statement()
{
    if(match(Token_Type::FOR))
    {
        return forStatement();
    }
    
    if(match(Token_Type::IF))
    {
        return ifStatement();
    }
    
    if(match(Token_Type::PRINT))
    {
        return printStatement();
    }
    
    if(match(Token_Type::RETURN))
    {
        return returnStatement();
    }
    
    if(match(Token_Type::WHILE))
    {
        return whileStatement();
    }
    
    if(match(Token_Type::LEFT_BRACE))
    {
        vector<shared_ptr<Stmt*>> statements = block();
        return new Stmt::Block_Stmt(statements);
    }
    
    return expressionStatement();
}

Stmt* Parser::forStatement()
{
    Token_Type tokenType = Token_Type::LEFT_PAREN;
    string message = "Expect '(' after 'for'.";
    consume(tokenType, message);
    
    optional<Stmt*> initializer;
    
    if(match(Token_Type::SEMICOLON))
    {
        initializer = nullopt;
    }
    else if(match(Token_Type::VAR))
    {
        initializer = varDeclaration();
    }
    else
    {
        initializer = expressionStatement();
    }
    
    optional<Expr*> condition;
    
    tokenType = Token_Type::SEMICOLON;
    if(!check(tokenType))
    {
        condition = expression();
    }
    
    
    message = "Expect ':' after look condition.";
    consume(tokenType, message);
    
    optional<Expr*> increment;
    tokenType = Token_Type::RIGHT_PAREN;
    if(!check(tokenType))
    {
        increment = expression();
    }
    
    message = "Expect ')' after for clauses.";
    consume(tokenType, message);
    
    Stmt* body = statement();
    
    if(increment.has_value())
    {
        vector<shared_ptr<Stmt*>> blockList = {make_shared<Stmt*>(body), make_shared<Stmt*>(new Stmt::Expression_Stmt(increment.value()))};
        body = new Stmt::Block_Stmt(blockList);
    }
    
    if(!condition.has_value())
    {
        bool literalTrue = true;
        condition = new Expr::Literal_Expr(literalTrue);
    }

    body = new Stmt::While_Stmt(condition.value(), body);
    
    if(initializer.has_value())
    {
        vector<shared_ptr<Stmt*>> blockList = {make_shared<Stmt*>(initializer.value()), make_shared<Stmt*>(body)};
        body = new Stmt::Block_Stmt(blockList);
    }

    return body;
}

Stmt* Parser::ifStatement()
{
    Token_Type tokenType = Token_Type::LEFT_PAREN;
    string message = "Expect '(' after 'if'.";
    consume(tokenType, message);
    
    Expr* condition = expression();
    tokenType = Token_Type::RIGHT_PAREN;
    message = "Expect ')' after if condition.";
    consume(tokenType, message);
    
    Stmt* thenBranch = statement();
    Stmt* elseBranch = nullptr;
    
    if(match(Token_Type::ELSE))
    {
        elseBranch = statement();
    }
    
    return new Stmt::If_Stmt(condition, thenBranch, elseBranch);
}

Stmt* Parser::printStatement()
{
    Expr* value = expression();
    string message = "Expect ';' after value.";
    Token_Type tokenType = Token_Type::SEMICOLON;
    consume(tokenType, message);
    return new Stmt::Print_Stmt(value);
}

Stmt* Parser::returnStatement()
{
    Interpreter_Token keyword = previous();
    Expr* value = nullptr;
    Token_Type tokenType = Token_Type::SEMICOLON;
    if(!check(tokenType))
    {
        value = expression();
    }
    string message = "Expect ';' after return value.";
    consume(tokenType, message);
    return new Stmt::Return_Stmt(keyword, value);
}

Stmt* Parser::varDeclaration()
{
    Token_Type tokenType = Token_Type::IDENTIFIER;
    string message = "Expect variable name";
    Interpreter_Token name = consume(tokenType, message);
    Expr* initializer = nullptr;
    if(match(Token_Type::EQUAL))
    {
        initializer = expression();
    }
    tokenType = Token_Type::SEMICOLON;
    message = "Expect ';' after variable declaration.";
    consume(tokenType, message);
    return new Stmt::Var_Stmt(name, initializer);
}

Stmt* Parser::whileStatement()
{
    Token_Type tokenType = Token_Type::LEFT_PAREN;
    string message = "Expect '(' after 'while'.";
    consume(tokenType, message);
    
    Expr* condition = expression();
    tokenType = Token_Type::RIGHT_PAREN;
    message = "Expect ')' after condtion";
    consume(tokenType, message);
    
    Stmt* body = statement();
    
    return new Stmt::While_Stmt(condition, body);
}

Stmt* Parser::expressionStatement()
{
    Expr* expr = expression();
    Token_Type tokenType = Token_Type::SEMICOLON;
    string message = "Expect ';' after expression.";

    consume(tokenType, message);
    return new Stmt::Expression_Stmt(expr);
}

Stmt::Function_Stmt* Parser::function(string& kind)
{
    Token_Type tokenType = Token_Type::IDENTIFIER;
    string message = "Expect "+kind+" name.";
    Interpreter_Token name = consume(tokenType, message);
    
    tokenType = Token_Type::LEFT_PAREN;
    message = "Expect '(' after "+kind+" name.";
    consume(tokenType, message);
    
    vector<shared_ptr<Interpreter_Token>> parameters;
    tokenType = Token_Type::RIGHT_PAREN;
    if(!check(tokenType))
    {
        do
        {
            if(parameters.size() >= 255)
            {
                message = "Cannot have more than 255 parameters.";
                Interpreter_Token token = peek();
                error(token, message);
            }
            tokenType = Token_Type::IDENTIFIER;
            message = "Expect parameter name.";
            parameters.push_back(make_shared<Interpreter_Token>(consume(tokenType, message)));
        }while(match(Token_Type::COMMA));
    }
    tokenType = Token_Type::RIGHT_PAREN;
    message = "Expect ')' after parameters.";
    consume(tokenType, message);
    
    tokenType = Token_Type::LEFT_BRACE;
    message = "Expect '{' before "+kind+" body.";
    vector<shared_ptr<Stmt*>> body = block();
    return new Stmt::Function_Stmt(name, parameters, body);
}

vector<shared_ptr<Stmt*>> Parser::block()
{
    vector<shared_ptr<Stmt*>> statements;
    Token_Type tokenType = Token_Type::RIGHT_BRACE;

    while(!check(tokenType) && !isAtEnd())
    {
        statements.push_back(make_shared<Stmt*>(declaration()));
    }
    
    string message = "Expect '}' after block.";
    consume(tokenType, message);
    return statements;
}

Expr* Parser::assignment()
{
    Expr* expr = logicalOr();
    
    if(match(Token_Type::EQUAL))
    {
        Interpreter_Token equals = previous();
        Expr* value = assignment();
        if(typeid(expr) == typeid(Expr::Variable_Expr))
        {
            Interpreter_Token name =  dynamic_cast<Expr::Variable_Expr&>(*expr).name;
            return new Expr::Assign_Expr(name, value);
        }
        
        string message = "Invalid assignment target";
        error(equals, message);
    }
    
    return expr;
}

Expr* Parser::logicalOr()
{
    Expr* expr = logicalAnd();
    
    while(match(Token_Type::OR))
    {
        Interpreter_Token operatorToken = previous();
        Expr* right = equality();
        expr = new Expr::Logical_Expr(expr, operatorToken, right);
    }
    
    return expr;
}

Expr* Parser::logicalAnd()
{
    Expr* expr = equality();
    
    while(match(Token_Type::AND))
    {
        Interpreter_Token operatorToken = previous();
        Expr* right = equality();
        
        expr = new Expr::Logical_Expr(expr, operatorToken, right);
    }
    
    return expr;
}

Expr* Parser::equality()
{
    Expr* expr = comparison();
    
    while(match(Token_Type::BANG_EQUAL, Token_Type::EQUAL_EQUAL))
    {
        Interpreter_Token operatorToken = previous();
        Expr* right = comparison();
        expr = new Expr::Binary_Expr(expr, operatorToken, right);
    }
    
    return expr;
}

bool Parser::check(Token_Type& type)
{
    if(isAtEnd())
    {
        return false;
    }
    
    return peek().tokenType == type;
}

Interpreter_Token Parser::advance()
{
    if(!isAtEnd())
    {
        current++;
    }
    
    return previous();
}

Interpreter_Token Parser::previous()
{
    return *(tokens.at(current - 1).get());;
}

bool Parser::isAtEnd()
{
    return peek().tokenType == Token_Type::END;
}

Interpreter_Token Parser::peek()
{
    return *(tokens.at(current).get());
}

Expr* Parser::comparison()
{
    Expr* expr = addition();
    
    while(match(Token_Type::GREATER, Token_Type::GREATER_EQUAL, Token_Type::LESS, Token_Type::LESS_EQUAL))
    {
        Interpreter_Token operatorToken = previous();
        Expr* right = addition();
        expr = new Expr::Binary_Expr(expr, operatorToken, right);
    }
    
    return expr;
}

Expr* Parser::addition()
{
    Expr* expr = multiplication();
    
    while(match(Token_Type::MINUS, Token_Type::PLUS))
    {
        Interpreter_Token operatorToken = previous();
        Expr* right = multiplication();
        
        expr = new Expr::Binary_Expr(expr, operatorToken, right);
    }
    
    return expr;
}

Expr* Parser::multiplication()
{
    Expr* expr = unary();
    
    while(match(Token_Type::SLASH, Token_Type::STAR))
    {
        Interpreter_Token operatorToken = previous();
        Expr* right = unary();
        
        expr = new Expr::Binary_Expr(expr, operatorToken, right);
    }
    
    return expr;
}

Expr* Parser::unary()
{
    if(match(Token_Type::BANG, Token_Type::MINUS))
    {
        Interpreter_Token operatorToken = previous();
        Expr* right = unary();
        return new Expr::Unary_Expr(operatorToken, right);
    }
    return call();
}
Expr* Parser::finishCall(Expr* callee)
{
    vector<shared_ptr<Expr>> arguments;
    Token_Type tokenType = Token_Type::RIGHT_PAREN;
    if(!check(tokenType))
    {
        do{
            if(arguments.size() >= 127)
            {
                string message = "Cannot have more than 127 arguments.";
                Interpreter_Token peekToken = peek();
                error(peekToken, message);
            }
            arguments.push_back(make_shared<Expr>(*expression()));
        }while (match(Token_Type::COMMA));
    }
    string message = "Expect ')' after arguments";
    Interpreter_Token paren = consume(tokenType, message);
    
    return new Expr::Call_Expr(callee, paren, arguments);
}

Expr* Parser::call()
{
    Expr* expr = primary();
    
    while(true)
    {
        if(match(Token_Type::LEFT_PAREN))
        {
            expr = finishCall(expr);
        }
        else
        {
            break;
        }
    }
    
    return expr;
}

Expr* Parser::primary()
{
    if(match(Token_Type::FALSE))
    {
        return new Expr::Literal_Expr(false);
    }
    if(match(Token_Type::TRUE))
    {
        return new Expr::Literal_Expr(true);
    }
    if(match(Token_Type::NIL))
    {
        return new Expr::Literal_Expr(nullptr);
    }
    if(match(Token_Type::NUMBER, Token_Type::STRING))
    {
        any literal = previous().literal;
        return new Expr::Literal_Expr(literal);
    }
    if(match(Token_Type::IDENTIFIER))
    {
        Interpreter_Token name = previous();
        Expr expr = Expr::Variable_Expr(name);
        return new Expr::Variable_Expr(name);
    }
    
    if(match(Token_Type::LEFT_PAREN))
    {
        Expr* expr = expression();
        Token_Type tokenType = Token_Type::RIGHT_PAREN;
        string message = "Expect ')' after expression";
        consume(tokenType, message);
        return new Expr::Grouping_Expr(expr);
    }
    
    string message = "Expect expression";
    Interpreter_Token token = peek();
    throw error(token, message);
}



Interpreter_Token Parser::consume(Token_Type& type, string& message)
{
    try {
        if(check(type))
        {
            return advance();
        }
        throw Parser::ParseError();
    } catch (ParseError& pe) {
        cout <<pe.what() << endl;
    }
    
    Interpreter_Token token = peek();
    throw error(token, message);
}


Parser::ParseError Parser::error(Interpreter_Token& token, string& message)
{
    Script_Engine::error(token, message);
    return ParseError();
}

vector<shared_ptr<Stmt*>> Parser::parse()
{
    vector<shared_ptr<Stmt*>> statements;
    while(!isAtEnd())
    {
        statements.push_back(make_shared<Stmt*>(declaration()));
    }
    
    return statements;
}

void Parser::synchronize()
{
    advance();
    
    while(!isAtEnd())
    {
        if(previous().tokenType == Token_Type::SEMICOLON)
        {
            return ;
        }
        
        switch (peek().tokenType) {
            case Token_Type::CLASS:
            case Token_Type::FUN:
            case Token_Type::VAR:
            case Token_Type::LET:
            case Token_Type::FOR:
            case Token_Type::IF:
            case Token_Type::WHILE:
            case Token_Type::PRINT:
            case Token_Type::RETURN:
                return ;
        }
        
        advance();
    }
}
