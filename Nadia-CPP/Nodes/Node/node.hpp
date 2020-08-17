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
#include <regex>
#include <optional>
#include <any>
#include <unordered_map>

#include "tokens.hpp"
#include "string_handler.hpp"


namespace LineType {
    enum Line_Type {
        META, VALUE_CONCLUSION, EXPR_CONCLUSION, COMPARISON, RULE_SET, ITERATE, WARNING
    };
}

class Script_Engine;
extern smatch match;

using namespace std;
using namespace LineType;

class Metadata_Line;
class Value_Conclusion_Line;
class Comparison_Line;
class Expr_Conclusion_Line;

class Node
{
protected:
    static int staticNodeId;
    int nodeId;
    string nodeName;
    int nodeLine;
    string variableName;
    any value;
    shared_ptr<Tokens> tokens; 
    void setValue(string& lastTokenString, string& lastToken);
    bool isBoolean(string& str);
    bool isInteger(string& str);
    bool isDouble(string& str);
    bool isDate(string& str);
    bool isURL(string& str);
    bool isHash(string& str);
    bool isUUID(string& str);
    bool isQuoted(string& str);
    
    
public:
    Node(string& parentText, shared_ptr<Tokens> tokens);
    virtual ~Node(){ };
    
    virtual void initialisation(string& parentText, shared_ptr<Tokens> tokens) = 0;
    virtual Line_Type* getLineType() = 0;
    virtual any selfEvaluate(unordered_map<string, any>& workingMemory) = 0;
    
    void setNodeLine(int nodeLine);
    int* getNodeLine();
    static int* getStaticNodeId();
    int* getNodeId();
    string* getNodeName();
    shared_ptr<Tokens> getTokens();
    string* getVariableName();
    void setNodeVariable(string& newVariableName);
    any getFactValue();
    void setValue(any fv);
    
};
#endif /* node_hpp */
