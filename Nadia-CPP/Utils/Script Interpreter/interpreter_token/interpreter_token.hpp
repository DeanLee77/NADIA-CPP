//
//  interpreter_token.hpp
//  Nadia-CPP
//
//  Created by Dean Lee on 6/3/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef interpreter_token_hpp
#define interpreter_token_hpp

#include <stdio.h>
#include <string>
#include <any>

using namespace std;

namespace TokenType {
    enum Token_Type
    {
        //single-character tokens
        LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
        COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,
        
        
        //one or two character tokens
        BANG, BANG_EQUAL,
        EQUAL, EQUAL_EQUAL,
        GREATER, GREATER_EQUAL,
        LESS, LESS_EQUAL,
        
        //literals
        IDENTIFIER, STRING, NUMBER,
        
        //keywords
        AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
        PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE, LET,
        
        END
    };
}

using namespace TokenType;

class Interpreter_Token
{
    
public:
    Token_Type tokenType;
    string lexeme;
    any literal;
    int line;
    
    Interpreter_Token(Token_Type tokenType, string lexeme, any literal, int line);
    string toString();
};


#endif /* interpreter_token_hpp */
