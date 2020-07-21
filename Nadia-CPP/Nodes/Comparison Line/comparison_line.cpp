//
//  comparison_line.cpp
//  Nadia-CPP
//
//  Created by Dean Lee on 21/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "comparison_line.hpp"
#include "fact_date_value.hpp"
#include "fact_boolean_value.hpp"
#include "fact_string_value.hpp"
#include "fact_defi_string_value.hpp"
#include "fact_double_value.hpp"
#include "fact_integer_value.hpp"
#include "script_engine.hpp"
#include "runtime_exception.hpp"

Line_Type Comparison_Line::lineType = Line_Type::COMPARISON;

Comparison_Line::Comparison_Line(string& childText, shared_ptr<Tokens> tokens): Node(childText, tokens)
{
    initialisation(childText, tokens);
}

void Comparison_Line::initialisation(string& childText, shared_ptr<Tokens> tokens)
{
    
    /*
     * this line pattern is as (^[ML]+)(O)([MLNoDaDeHaUrlId]*$)
     */
    
    this->nodeName = childText;
    /*
     * In javascript engine '=' operator means assigning a value, hence if the operator is '=' then it needs to be replaced with '=='.
     */
    
    string operatorToken = "O";
    vector<string> tempVector;
    for(shared_ptr<string> item: tokens.get()->tokensStringList)
    {
        tempVector.push_back(*item.get());
    }
    
    vector<string>::iterator itr = find(tempVector.begin(), tempVector.end(), operatorToken);
    
    int operatorIndex = -1;
    if(itr != tempVector.end())
    {
        operatorIndex = (int)distance(tempVector.begin(), itr);
    }
    
    string operatorFromText = *(tokens.get()->tokensStringList.at(operatorIndex).get());
    operatorString = operatorFromText.compare("=") == 0?string("=="):const_cast<string&>(*tokens.get()->tokensList.at(operatorIndex));
    
    
    if(operatorString.compare("==") == 0)
    {
        char delimiter = '=';
        
        this->variableName = String_Handler::stringTrim(String_Handler::stringSplit(childText, delimiter).at(0));
    }
    else
    {
        char charArray[operatorString.length() + 1];
        strcpy(charArray, operatorString.c_str());
        
        this->variableName =  String_Handler::stringTrim(String_Handler::stringSplit(childText, charArray[0]).at(0));
    }
    
    lhs = this->variableName;
    
    int tokensStringListSize = (int)tokens.get()->tokensStringList.size();
    string lastToken = *(const_cast<shared_ptr<string>&>(tokens.get()->tokensList.at(tokensStringListSize-1)).get());
    string lastTokenString = *(const_cast<vector<shared_ptr<string>>&>(tokens->tokensStringList).at(tokensStringListSize - 1));
    this->setValue(lastTokenString, lastToken);
    rhs = this->value;
}


string* Comparison_Line::getLHS()
{
    return &lhs;
}


any Comparison_Line::getRHS()
{
    return rhs;
}


Line_Type* Comparison_Line::getLineType()
{
    return &lineType;
}


