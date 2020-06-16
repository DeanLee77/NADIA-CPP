//
//  interpreter_scanner.hpp
//  Nadia-CPP
//
//  Created by Dean Lee on 8/3/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef interpreter_scanner_hpp
#define interpreter_scanner_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include "interpreter_token.hpp"

using namespace std;
class Scanner
{
    const string source;
    vector<shared_ptr<Interpreter_Token>>  interpreterTokens;
    int start = 0;
    int current  = 0;
    int line = 1;
    bool isAtEnd();
    void scanToken();
    char advance();
    void addToken(Token_Type& tokenType);
    void addToken(Token_Type& tokenType, any& literal);
    bool match(char expected);
    char peek();
    void stringMark();
    bool isDigit(char c);
    void number();
    char peekNext();
    bool isAlpha(char c);
    void identifier();
    bool isAlphaNumeric(char c);
    static const map<string, Token_Type> keywords;
    
    
public:
    Scanner(string& source);
    vector<shared_ptr<Interpreter_Token>> scanTokens();
};
#endif /* interpreter_scanner_hpp */
