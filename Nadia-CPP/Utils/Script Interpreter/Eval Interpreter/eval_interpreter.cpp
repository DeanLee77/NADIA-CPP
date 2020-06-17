//
//  eval_interpreter.cpp
//  Nadia-CPP
//
//  Created by Dean Lee on 17/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "eval_interpreter.hpp"
#include "script_engine.hpp"
#include "script_engine_callable.hpp"
#include "script_engine_function.hpp"
#include "return.hpp"

Eval_Interpreter::Eval_Interpreter()
{
    environment = globals;
}

void Eval_Interpreter::interpret(vector<shared_ptr<Stmt*>>& statements)
{
    try{
        for(shared_ptr<Stmt*> statement : statements)
        {
            execute(*statement.get());
        }
    }
    catch(Runtime_Error error)
    {
        Script_Engine::runtimeError(error);
    }
}

any Eval_Interpreter::visitLiteralExpr(Expr::Literal_Expr* expr)
{
    return expr->literal;
}

any Eval_Interpreter::visitLogicalExpr(Expr::Logical_Expr* expr)
{
    any left = evaluate(const_cast<Expr*>(expr->left));
    
    if(expr->operatorToken.tokenType == Token_Type::OR)
    {
        if(isTruthy(left))
        {
            return left;
        }
    }
    else
    {
        if(!isTruthy(left))
        {
            return left;
        }
    }
    
    return evaluate(const_cast<Expr*>(expr->right));
}

any Eval_Interpreter::visitGroupingExpr(Expr::Grouping_Expr* expr)
{
    return evaluate(const_cast<Expr*>(expr->expression));
}

any Eval_Interpreter::visitUnaryExpr(Expr::Unary_Expr* expr)
{
    any right =  evaluate(const_cast<Expr*>(expr->right));
    switch(expr->operatorToken.tokenType)
    {
        case Token_Type::BANG:
        {
            return !isTruthy(right);
        }
        case Token_Type::MINUS:
        {
            Interpreter_Token token = expr->operatorToken;
            checkNumberOperand(token, right);
            return -any_cast<double>(right);
        }
    }
    
    return nullptr;
}

