//
//  interpreter_token_test.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 12/5/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "interpreter_token_test.hpp"

void Interpreter_Token_Test::tokenTypeTest()
{
    Token_Type type = Token_Type::LEFT_BRACE;
    string lexeme = "{";
    
    Interpreter_Token token(type, lexeme, "", 9);
    cout << "token.tokenType: " << token.tokenType << endl;
    cout << "token.toString(): " << token.toString() << endl;
}
