//
//  eval_interpreter.hpp
//  Nadia-CPP
//
//  Created by Dean Lee on 17/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef eval_interpreter_hpp
#define eval_interpreter_hpp

#include <stdio.h>
#include <regex>
#include <optional>
#include "interpreter.hpp"
#include "expression.hpp"
#include "statement.hpp"
#include "string_handler.hpp"
#include "environment.hpp"

class Script_Engine;
class Script_Engine_Callable;

class Eval_Interpreter : public Expr::Visitor<any>, public Stmt::Visitor<any>
{
    any evaluate(Expr* expr);
    void execute(Stmt* stmt);
    bool isTruthy(any& anyValue);
    bool isEqual(any& left, any& right);
    string stringify(any& anyObject);
    void checkNumberOperand(Interpreter_Token& operatorToken, any& right);
    void checkNumberOperand(Interpreter_Token& operatorToken, any& left, any& right);
public:
    Environment globals;
    Environment environment;
    Eval_Interpreter();
    void executeBlock(vector<shared_ptr<Stmt*>>& statements, Environment& environment);
    void interpret(vector<shared_ptr<Stmt*>>& expr);
    any visitLiteralExpr(Expr::Literal_Expr* expr) override;
    any visitLogicalExpr(Expr::Logical_Expr* expr) override;
    any visitGroupingExpr(Expr::Grouping_Expr* expr) override;
    any visitUnaryExpr(Expr::Unary_Expr* expr) override;
    any visitBinaryExpr(Expr::Binary_Expr* expr) override;
    any visitCallExpr(Expr::Call_Expr* expr)override;
    any visitVariableExpr(Expr::Variable_Expr* expr) override;
    any visitAssignExpr(Expr::Assign_Expr* expr) override;
    any visitExpressionStmt(Stmt::Expression_Stmt* stmt) override;
    any visitFunctionStmt(Stmt::Function_Stmt* stmt) override;
    any visitPrintStmt(Stmt::Print_Stmt* stmt) override;
    any visitReturnStmt(Stmt::Return_Stmt* stmt) override;
    any visitVarStmt(Stmt::Var_Stmt* stmt) override;
    any visitLetStmt(Stmt::Let_Stmt* stmt) override;
    any visitBlockStmt(Stmt::Block_Stmt* stmt) override;
    any visitIfStmt(Stmt::If_Stmt* stmt) override;
    any visitWhileStmt(Stmt::While_Stmt* stmt) override;
    
};
#endif /* eval_interpreter_hpp */