any Eval_Interpreter::visitBinaryExpr(Expr::Binary_Expr* expr)
{
    any left = evaluate(const_cast<Expr*>(expr->left));
    any right = evaluate(const_cast<Expr*>(expr->right));
    Interpreter_Token token = expr->operatorToken;
    
    switch(expr->operatorToken.tokenType)
    {
        case Token_Type::GREATER:
        {
            checkNumberOperand(token, left, right);
            if(left.type() == typeid(double) && right.type() == typeid(double))
            {
                return any_cast<double>(left) > any_cast<double>(right);
            }
            else if(left.type() == typeid(long double) && right.type() == typeid(long double))
            {
                return any_cast<long double>(left) > any_cast<long double>(right);
            }
            else if(left.type() == typeid(int) && right.type() == typeid(int))
            {
                return any_cast<int>(left) > any_cast<int>(right);
            }
            else if(left.type() == typeid(long int) && right.type() == typeid(long int))
            {
                return any_cast<long int>(left) > any_cast<long int>(right);
            }
            else if(left.type() == typeid(long long int) && right.type() == typeid(long long int))
            {
                return any_cast<long long int>(left) > any_cast<long long int>(right);
            }
            else if(left.type() == typeid(short int) && right.type() == typeid(short int))
            {
                return any_cast<short int>(left) > any_cast<short int>(right);
            }
            else if(left.type() == typeid(float) && right.type() == typeid(float))
            {
                return any_cast<float>(left) > any_cast<float>(right);
            }
        }
        case Token_Type::GREATER_EQUAL:
        {
            checkNumberOperand(token, left, right);
            if(left.type() == typeid(double) && right.type() == typeid(double))
            {
                return any_cast<double>(left) >= any_cast<double>(right);
            }
            else if(left.type() == typeid(long double) && right.type() == typeid(long double))
            {
                return any_cast<long double>(left) >= any_cast<long double>(right);
            }
            else if(left.type() == typeid(int) && right.type() == typeid(int))
            {
                return any_cast<int>(left) >= any_cast<int>(right);
            }
            else if(left.type() == typeid(long int) && right.type() == typeid(long int))
            {
                return any_cast<long int>(left) >= any_cast<long int>(right);
            }
            else if(left.type() == typeid(long long int) && right.type() == typeid(long long int))
            {
                return any_cast<long long int>(left) >= any_cast<long long int>(right);
            }
            else if(left.type() == typeid(short int) && right.type() == typeid(short int))
            {
                return any_cast<short int>(left) >= any_cast<short int>(right);
            }
            else if(left.type() == typeid(float) && right.type() == typeid(float))
            {
                return any_cast<float>(left) >= any_cast<float>(right);
            }
        }
        case Token_Type::LESS:
        {
            checkNumberOperand(token, left, right);
            if(left.type() == typeid(double) && right.type() == typeid(double))
            {
                return any_cast<double>(left) < any_cast<double>(right);
            }
            else if(left.type() == typeid(long double) && right.type() == typeid(long double))
            {
                return any_cast<long double>(left) < any_cast<long double>(right);
            }
            else if(left.type() == typeid(int) && right.type() == typeid(int))
            {
                return any_cast<int>(left) < any_cast<int>(right);
            }
            else if(left.type() == typeid(long int) && right.type() == typeid(long int))
            {
                return any_cast<long int>(left) < any_cast<long int>(right);
            }
            else if(left.type() == typeid(long long int) && right.type() == typeid(long long int))
            {
                return any_cast<long long int>(left) < any_cast<long long int>(right);
            }
            else if(left.type() == typeid(short int) && right.type() == typeid(short int))
            {
                return any_cast<short int>(left) < any_cast<short int>(right);
            }
            else if(left.type() == typeid(float) && right.type() == typeid(float))
            {
                return any_cast<float>(left) < any_cast<float>(right);
            }
        }
        case Token_Type::LESS_EQUAL:
        {
            checkNumberOperand(token, left, right);
            if(left.type() == typeid(double) && right.type() == typeid(double))
            {
                return any_cast<double>(left) <= any_cast<double>(right);
            }
            else if(left.type() == typeid(long double) && right.type() == typeid(long double))
            {
                return any_cast<long double>(left) <= any_cast<long double>(right);
            }
            else if(left.type() == typeid(int) && right.type() == typeid(int))
            {
                return any_cast<int>(left) <= any_cast<int>(right);
            }
            else if(left.type() == typeid(long int) && right.type() == typeid(long int))
            {
                return any_cast<long int>(left) <= any_cast<long int>(right);
            }
            else if(left.type() == typeid(long long int) && right.type() == typeid(long long int))
            {
                return any_cast<long long int>(left) <= any_cast<long long int>(right);
            }
            else if(left.type() == typeid(short int) && right.type() == typeid(short int))
            {
                return any_cast<short int>(left) <= any_cast<short int>(right);
            }
            else if(left.type() == typeid(float) && right.type() == typeid(float))
            {
                return any_cast<float>(left) <= any_cast<float>(right);
            }
        }
        case Token_Type::MINUS:
        {
            checkNumberOperand(token, left, right);
            if(left.type() == typeid(double) && right.type() == typeid(double))
            {
                return any_cast<double>(left) - any_cast<double>(right);
            }
            else if(left.type() == typeid(long double) && right.type() == typeid(long double))
            {
                return any_cast<long double>(left) - any_cast<long double>(right);
            }
            else if(left.type() == typeid(int) && right.type() == typeid(int))
            {
                return any_cast<int>(left) - any_cast<int>(right);
            }
            else if(left.type() == typeid(long int) && right.type() == typeid(long int))
            {
                return any_cast<long int>(left) - any_cast<long int>(right);
            }
            else if(left.type() == typeid(long long int) && right.type() == typeid(long long int))
            {
                return any_cast<long long int>(left) - any_cast<long long int>(right);
            }
            else if(left.type() == typeid(short int) && right.type() == typeid(short int))
            {
                return any_cast<short int>(left) - any_cast<short int>(right);
            }
            else if(left.type() == typeid(float) && right.type() == typeid(float))
            {
                return any_cast<float>(left) - any_cast<float>(right);
            }
        }
        case Token_Type::PLUS:
        {
            if((left.type() != typeid(string) && right.type() != typeid(string)) ||
               (left.type() != typeid(char) && right.type() != typeid(char)))
            {
                if(left.type() == typeid(double) && right.type() == typeid(double))
                {
                    return any_cast<double>(left) + any_cast<double>(right);
                }
                else if(left.type() == typeid(long double) && right.type() == typeid(long double))
                {
                    return any_cast<long double>(left) + any_cast<long double>(right);
                }
                else if(left.type() == typeid(int) && right.type() == typeid(int))
                {
                    return any_cast<int>(left) + any_cast<int>(right);
                }
                else if(left.type() == typeid(long int) && right.type() == typeid(long int))
                {
                    return any_cast<long int>(left) + any_cast<long int>(right);
                }
                else if(left.type() == typeid(long long int) && right.type() == typeid(long long int))
                {
                    return any_cast<long long int>(left) + any_cast<long long int>(right);
                }
                else if(left.type() == typeid(short int) && right.type() == typeid(short int))
                {
                    return any_cast<short int>(left) + any_cast<short int>(right);
                }
                else if(left.type() == typeid(float) && right.type() == typeid(float))
                {
                    return any_cast<float>(left) + any_cast<float>(right);
                }
            }
            
            if(left.type() == typeid(string) && right.type() == typeid(string))
            {
                return any_cast<string>(left).append(any_cast<string>(right));
            }
            
            if(left.type() == typeid(char) && right.type() == typeid(char))
            {
                string initialString = " ";
                
                initialString.push_back(any_cast<char>(left));
                initialString.push_back(any_cast<char>(right));
                
                return String_Handler::stringTrim(initialString);
            }
            
            string message = "Operands must be two numbers or two strings or two characters";
            throw Runtime_Error(token, message);
        }
        case Token_Type::SLASH:
        {
            checkNumberOperand(token, left, right);
            if(left.type() == typeid(double) && right.type() == typeid(double))
            {
                return any_cast<double>(left) / any_cast<double>(right);
            }
            else if(left.type() == typeid(long double) && right.type() == typeid(long double))
            {
                return any_cast<long double>(left) / any_cast<long double>(right);
            }
            else if(left.type() == typeid(int) && right.type() == typeid(int))
            {
                return any_cast<int>(left) / any_cast<int>(right);
            }
            else if(left.type() == typeid(long int) && right.type() == typeid(long int))
            {
                return any_cast<long int>(left) / any_cast<long int>(right);
            }
            else if(left.type() == typeid(long long int) && right.type() == typeid(long long int))
            {
                return any_cast<long long int>(left) / any_cast<long long int>(right);
            }
            else if(left.type() == typeid(short int) && right.type() == typeid(short int))
            {
                return any_cast<short int>(left) / any_cast<short int>(right);
            }
            else if(left.type() == typeid(float) && right.type() == typeid(float))
            {
                return any_cast<float>(left) / any_cast<float>(right);
            }
        }
        case Token_Type::STAR:
        {
            checkNumberOperand(token, left, right);
            if(left.type() == typeid(double) && right.type() == typeid(double))
            {
                return any_cast<double>(left) * any_cast<double>(right);
            }
            else if(left.type() == typeid(long double) && right.type() == typeid(long double))
            {
                return any_cast<long double>(left) * any_cast<long double>(right);
            }
            else if(left.type() == typeid(int) && right.type() == typeid(int))
            {
                return any_cast<int>(left) * any_cast<int>(right);
            }
            else if(left.type() == typeid(long int) && right.type() == typeid(long int))
            {
                return any_cast<long int>(left) * any_cast<long int>(right);
            }
            else if(left.type() == typeid(long long int) && right.type() == typeid(long long int))
            {
                return any_cast<long long int>(left) * any_cast<long long int>(right);
            }
            else if(left.type() == typeid(short int) && right.type() == typeid(short int))
            {
                return any_cast<short int>(left) * any_cast<short int>(right);
            }
            else if(left.type() == typeid(float) && right.type() == typeid(float))
            {
                return any_cast<float>(left) * any_cast<float>(right);
            }
        }
        case Token_Type::BANG_EQUAL:
        {
            return !isEqual(left, right);
        }
        case Token_Type::EQUAL:
        {
            return isEqual(left, right);
        }
    }
    
    return nullptr;
}

