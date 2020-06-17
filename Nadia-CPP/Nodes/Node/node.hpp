//
//  node.hpp
//  Nadia-CPP
//
//  Created by Dean Lee on 17/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef node_hpp
#define node_hpp

#include <stdio.h>
#include <string>
#include "interpreter_token.hpp"
#include "fact_value.hpp"

enum Line_Type {
    META, VALUE_CONCLUSION, EXPR_CONCLUSION, COMPARISON, RULE_SET_LINE, ITERATE, WARNING
};

class Script_Engine;

using namespace std;
class Node
{
protected:
    static int staticNodeId;
    int nodeId;
    string nodeName;
    int nodeLine;
    string variableName;
    
    template <typename T>
    Fact_Value<T> value;
    
    Interpreter_Token tokens;
    void setValue(string lastTokenString, string lastToken);
    bool isBoolean(string str);
    bool isInteger(string str);
    bool isDouble(string str);
    bool isDate(string str);
    bool isURL(string str);
    bool isHash(string str);
    bool isUUID(string str);
    
public:
    Node(string parentText, Interpreter_Token tokens);
    
    virtual void initialisation(string parentText, Interpreter_Token tokens) = 0;
    virtual Line_Type getLineType();
    
    template<typename T>
    Fact_Value<T> selfEvaluate(map<string, Fact_Value<T>> workingMemory, Script_Engine scriptEngine);
    
    void setNodeLine(int nodeLine);
    int getNodeLine();
    static int getStaticNodeId();
    int getNodeId();
    string getNodeName();
    Interpreter_Token getTokens();
    string getVariableName();
    void setNodeVariable(string newVariableName);
    
    template<typename T>
    Fact_Value<T> getFactValue();
    
    template<typename T>
    void setValue(Fact_Value<T> fv);
    
};
#endif /* node_hpp */
