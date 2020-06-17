//
//  node.cpp
//  Nadia-CPP
//
//  Created by Dean Lee on 17/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "node.hpp"
#include <regex>
#include "date.hpp"

inline smatch match;
regex falseString("[fF][aA][lL][sS][eE]");
regex trueString("[tT][rR][uU][eE]");
regex intPattern("No");
regex doublePattern("De");
regex datePattern("Da");
regex urlPattern("Url");
regex hashPattern("Ha");
regex uuidPattern("Id");
regex defiStringPattern("(^[\'\"])(.*)([\'\"]$)");

template <typename T>
int Node<T>::staticNodeId = 0;

template <typename T>
Node<T>::Node(string& parentText, shared_ptr<Tokens> tokens): tokens(tokens)
{
    nodeId = staticNodeId;
    staticNodeId++;
    
    initialisation(parentText, tokens);
}

template <typename T>
void Node<T>::setNodeLine(shared_ptr<int> inputNodeLine)
{
    nodeLine = inputNodeLine;
}

template <typename T>
shared_ptr<int> Node<T>::getNodeLine()
{
    return nodeLine;
}

template <typename T>
int Node<T>::getStaticNodeId()
{
    return staticNodeId;
}

template <typename T>
int Node<T>::getNodeId()
{
    return nodeId;
}

template <typename T>
string& Node<T>::getNodeName()
{
    return nodeName;
}

template <typename T>
shared_ptr<Tokens> Node<T>::getTokens()
{
    return tokens;
}

template <typename T>
shared_ptr<string> Node<T>::getVariableName()
{
    return variableName;
}

template <typename T>
void Node<T>::setNodeVariable(shared_ptr<string> inputNewVariableName)
{
    variableName = inputNewVariableName;
}

template <typename T>
shared_ptr<Fact_Value<T>> Node<T>::getFactValue()
{
    return value;
}

template <typename T>
void Node<T>::setValue(shared_ptr<Fact_Value<T>> fv)
{
    value = fv;
}

template <typename T>
void Node<T>::setValue(string& lastTokenString, string& lastToken)
{
    map<string, int> tokenMap = {{"No", 0},{"Do", 1},{"Da", 2},{"Url", 3},{"Id", 4},{"Ha", 5},{"Q", 6},{"L", 7},{"M", 8},{"U", 9},{"C", 10}};
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

template <typename T>
bool Node<T>::isBoolean(string& str)
{
    return regex_match(str, match, falseString) || regex_match(str, match, trueString)? true : false;
}

template <typename T>
bool Node<T>::isInteger(string& str)
{
    return regex_match(str, match, intPattern)? true: false;
}

template <typename T>
bool Node<T>::isDouble(string& str)
{
    return regex_match(str, match, doublePattern)? true: false;
}

template <typename T>
bool Node<T>::isDate(string& str)
{
    return regex_match(str, match, datePattern)? true: false;
}

template <typename T>
bool Node<T>::isURL(string& str)
{
    return regex_match(str, match, urlPattern)? true: false;
}

template <typename T>
bool Node<T>::isHash(string& str)
{
    return regex_match(str, match, hashPattern)? true: false;
}

template <typename T>
bool Node<T>::isUUID(string& str)
{
    return regex_match(str, match, uuidPattern)? true: false;
}