any Eval_Interpreter::visitCallExpr(Expr::Call_Expr* expr)
{
    any callee = evaluate(const_cast<Expr*>(expr->callee));
    
    vector<shared_ptr<any>> arguments;
    
    for(auto argument : expr->arguments)
    {
        arguments.push_back(make_shared<any>(evaluate(argument.get())));
    }
    
    if(typeid(callee) != typeid(Script_Engine_Callable))
    {
        string message = "Can only call functions and classes.";
        Interpreter_Token token = expr->paren;
        throw Runtime_Error(token, message);
    }
    
    Script_Engine_Callable *function = any_cast<Script_Engine_Callable*>(callee);
    
    if(arguments.size() != function->arity())
    {
        string message = "Expected "+String_Handler::toString(function->arity())+" arguments but got "+String_Handler::toString(arguments.size());
        Interpreter_Token token = expr->paren;
        throw Runtime_Error(token, message);
    }
    return function->call(*this, arguments);
}

any Eval_Interpreter::visitVariableExpr(Expr::Variable_Expr* var)
{
    return environment.get(const_cast<Interpreter_Token&>(var->name));
}

any Eval_Interpreter::visitAssignExpr(Expr::Assign_Expr* expr)
{
    
    any value = evaluate(const_cast<Expr*>(expr->value));
    
    environment.assign(const_cast<Interpreter_Token&>(expr->name), value);
    
    return value;
}

