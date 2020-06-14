//
//  expression.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 9/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "expression.hpp"

Expr::Assign_Expr::Assign_Expr(Interpreter_Token& name, Expr& value) : name(name), value(value)
{
    
}

Expr::Binary_Expr::Binary_Expr(Expr& inputLeft, Interpreter_Token& inputOperatorToken, Expr& inputRight) :left(inputLeft), operatorToken(inputOperatorToken),right(inputRight)
{
    
}

Expr::Call_Expr::Call_Expr(Expr& callee, Interpreter_Token& paren, vector<shared_ptr<Expr>> arguments): callee(callee), paren(paren), arguments(arguments)
{
    
}

Expr::Grouping_Expr::Grouping_Expr(Expr& inputExpression) : expression(inputExpression)
{
       
}

Expr::Literal_Expr::Literal_Expr(any inputLiteral) : literal(inputLiteral)
{
        
}

Expr::Logical_Expr::Logical_Expr(Expr& left, Interpreter_Token& operatorToken, Expr& right): left(left), operatorToken(operatorToken), right(right)
{
    
}

Expr::Unary_Expr::Unary_Expr(Interpreter_Token& inputOperatorToken, Expr& inputRight) : operatorToken(inputOperatorToken), right(inputRight)
{

}

Expr::Variable_Expr::Variable_Expr(Interpreter_Token& name) : name(name)
{
    
}

