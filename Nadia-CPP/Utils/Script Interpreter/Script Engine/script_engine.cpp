//
//  script_engine.cpp
//  Nadia-CPP
//
//  Created by Dean Lee on 6/3/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "script_engine.hpp"
#include "interpreter_scanner.hpp"
#include "parser.hpp"

//Interpreter* Script_Engine::interpreter = new Interpreter();

Script_Engine::Script_Engine()
{

}

void* Script_Engine::evaluate(string script)
{
    int i = 0;
    void *voidPtr = &i;
    return voidPtr;
}

void Script_Engine::error(int line, string message)
{
    Script_Engine::report(line, "", message);
}

void Script_Engine::error(Interpreter_Token token, string message)
{
    if(token.tokenType == Token_Type::END)
    {
        report(token.line, "at end", message);
    }
    else
    {
        string atString = " at '";
        report(token.line, atString.append(token.lexeme).append("' "), message);
    }
}

void Script_Engine::runtimeError(Runtime_Error error)
{
    cout << error.getMessage().append("\n[line ").append(String_Handler::toString(error.token.line)).append("]") << endl;
    
    hadRuntimeError = true;
}

void Script_Engine::report(int line, string where, string message)
{
    cout << "[ line " << line << " ] Error" << where << ": " << message << endl;
    hadError = true;
}

void Script_Engine::run(string source)
{
    Scanner scanner = Scanner(source);
    vector<shared_ptr<Interpreter_Token>> tokens = scanner.scanTokens();
    Parser parser(tokens);
    
    vector<shared_ptr<Stmt*>> statements = parser.parse();
    
    if(hadError)
    {
        return;
    }

//    interpreter = new Interpreter();
    interpreter->interpret(statements);

//    cout << AST_Printer().print(expression) << endl;
//    for(Interpreter_Token token: tokens)
//    {
//        cout << token.toString() << endl;
//    }
}

any Script_Engine::evalStatement(string source)
{
    Scanner scanner = Scanner(source);
    vector<shared_ptr<Interpreter_Token>> tokens = scanner.scanTokens();
    Parser parser(tokens);
    
    Stmt::Expression_Stmt* statement = dynamic_cast<Stmt::Expression_Stmt*>(*parser.parse().at(0).get());
    
    
    if(hadError)
    {
        return nullptr;
    }
    
    //    interpreter = new Interpreter();
    evalInterpreter = new Eval_Interpreter();
    return evalInterpreter->visitExpressionStmt(statement);
}
