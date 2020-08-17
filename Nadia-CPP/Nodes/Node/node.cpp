//
//  node.cpp
//  Nadia-CPP
//
//  Created by Dean Lee on 17/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "node.hpp"
#include "fact_value.hpp"
#include "date.hpp"
#include "metadata_line.hpp"
#include "value_conclusion_line.hpp"
#include "comparison_line.hpp"
#include "expr_conclusion_line.hpp"
#include <iostream>
regex falseString("[fF][aA][lL][sS][eE]");
regex trueString("[tT][rR][uU][eE]");
regex defiStringPattern("(^[\'\"])(.*)([\'\"]$)");

int Node::staticNodeId = 0;

Node::Node(string& parentText, shared_ptr<Tokens> tokens): tokens(tokens), nodeId(staticNodeId)
{
    staticNodeId++;
}

void Node::setNodeLine(int inputNodeLine)
{
    nodeLine = inputNodeLine;
}

int* Node::getNodeLine()
{
    return &nodeLine;
}

int* Node::getStaticNodeId()
{
    return &staticNodeId;
}

int* Node::getNodeId()
{
    return &nodeId;
}


string* Node::getNodeName()
{
    return &nodeName;
}


shared_ptr<Tokens> Node::getTokens()
{
    return tokens;
}


string* Node::getVariableName()
{
    return &variableName;
}


void Node::setNodeVariable(string& inputNewVariableName)
{
    variableName = inputNewVariableName;
}

any Node::getFactValue()
{
    return value;
}


void Node::setValue(any fv)
{
    value = fv;
}


void Node::setValue(string& lastTokenString, string& lastToken)
{
    unordered_map<string, int> tokenMap = {{"No", 0},{"Do", 1},{"Da", 2},{"Url", 3},{"Id", 4},{"Ha", 5},{"Q", 6},{"L", 7},{"M", 8},{"U", 9},{"C", 10}};
    int lastTokenIndex = tokenMap.find(lastTokenString)->second;
    
    switch(lastTokenIndex)
    {
        case 0:
        {
            int intValue = stoi(lastToken);
            value = Fact_Value<int>::parse(intValue);
            break;
        }
        case 1:
        {
            double doubleValue = stod(lastToken);
            value = Fact_Value<double>::parse(doubleValue);
            break;
        }
        case 2:
        {
            Date dateValue(lastToken);
            value = Fact_Value<Date>::parse(dateValue);
            break;
        }
        case 3:
        {
            value = Fact_Value<string>::parseURL(lastToken);
            break;
        }
        case 4:
        {
            value = Fact_Value<string>::parseUUID(lastToken);
            break;
        }
        case 5:
        {
            value = Fact_Value<string>::parseHash(lastToken);
            break;
        }
        case 6:
        {
            value = Fact_Value<string>::parseDefiString(lastToken);
            break;
        }
        case 7 ... 10:
        {
            if(isBoolean(lastToken))
            {
                bool boolValue = regex_match(lastToken, match, falseString)? false : true;
                value =  Fact_Value<bool>::parse(boolValue);
                break;
            }
            else
            {
                if(regex_match(lastToken, match, defiStringPattern))
                {
                    string defiString = match.str(2);
                    value = Fact_Value<string>::parseDefiString(defiString);
                }
                else
                {
                    value = Fact_Value<string>::parse(lastToken);
                }
            }
            break;
        }
    }
}

bool Node::isBoolean(string& str)
{
    return regex_match(str, match, falseString) || regex_match(str, match, trueString)? true : false;
}

bool Node::isInteger(string& str)
{
    return str.compare("No") == 0? true:false;
}

bool Node::isDouble(string& str)
{
    return str.compare("De") == 0? true:false;
}

bool Node::isDate(string& str)
{
    return str.compare("Da") == 0? true:false;
}

bool Node::isURL(string& str)
{
    return str.compare("Url") == 0? true:false;
}

bool Node::isHash(string& str)
{
    return str.compare("Ha") == 0? true:false;
}

bool Node::isUUID(string& str)
{
    return str.compare("Id") == 0? true:false;
}

 bool Node::isQuoted(string& str)
{
    regex quoteRegex("^([\"\\“])(.*)([\"\\”])(\\.)*");
    
    return regex_search(str, match, quoteRegex);
}