any Eval_Interpreter::visitExpressionStmt(Stmt::Expression_Stmt* stmt)
{
    return evaluate(const_cast<Expr*>(stmt->expression));
}

any Eval_Interpreter::visitFunctionStmt(Stmt::Function_Stmt* stmt)
{
    Script_Engine_Function *function = new Script_Engine_Function(*stmt, environment);
    environment.define(const_cast<string&>(stmt->name.lexeme), *reinterpret_cast<any*>(function));
    
    return nullptr;
}

any Eval_Interpreter::visitPrintStmt(Stmt::Print_Stmt* stmt)
{
    any value = evaluate(const_cast<Expr*>(stmt->expression));
    cout << stringify(value) << endl;
    
    return nullptr;
}


any Eval_Interpreter::visitReturnStmt(Stmt::Return_Stmt* stmt)
{
    any value;
    optional<Expr> exprOp{*stmt->value};
    if(exprOp.has_value())
    {
        value = evaluate(const_cast<Expr*>(stmt->value));
    }
    
    throw Return(value);
}

any Eval_Interpreter::visitVarStmt(Stmt::Var_Stmt* stmt)
{
    any value = nullptr;
    
    if(make_optional<Expr>(*stmt->initializer).has_value())
    {
        value = evaluate(const_cast<Expr*>(stmt->initializer));
    }
    environment.define(const_cast<string&>(stmt->name.lexeme), value);
    
    return value;
}

any Eval_Interpreter::visitLetStmt(Stmt::Let_Stmt* stmt)
{
    any value = nullptr;
    
    if(make_optional<Expr>(*stmt->initializer).has_value())
    {
        value = evaluate(const_cast<Expr*>(stmt->initializer));
    }
    environment.define(const_cast<string&>(stmt->name.lexeme), value);
    
    return nullptr;
}

any Eval_Interpreter::visitBlockStmt(Stmt::Block_Stmt* stmt)
{
    executeBlock(const_cast<vector<shared_ptr<Stmt*>>&>(stmt->statements), environment);
    
    return nullptr;
}

any Eval_Interpreter::visitIfStmt(Stmt::If_Stmt* stmt)
{
    any anyValue = evaluate(const_cast<Expr*>(stmt->condition));
    if(isTruthy(anyValue))
    {
        execute(const_cast<Stmt*>(stmt->thenBranch));
    }
    else if(make_optional(const_cast<Stmt&>(*stmt->elseBranch)).has_value())
    {
        execute(const_cast<Stmt*>(stmt->elseBranch));
    }
    
    return nullptr;
}

any Eval_Interpreter::visitWhileStmt(Stmt::While_Stmt* stmt)
{
    any anyValue = evaluate(const_cast<Expr*>(stmt->condition));
    while(isTruthy(anyValue))
    {
        execute(const_cast<Stmt*>(stmt->body));
    }
    
    return nullptr;
}

any Eval_Interpreter::evaluate(Expr* expr)
{
    return expr->accept(this);
}

void Eval_Interpreter::execute(Stmt* stmt)
{
    stmt->accept(this);
}

void Eval_Interpreter::executeBlock(vector<shared_ptr<Stmt*>>& statements, Environment& inEnvironment)
{
    Environment previous = const_cast<Environment&>(this->environment);
    
    try{
        this->environment = inEnvironment;
        for(auto statement: statements)
        {
            execute(*statement.get());
        }
    }
    catch(...){
        
    }
    this->environment = previous;
    
}

bool Eval_Interpreter::isTruthy(any& anyValue)
{
    if(!anyValue.has_value())
    {
        return false;
    }
    if(anyValue.type() == typeid(bool))
    {
        return any_cast<bool>(anyValue);
    }
    
    return true;
}

