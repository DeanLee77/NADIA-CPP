//
//  AST_Printer.hpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 24/5/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef ast_printer_hpp
#define ast_printer_hpp

#include <stdio.h>
#include "expression.hpp"
#include "string_handler.hpp"
using namespace std;


class AST_Printer : public Expr::Visitor<string>
{
    template<typename ...Ts>
    string parenthesize(string name, Ts ...exprs);
    
    template<typename Ex, typename ...Args>
    string parenthesizeAux(Ex expr, Args ...args);
    
    template<typename Ex>
    string parenthesizeAux(Ex expr);
    
public:
    string print(Expr& expr);
    string visitBinaryExpr(Expr::Binary_Expr* binary) override;
    string visitGroupingExpr(Expr::Grouping_Expr* grouping) override;
    string visitUnaryExpr(Expr::Unary_Expr* unary) override;
    string visitLiteralExpr(Expr::Literal_Expr* liter) override;
};

template<typename Ex>
string AST_Printer::parenthesizeAux(Ex arg)
{
    string returnValue;
    return returnValue.append(" ").append(dynamic_cast<Expr*>(const_cast<Expr*>(arg))->accept(this));
};

template<typename Ex, typename ...Args>
string AST_Printer::parenthesizeAux(Ex first, Args ...args)
{
    string returnValue;
    return returnValue.append(" ").append(dynamic_cast<Expr*>(const_cast<Expr*>(first))->accept(this)).append(parenthesizeAux(args...));
};

template<typename ...Ts>
string AST_Printer::parenthesize(string name, Ts ...exprs)
{
    string returnValue;
    
    returnValue.append("(").append(name).append(parenthesizeAux(exprs...)).append(")");
    
    return returnValue;
};

#endif /* ast_printer_hpp */
