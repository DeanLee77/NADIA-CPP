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
#include "fact_value_test.hpp"
//#include "string_handler_test.hpp"
//#include "date_test.hpp"
//#include "tokenizer_test.hpp"

//#include "script_engine.hpp"
//#include "interpreter_token_test.hpp"
#include "interpreter_test.hpp"
#include "fact_value.hpp"
#include "fact_string_value.hpp"
#include "metaline_test.hpp"
#include "node.hpp"
#include "metadata_line.hpp"
#include "tokenizer.hpp"
#include "tokens.hpp"

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
//    Interpreter_Test::expressionTest();
//    Interpreter_Test::scriptEngineTest();

//    string fsvValue = "fsvValue";
    
    Metaline_Testing::testing();
//    
//    shared_ptr<Fact_Value<string>> fv = make_shared<Fact_String_Value<string>>(Fact_String_Value<string>("fact string value"));
//    string testText = "FIXED name list AS LIST";
//    shared_ptr<Tokens> token = Tokenizer::getTokens(testText);
//    shared_ptr<Node> node = make_shared<Metadata_Line>(testText, token);
//    bool comparison = typeid(*node) == typeid(Metadata_Line);
//    cout << comparison << endl;
    return 0;
}