bool Eval_Interpreter::isEqual(any& left, any& right)
{
    if(left.has_value() && right.has_value())
    {
        const type_info& leftType = left.type();
        if(leftType == typeid(string))
        {
            return any_cast<string>(left).compare(any_cast<string>(right)) == 0;
        }
        else if(leftType == typeid(int))
        {
            return  any_cast<int>(left) == any_cast<int>(right);
        }
        else if(left.type() == typeid(long int))
        {
            return any_cast<long int>(left)== any_cast<long int>(right);
        }
        else if(left.type() == typeid(long long int))
        {
            return any_cast<long long int>(left) == any_cast<long long int>(right);
        }
        else if(left.type() == typeid(short int))
        {
            return any_cast<short int>(left) == any_cast<short int>(right);
        }
        else if(leftType == typeid(double))
        {
            return any_cast<double>(left) == any_cast<double>(right);
        }
        else if(left.type() == typeid(long double))
        {
            return any_cast<long double>(left) == any_cast<long double>(right);
        }
        else if(leftType == typeid(float))
        {
            return any_cast<float>(left) == any_cast<float>(right);
        }
        else if(leftType == typeid(char))
        {
            return any_cast<char>(left) == any_cast<char>(right);
        }
        else if(leftType == typeid(bool))
        {
            return any_cast<bool>(left) == any_cast<bool>(right);
        }
    }
    if(!left.has_value() && !right.has_value())
    {
        return true;
    }
    if(!left.has_value())
    {
        return false;
    }
    return false;
}

string Eval_Interpreter::stringify(any& anyObject)
{
    if(! anyObject.has_value())
    {
        return "nill";
    }
    
    if(anyObject.type() == typeid(double) || anyObject.type() == typeid(long double) || anyObject.type() == typeid(float))
    {
        string text;
        if(anyObject.type() == typeid(double))
        {
            text = String_Handler::toString(any_cast<double>(anyObject));
        }
        else if(anyObject.type() == typeid(long double))
        {
            text = String_Handler::toString(any_cast<long double>(anyObject));
        }
        else
        {
            text = String_Handler::toString(any_cast<float>(anyObject));
        }
        
        regex re(".*\\.0$");
        smatch match;
        bool matched = regex_match(text, match, re);
        if(matched)
        {
            text = text.substr(0,text.length()-2);
        }
        return text;
    }
    if(anyObject.type() == typeid(int))
    {
        return String_Handler::toString(any_cast<int>(anyObject));
    }
    if(anyObject.type() == typeid(short int))
    {
        return String_Handler::toString(any_cast<short int>(anyObject));
    }
    if(anyObject.type() == typeid(long int))
    {
        return String_Handler::toString(any_cast<long int>(anyObject));
    }
    if(anyObject.type() == typeid(long long int))
    {
        return String_Handler::toString(any_cast<long long int>(anyObject));
    }
    if(anyObject.type() == typeid(short int))
    {
        return String_Handler::toString(any_cast<short int>(anyObject));
    }
    if(anyObject.type() == typeid(bool))
    {
        return String_Handler::toString(any_cast<bool>(anyObject));
    }
    if(anyObject.type() == typeid(char))
    {
        return String_Handler::toString(any_cast<char>(anyObject));
    }
    
    return any_cast<string>(anyObject);;
}

void Eval_Interpreter::checkNumberOperand(Interpreter_Token& operatorToken, any& right)
{
    if(right.type() == typeid(double) || right.type() == typeid(long double) || right.type() == typeid(int) || right.type() == typeid(short int) || right.type() == typeid(long int) || right.type() == typeid(long long int) || right.type() == typeid(float))
    {
        return ;
    }
    
    string message = "Operand must be a number.";
    throw Runtime_Error(operatorToken, message);
}

void Eval_Interpreter::checkNumberOperand(Interpreter_Token& operatorToken, any& left, any& right)
{
    if((left.type() == typeid(double) && right.type() == typeid(double)) ||
       (right.type() == typeid(long double) && left.type() == typeid(long double)) ||
       (right.type() == typeid(int) && left.type() == typeid(int)) ||
       (right.type() == typeid(short int) && left.type() == typeid(short int)) ||
       (right.type() == typeid(long int) && left.type() == typeid(long int)) ||
       (right.type() == typeid(long long int) && left.type() == typeid(long long int)) ||
       (right.type() == typeid(float) && left.type() == typeid(float)))
    {
        return ;
    }
    string message = "Operand must be a number.";
    throw Runtime_Error(operatorToken, message);
}
