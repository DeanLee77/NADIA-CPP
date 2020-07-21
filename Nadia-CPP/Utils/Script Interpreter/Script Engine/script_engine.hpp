//
//  script_engine.hpp
//  Nadia-CPP
//
//  Created by Dean Lee on 6/3/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef script_engine_hpp
#define script_engine_hpp

#include <stdio.h>
#include <iostream>
#include <string>

#include "interpreter_token.hpp"
#include "ast_printer.hpp"
#include "interpreter_runtime_error.hpp"
#include "interpreter.hpp"
#include "eval_interpreter.hpp"

using namespace std;

class Parser;
class Eval_Interpreter;

class Script_Engine
{
    inline static Interpreter *interpreter = new Interpreter();
    inline static Eval_Interpreter *evalInterpreter;
    static void report(int line, string where, string message);
public:
    inline static bool hadError = false;
    inline static bool hadRuntimeError = false;
    Script_Engine();
    static void run(string source);
    static any evalStatement(string source);
    void* evaluate(string script);
    static void error(int line, string message);
    static void error(Interpreter_Token token, string message);
    static void runtimeError(Runtime_Error error);
    
    
};

#endif /* script_engine_hpp */