any Comparison_Line::selfEvaluate(unordered_map<string, any>& workingMemory)
{
    /*
     * Negation type can only be used for this line type
     */
    any workingMemoryLhsValue = workingMemory[this->variableName].has_value()? workingMemory[this->variableName] : nullptr;
    
    any workingMemoryRhsValue;
    if(getRHS().type() == typeid(shared_ptr<Fact_String_Value<string>>))
    {
        
        workingMemoryRhsValue = workingMemory[*(any_cast<shared_ptr<Fact_String_Value<string>>>(getRHS()).get()->getValue().get())];
    }
    else
    {
        workingMemoryRhsValue = getRHS();
    }
    
    string script = "";
    
    /*
     * There will NOT be the case of that workingMemoryRhsValue is null because the node must be in following format;
     * - A = 12231 (int or double)
     * - A = Adam sandler (String)
     * - A = 11/11/1977 (Date)
     * - A = 123123dfae1421412aer(Hash)
     * - A = 1241414-12421312-142421312(UUID)
     * - A = true(Boolean)
     * - A = www.aiBrain.com(URL)
     * - A = B(another variable)
     */
    
    /*
     * if it is about date comparison then string of 'script' needs rewriting
     */
    const type_info& lhsValueType = workingMemoryLhsValue.type();
    const type_info& rhsValueType = workingMemoryRhsValue.type();
    if((workingMemoryLhsValue.has_value() &&  lhsValueType == typeid(shared_ptr<Fact_Date_Value<Date>>)) || (workingMemoryRhsValue.has_value() && rhsValueType == typeid(shared_ptr<Fact_Date_Value<Date>>)))
    {
        map<string, int> operatorTokenMap{{">", 0}, {">=", 1}, {"<", 2}, {"<=", 3}};
        
        Date* lhsDateValue = any_cast<shared_ptr<Fact_Date_Value<Date>>>(workingMemoryLhsValue).get()->getValue().get();
        Date* rhsDateValue = any_cast<shared_ptr<Fact_Date_Value<Date>>>(workingMemoryRhsValue).get()->getValue().get();
        
        switch(operatorTokenMap.at(operatorString))
        {
            case 0:
            {
                bool isAfter = (*lhsDateValue).isAfter(*rhsDateValue);
                return Fact_Value<bool>::parse(isAfter);
            }
            case 1:
            {
                bool isAfterAndEqualTo = (*lhsDateValue).isAfter(*rhsDateValue) || (*lhsDateValue).isEqual(*rhsDateValue);
                return Fact_Value<bool>::parse(isAfterAndEqualTo);
            }
            case 2:
            {
                bool isBefore = (*lhsDateValue).isBefore(*rhsDateValue);
                return Fact_Value<bool>::parse(isBefore);
            }
            case 3:
            {
                bool isBeforeAndEqualTo = (*lhsDateValue).isBefore(*rhsDateValue) || (*lhsDateValue).isEqual(*rhsDateValue);
                return Fact_Value<bool>::parse(isBeforeAndEqualTo);
            }
        }
    }
    else if(workingMemoryLhsValue.has_value() &&
            (lhsValueType == typeid(shared_ptr<Fact_Double_Value<double>>) ||
             lhsValueType == typeid(shared_ptr<Fact_Integer_Value<int>>)))
    {
        string lhsValueInString = (lhsValueType == typeid(shared_ptr<Fact_Double_Value<double>>))? String_Handler::toString(*((any_cast<shared_ptr<Fact_Double_Value<double>>>(workingMemoryLhsValue).get())->getValue().get())) : String_Handler::toString(*((any_cast<shared_ptr<Fact_Integer_Value<int>>>(workingMemoryLhsValue)).get()->getValue().get()));
        
        string rhsValueInString = (lhsValueType == typeid(shared_ptr<Fact_Double_Value<double>>))? String_Handler::toString(*(any_cast<shared_ptr<Fact_Double_Value<double>>>(workingMemoryRhsValue).get()->getValue().get())) : String_Handler::toString(*(any_cast<shared_ptr<Fact_Integer_Value<int>>>(workingMemoryRhsValue).get()->getValue().get()));
        
        
        script = lhsValueInString.append(operatorString).append(rhsValueInString);
    }
    else
    {
        if(workingMemoryRhsValue.has_value() && workingMemoryLhsValue.has_value())
        {
            string lhsValueInString = String_Handler::toString(*((any_cast<shared_ptr<Fact_Defi_String_Value<string>>>(workingMemoryLhsValue).get())->getValue().get()));
            string rhsValueInString = String_Handler::toString(*((any_cast<shared_ptr<Fact_Defi_String_Value<string>>>(workingMemoryRhsValue).get())->getValue().get()));
            
            script = lhsValueInString.insert(0, "\"").append("\"").append(operatorString).append("\"").append(rhsValueInString).append("\"");
        }
        
    }
    bool result;
    shared_ptr<Fact_Boolean_Value<bool>> fbv;
    if(workingMemoryRhsValue.has_value() && workingMemoryLhsValue.has_value())
    {
        result = any_cast<bool>(Script_Engine::evalStatement(script));
        fbv = Fact_Value<bool>::parse(result);
    }
    
    return fbv;
}
