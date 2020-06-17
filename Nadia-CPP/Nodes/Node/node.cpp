//
//  node.cpp
//  Nadia-CPP
//
//  Created by Dean Lee on 17/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "node.hpp"

int Node::staticNodeId = 0;

Node::Node(string parentText, Interpreter_Token tokens): tokens(tokens)
{
    nodeId = staticNodeId;
    staticNodeId++;
    
    initialisation(parentText, tokens);
}

void Node::setNodeLine(int nodeLine)
{
    this.nodeLine = nodeLine;
}

int Node::getNodeLine()
{
    return this.nodeLine;
}

int Node::getStaticNodeId()
{
    return staticNodeId;
}
int Node::getNodeId()
{
    return this.nodeId;
}

string Node::getNodeName()
{
    return this.nodeName;
}

Interpreter_Token Node::getTokens()
{
    return this.tokens;
}

string Node::getVariableName()
{
    return variableName;
}

void Node::setNodeVariable(string newVariableName)
{
    this.variableName = newVariableName;
}

Fact_Value Node::getFactValue()
{
    return this.value;
}
void Node::setValue(Fact_Value fv)
{
    this.value = fv;
}

void Node::setValue(string lastTokenString, string lastToken)
{
    switch(lastTokenString)
    {
        case "No":
            this.value = FactValue.parse(Integer.parseInt(lastToken));
            break;
        case "Do":
            this.value = FactValue.parse(Double.parseDouble(lastToken));
            break;
        case "Da":
            this.value = FactValue.parse(LocalDate.parse(lastToken, DateTimeFormatter.ofPattern("d/M/yyyy")));
            break;
        case "Url":
            this.value = FactValue.parseURL(lastToken);
            break;
        case "Id":
            this.value = FactValue.parseUUID(lastToken);
            break;
        case "Ha":
            this.value = FactValue.parseHash(lastToken);
            break;
        case "Q":
            this.value = FactValue.parseDefiString(lastToken);
            break;
        case "L":
        case "M":
        case "U":
        case "C":
            if(this.isBoolean(lastToken))
            {
                this.value = lastToken.equalsIgnoreCase("false")? FactValue.parse(false): FactValue.parse(true);
            }
            else
            {
                Pattern defiStringPattern = Pattern.compile("(^[\'\"])(.*)([\'\"]$)");
                Matcher matcher = defiStringPattern.matcher(lastToken);
                if(matcher.find())
                {
                    String newS = matcher.group(2);
                    this.value = FactValue.parseDefiString(newS);
                }
                else
                {
                    this.value = FactValue.parse(lastToken);
                }
            }
            break;
    }
}
bool Node::isBoolean(string str)
{
    return str.matches("[FfAaLlSsEe]+")||str.matches("[TtRrUuEe]+")? true: false;
}

bool Node::isInteger(string str)
{
    return str.equals("No")? true: false;
}

bool Node::isDouble(string str)
{
    return str.equals("De")?true: false;
}

bool Node::isDate(string str)
{
    return str.equals("Da")? true: false;
}

bool Node::isURL(string str)
{
    return str.equals("Url")? true: false;
}

bool Node::isHash(string str)
{
    return str.equals("Ha")? true: false;
}

bool Node::isUUID(string str)
{
    return str.equals("Id")? true: false;
}
