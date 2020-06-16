//
//  interpreter_scanner.cpp
//  Nadia-CPP
//
//  Created by Dean Lee on 8/3/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "interpreter_scanner.hpp"
#include "script_engine.hpp"

Scanner::Scanner(string& source): source(source)
{
    
}


vector<shared_ptr<Interpreter_Token>> Scanner::scanTokens()
{
    while (!isAtEnd()) {
        // We are at the beginning of the next lexeme.
        start = current;
        scanToken();
    }
    interpreterTokens.push_back(make_shared<Interpreter_Token>(Token_Type::END, "", "", line));
    return interpreterTokens;
}

bool Scanner::isAtEnd()
{
    return current >= source.length();
}

void Scanner::scanToken()
{
    char c = advance();
    Token_Type tokenType;
    switch(c)
    {
        case '(':
            tokenType = Token_Type::LEFT_PAREN;
            addToken(tokenType);
            break;
        case ')':
            tokenType = Token_Type::RIGHT_PAREN;
            addToken(tokenType);
            break;
        case '{':
            tokenType = Token_Type::LEFT_BRACE;
            addToken(tokenType);
            break;
        case '}':
            tokenType = Token_Type::RIGHT_BRACE;
            addToken(tokenType);
            break;
        case ',':
            tokenType = Token_Type::COMMA;
            addToken(tokenType);
            break;
        case '.':
            tokenType = Token_Type::DOT;
            addToken(tokenType);
            break;
        case'-':
            tokenType = Token_Type::MINUS;
            addToken(tokenType);
            break;
        case '+':
            tokenType = Token_Type::PLUS;
            addToken(tokenType);
            break;
        case '*':
            tokenType = Token_Type::STAR;
            addToken(tokenType);
            break;
        case ';':
            tokenType = Token_Type::SEMICOLON;
            addToken(tokenType);
            break;
        case '!':
            tokenType = match('=') ? Token_Type::BANG_EQUAL : Token_Type::BANG;
            addToken(tokenType);
            break;
        case '=':
            tokenType = match('=') ? Token_Type::EQUAL_EQUAL : Token_Type::EQUAL;
            addToken(tokenType);
            break;
        case '<':
            tokenType = match('=') ? Token_Type::LESS_EQUAL : Token_Type::LESS;
            addToken(tokenType);
            break;
        case '>':
            tokenType = match('=') ? Token_Type::GREATER_EQUAL : Token_Type::GREATER;
            addToken(tokenType);
            break;
        case '/':
            if (match('/')) {
                // A comment goes until the end of the line.
                while (peek() != '\n' && !isAtEnd())
                {
                    advance();
                }
            } else {
                tokenType = Token_Type::SLASH;
                addToken(tokenType);
            }
            break;
        case 'o':
            if (peek() == 'r') {
                tokenType = Token_Type::OR;
                addToken(tokenType);
            }
            break;
        case '|':
            if(peek() == '|')
            {
                tokenType = Token_Type::OR;
                addToken(tokenType);
            }
            break;
        case '&':
            if(peek() == '&')
            {
                tokenType = Token_Type::AND;
                addToken(tokenType);
            }
            break;
        case ' ':
        case '\r':
        case '\t':
            // Ignore whitespace.
            break;
        case '\n':
            line++;
            break;
        case '"':
            stringMark();
            break;
        default:
            if (isDigit(c))
            {
                number();
            }
            else if (isAlpha(c))
            {
                identifier();
            }
            else
            {
                Script_Engine::error(line, "Unexpected Character.");
            }
            break;
            
    }
}

char Scanner::advance()
{
    current++;
    
    return source.at(current - 1);
}


void Scanner::addToken(Token_Type& tokenType)
{
    any nullPointer = nullptr;
    addToken(tokenType, nullPointer);
}

void Scanner::addToken(Token_Type& tokenType, any& literal)
{
    string text = source.substr(start, current-start);
    interpreterTokens.push_back(make_shared<Interpreter_Token>(tokenType, text, literal, line));
}

bool Scanner::match(char expected)
{
    if (isAtEnd())
    {
        return false;
    }
    if (source.at(current) != expected)
    {
        return false;
    }
    current++;
    return true;
}

char Scanner::peek()
{
    if (isAtEnd())
    {
        return '\0';
    }
    return source.at(current);
}

void Scanner::stringMark()
{
    while(peek() != '"' && !isAtEnd())
    {
        if (peek() == '\n')
        {
            line++;
        }
        advance();
    }
    // Unterminated string.
    if (isAtEnd()) {
        Script_Engine::error(line, "Unterminated string.");
        return;
    }
    // The closing ".
    advance();
    // Trim the surrounding quotes.
    any value = source.substr(start + 1, current - 1);
    Token_Type tokenType = Token_Type::STRING;
    addToken(tokenType, value);
}

bool Scanner::isDigit(char c)
{
    return c >= '0' && c <= '9';
}

void Scanner::number()
{
    while (isDigit(peek()))
    {
        advance();
    }
    // Look for a fractional part.
    if (peek() == '.' && isDigit(peekNext()))
    {
        // Consume the "."
        advance();
        while (isDigit(peek()))
        {
            advance();
        }
    }
    Token_Type tokenType = Token_Type::NUMBER;
    any subString = stod(source.substr(start, current-start));
    addToken(tokenType, subString);
}

char Scanner::peekNext()
{
    if (current + 1 >= source.length())
    {
        return '\0';
    }
    return source.at(current + 1);
}

bool Scanner::isAlpha(char c)
{
    return (c >= 'a' && c <= 'z') ||
    (c >= 'A' && c <= 'Z') ||
    c == '_';
}

void Scanner::identifier()
{
    while (isAlphaNumeric(peek()))
    {
        advance();
    }
    
    // See if the identifier is a reserved word.
    string text = source.substr(start, current);
    auto iterator = keywords.find(text);
    Token_Type tokenType;
    if(iterator != keywords.end())
    {
        tokenType = iterator->second;
    }
    else
    {
        tokenType = Token_Type::IDENTIFIER;
    }
    
    addToken(tokenType);
}

bool Scanner::isAlphaNumeric(char c)
{
    return isAlpha(c) || isDigit(c);
}

const map<string, Token_Type> Scanner::keywords = {
    {"and", Token_Type::AND},
    {"class", Token_Type::CLASS},
    {"else", Token_Type::ELSE},
    {"false", Token_Type::FALSE},
    {"for", Token_Type::FOR},
    {"fun", Token_Type::FUN},
    {"if", Token_Type::IF},
    {"nil", Token_Type::NIL},
    {"or", Token_Type::OR},
    {"print", Token_Type::PRINT},
    {"return", Token_Type::RETURN},
    {"super", Token_Type::SUPER},
    {"this", Token_Type::THIS},
    {"true", Token_Type::TRUE},
    {"var", Token_Type::VAR},
    {"while", Token_Type::WHILE}
};


