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
#include "tokens.hpp"
#include "fact_value.hpp"
//#include "date.hpp"

namespace LineType {
    enum Line_Type {
        META, VALUE_CONCLUSION, EXPR_CONCLUSION, COMPARISON, RULE_SET, ITERATE, WARNING
    };
}

class Script_Engine;

using namespace std;
using namespace LineType;

template <typename T>
class Node
{
protected:
    static int staticNodeId;
    int nodeId;
    string nodeName;
    shared_ptr<int> nodeLine;
    shared_ptr<string> variableName;
    shared_ptr<Fact_Value<T>> value;
    shared_ptr<Tokens> tokens;
    
    void setValue(string& lastTokenString, string& lastToken);
    bool isBoolean(string& str);
    bool isInteger(string& str);
    bool isDouble(string& str);
    bool isDate(string& str);
    bool isURL(string& str);
    bool isHash(string& str);
    bool isUUID(string& str);
    
public:
    Node(string& parentText, shared_ptr<Tokens> tokens);
    virtual ~Node(){ };
    
    virtual void initialisation(string& parentText, shared_ptr<Tokens> tokens) = 0;
    virtual Line_Type getLineType();
    
    Fact_Value<T> selfEvaluate(map<string, shared_ptr<Fact_Value<T>>> workingMemory, Script_Engine* scriptEngine);
    void setNodeLine(shared_ptr<int> nodeLine);
    shared_ptr<int> getNodeLine();
    static int getStaticNodeId();
    int getNodeId();
    string& getNodeName();
    shared_ptr<Tokens> getTokens();
    shared_ptr<string> getVariableName();
    void setNodeVariable(shared_ptr<string> newVariableName);
    shared_ptr<Fact_Value<T>> getFactValue();
    void setValue(shared_ptr<Fact_Value<T>> fv);
    
};
#endif /* node_hpp */
