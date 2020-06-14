//
//  interpreter.hpp
//  Nadia-CPP
//
//  Created by Dean Lee on 11/3/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef interpreter_hpp
#define interpreter_hpp

#include <stdio.h>
#include <regex>
#include <optional>
#include "expression.hpp"
#include "statement.hpp"
#include "string_handler.hpp"
#include "environment.hpp"

class Script_Engine;
class Script_Engine_Callable;

class Interpreter: public Expr::Visitor<any>, public Stmt::Visitor<void>
{
    Environment environment;
    any evaluate(Expr& expr);
    void execute(Stmt& stmt);
    bool isTruthy(any& anyValue);
    bool isEqual(any& left, any& right);
    string stringify(any& anyObject);
    void checkNumberOperand(Interpreter_Token& operatorToken, any& right);
    void checkNumberOperand(Interpreter_Token& operatorToken, any& left, any& right);
public:
    Interpreter();
    void executeBlock(vector<shared_ptr<Stmt>>& statements, Environment& environment);
    void interpret(vector<shared_ptr<Stmt>>& expr);
    any visitLiteralExpr(Expr::Literal_Expr* expr) override;
    any visitLogicalExpr(Expr::Logical_Expr* expr) override;
    any visitGroupingExpr(Expr::Grouping_Expr* expr) override;
    any visitUnaryExpr(Expr::Unary_Expr* expr) override;
    any visitBinaryExpr(Expr::Binary_Expr* expr) override;
    any visitCallExpr(Expr::Call_Expr* expr)override;
    any visitVariableExpr(Expr::Variable_Expr* expr) override;
    any visitAssignExpr(Expr::Assign_Expr* expr) override;
    void visitExpressionStmt(Stmt::Expression_Stmt* stmt) override;
    void visitPrintStmt(Stmt::Print_Stmt* stmt) override;
    void visitVarStmt(Stmt::Var_Stmt* stmt) override;
    void visitBlockStmt(Stmt::Block_Stmt* stmt) override;
    void visitIfStmt(Stmt::If_Stmt* stmt) override;
    void visitWhileStmt(Stmt::While_Stmt* stmt) override;
    
};
#endif /* interpreter_hpp */
