//
//  interpreter_test.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 27/5/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//
#include <iostream>
#include <memory>
#include "interpreter_test.hpp"

void Interpreter_Test::expressionTest()
{
    Expr* firstLiteral = new Expr::Literal_Expr(123);
    Interpreter_Token firstToken = Interpreter_Token(Token_Type::MINUS, "-", "", 1);
    
    Expr* binaryLeft = new Expr::Unary_Expr(firstToken, firstLiteral);
    
    Interpreter_Token secondToken = Interpreter_Token(Token_Type::STAR, "*", "", 1);

    Expr* secondLiteral = new Expr::Literal_Expr(45.67);
    Expr* binaryRight = new Expr::Grouping_Expr(secondLiteral);
//    Expr *expression = new Expr::Binary_Expr(binaryLeft, Interpreter_Token(Token_Type::STAR, "*", "", 1), binaryRight);
    

    
    
    Expr expression = Expr::Binary_Expr(binaryLeft, secondToken, binaryRight);

//    assert(AST_Printer().print(expression).compare("(* (- 123) (group 45.67))") == 0);
}

void Interpreter_Test::scriptEngineTest()
{
    string expression = "23+34*44/11;";
    Script_Engine::run(expression);
}
