//
//  AST_Printer.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 24/5/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//


#include "ast_printer.hpp"
#include <iostream>
string AST_Printer::print(Expr& expr)
{
    return expr.accept(this);
}

string AST_Printer::visitBinaryExpr(Expr::Binary_Expr* binary)
{
    return parenthesize(binary->operatorToken.lexeme, binary->left, binary->right);
}

string AST_Printer::visitGroupingExpr(Expr::Grouping_Expr* group)
{
    return parenthesize("group", group->expression);
}

string AST_Printer::visitUnaryExpr(Expr::Unary_Expr* unary)
{
    return parenthesize(unary->operatorToken.lexeme, unary->right);
}

string AST_Printer::visitLiteralExpr(Expr::Literal_Expr* literal)
{
    string value;
    if(literal->literal.has_value())
    {
        const type_info& literalType = literal->literal.type();
        if(literalType == typeid(int))
        {
           value = String_Handler::toString(any_cast<int>(literal->literal));
        }
        else if(literalType == typeid(double))
        {
           value = String_Handler::toString(any_cast<double>(literal->literal));
        }
        else if(literalType == typeid(float))
        {
            value = String_Handler::toString(any_cast<float>(literal->literal));
        }
        else if(literalType == typeid(bool))
        {
            value = String_Handler::toString(any_cast<bool>(literal->literal));
        }
        else if(literalType == typeid(char))
        {
            value = String_Handler::toString(any_cast<char>(literal->literal));
        }
        else if(literalType == typeid(string))
        {
           value = any_cast<string>(literal->literal);
        }
    }
    return value;
}

