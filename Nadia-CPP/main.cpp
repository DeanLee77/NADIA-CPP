//
//  main.cpp
//  Nadia-CPP
//
//  Created by Dean Lee on 4/2/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include <iostream>
#include <variant>
#include <regex>
//#include "fact_value_test.hpp"
//#include "string_handler_test.hpp"
//#include "date_test.hpp"
//#include "tokenizer_test.hpp"

//#include "script_engine.hpp"
//#include "interpreter_token_test.hpp"
#include "interpreter_test.hpp"

using namespace std;

int main(int argc, const char * argv[]) {

//    Fact_Value_Test::testGenerateFactValue();
//    String_Handler_Test::testAll();
//    Date_Test::generateDatesAndPrint();
//    Tokenizer_Test::tesing();
    
//    for(int i = 0 ; i < 5; i++)
//    {
//        cout << i << " th" << endl;
//        cout << " static value" << Script_Engine::hadError << endl;
//        Script_Engine::hadError = !Script_Engine::hadError;
//
//    }
    
//    Interpreter_Token_Test::tokenTypeTest();
    cout << 4+5 << endl;
    string text = "123.01";
    regex re(".*\\.0$");
    smatch match;
    bool matched = regex_match(text, match, re);
    cout << "matched : " << matched << endl;
//    Interpreter_Test::expressionTest();
    Interpreter_Test::scriptEngineTest();

    string test;
    cout << test << endl;
    return 0;
}
