//
//  expr_conclusion_line.cpp
//  Nadia-CPP
//
//  Created by Dean Lee on 22/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "expr_conclusion_line.hpp"
#include "script_engine.hpp"
#include "fact_boolean_value.hpp"
#include "fact_string_value.hpp"
#include "fact_date_value.hpp"
#include "fact_defi_string_value.hpp"
#include "fact_double_value.hpp"
#include "fact_hash_value.hpp"
#include "fact_integer_value.hpp"
#include "fact_url_value.hpp"
#include "fact_uuid_value.hpp"
#include "fact_list_value.hpp"


Line_Type Expr_Conclusion_Line::lineType = Line_Type::EXPR_CONCLUSION;

Expr_Conclusion_Line::Expr_Conclusion_Line(string& parentText, shared_ptr<Tokens> tokens) : Node(parentText, tokens)
{
    
}


void Expr_Conclusion_Line::initialisation(string& parentText, shared_ptr<Tokens> tokens)
{
    this->nodeName = parentText;
    string rawVariableName = parentText.substr(0, parentText.find("IS CALC"));
    this->variableName = String_Handler::stringTrim(rawVariableName);
    
    string calculatorStringToken = "C";
    vector<string> tempVector;
    for(shared_ptr<string> item: tokens.get()->tokensStringList)
    {
        tempVector.push_back(*item.get());
    }
    
    vector<string>::iterator itr = find(tempVector.begin(), tempVector.end(), calculatorStringToken);
    
    int calculatorStringTokenIndex = -1;
    
    if(itr != tempVector.end())
    {
        calculatorStringTokenIndex = (int)distance(tempVector.begin(), itr);
    }

    try{
        string lastTokenString = String_Handler::stringTrim(*(tokens->tokensStringList.at(calculatorStringTokenIndex)));
        string lastToken = String_Handler::stringTrim(*(tokens->tokensList.at(calculatorStringTokenIndex)));
        this->setValue(lastTokenString, lastToken);
        
        equation = this->value;
        
    }
    catch(exception& e){
        cout << e.what() << endl;
    }
    
}


any Expr_Conclusion_Line::getEquation()
{
    return equation;
}


void Expr_Conclusion_Line::setEquation(any newEquation)
{
    equation = newEquation;
}


Line_Type* Expr_Conclusion_Line::getLineType()
{
    return &lineType;
}


any Expr_Conclusion_Line::selfEvaluate(unordered_map<string , any>& workingMemory)
{
    /*
     * calculation can only handle int, double(long) and difference in years between two dates at the moment.
     * if difference in days or months is required then new 'keyword' must be introduced such as 'Diff Years', 'Diff Days', or 'Diff Months'
     */
    string equationInString = String_Handler::toString(*(any_cast<shared_ptr<Fact_String_Value<string>>>(equation).get()->getValue().get()));
    regex equationSymbol("[-+/*()?:;,.\"](\\s*)");
    regex datePattern("([0-2]?[0-9]|3[0-1])/(0?[0-9]|1[0-2])/([0-9][0-9])?[0-9][0-9]|([0-9][0-9])?[0-9][0-9]/(0?[0-9]|1[0-2])/([0-2]?[0-9]|3[0-1])");
    
    /*
     * logic for this is as follows;
     *     1. replace all variables with actual values from 'workingMemory'
     *  2. find out if equation is about date (difference in years) calculation or not
     *  3. if it is about date then call 'java.time.LocalDate'and 'java.time.temporal.ChronoUnit' package then do the calculation
     *  3-1. if it is about int or double(long) then use plain Javascript
     *
     */
    
    string script = equationInString;
    string tempScript = script;
    
    if(regex_search(equationInString, match, equationSymbol))
    {
        vector<string> tempVector;
        long startIndex = 0;
        long matchPosition = 0;
        string operand;
        for (sregex_iterator it = sregex_iterator(equationInString.begin(), equationInString.end(), equationSymbol);
             it != sregex_iterator(); it++)
        {
            match = *it;
            matchPosition = match.position();
            operand = equationInString.substr(startIndex, matchPosition - 1 - startIndex);
            tempVector.push_back(String_Handler::stringTrim(operand));
            
            startIndex = matchPosition + 1;
        }
        operand = equationInString.substr(startIndex, equationInString.length()-1);
        tempVector.push_back(String_Handler::stringTrim(operand));

        for(string vectorItem : tempVector)
        {
            any tempFv{workingMemory[vectorItem]};
            
            if(vectorItem.length() > 0 && tempFv.has_value())
            {
                
                string tempS;
                switch(typeIndexMap[tempFv.type()])
                {
                    case 0: //shared_ptr<Fact_Boolean_Value<bool>>
                    {
                        tempS = String_Handler::toString(*((any_cast<shared_ptr<Fact_Boolean_Value<bool>>>(tempFv)).get()->getValue().get()));
                        break;
                    }
                    case 1: //shared_ptr<Fact_String_Value<string>>
                    {
                        tempS = *((any_cast<shared_ptr<Fact_String_Value<string>>>(tempFv)).get()->getValue().get());
                        break;
                    }
                    case 2: // shared_ptr<Fact_Date_Value<Date>>
                    {
                        string tempStr = (any_cast<shared_ptr<Fact_Date_Value<Date>>>(tempFv)).get()->getValue().get()->getWholeDateValueInString();
                        tempScript = regex_replace(tempScript, regex(vectorItem), tempStr);
                        break;
                    }
                    case 3: // shared_ptr<Fact_Defi_String_Value<string>>
                    {
                        tempS = (*((any_cast<shared_ptr<Fact_Defi_String_Value<string>>>(tempFv)).get()->getValue())).insert(0, "\"").append("\"");
                        break;
                    }
                    case 4: // shared_ptr<Fact_Double_Value<double>>
                    {
                        ;
                        
                        tempS = String_Handler::toString(*((any_cast<shared_ptr<Fact_Double_Value<double>>>(tempFv)).get()->getValue().get()));
                        break;
                    }
                    case 5: // shared_ptr<Fact_Hash_Value<string>>
                    {
                        tempS = *((any_cast<shared_ptr<Fact_Hash_Value<string>>>(tempFv)).get()->getValue());
                        break;
                    }
                    case 6: // shared_ptr<Fact_Integer_Value<int>>
                    {
                        tempS = String_Handler::toString(*((any_cast<shared_ptr<Fact_Integer_Value<int>>>(tempFv)).get()->getValue().get()));
                        break;
                    }
                    case 7: // shared_ptr<Fact_URL_Value<string>>
                    {
                        tempS = *((any_cast<shared_ptr<Fact_URL_Value<string>>>(tempFv)).get()->getValue());
                        break;
                    }
                    case 8: // shared_ptr<Fact_UUID_Value<string>>
                    {
                        tempS = *((any_cast<shared_ptr<Fact_UUID_Value<string>>>(tempFv)).get()->getValue());
                        break;
                    }
                    
                    }

                tempScript = regex_replace(tempScript, regex(vectorItem), String_Handler::toString(tempS));
            }
        }
    }
    
    vector<string> dateStringList;
    
    for (sregex_iterator it = sregex_iterator(tempScript.begin(), tempScript.end(), datePattern);
         it != sregex_iterator(); it++)
    {
        match = *it;
        dateStringList.push_back(match.str(0));
    }
    
    // if dateStringList.size() == 0 then there is no string in date format
    script = tempScript;
    any returnValue;
    if(dateStringList.size() != 0) // case of date calculation
    {
        Date date1(dateStringList.at(0));
        Date date2(dateStringList.at(1));
        int diffDays = Date::daysDiffBetween(date1, date2);
        returnValue = Fact_Value<int>::parse(diffDays);
    }
    //        else // case of int or double calculation
    //        {
    //             don't need to do anything due to script itself can be evaluated as it is
    //        }
    
    any scriptResult = Script_Engine::evalStatement(script);
    
    //there is no function for outcome to be a date at the moment     E.g. The determination IS CALC (enrollment date + 5 days)
    if(scriptResult.type() == typeid(int))
    {
        int intScriptResult = any_cast<int>(scriptResult);
        returnValue = Fact_Value<int>::parse(intScriptResult);
    }
    else if(scriptResult.type() == typeid(double))
    {
        double doubleScriptResult = any_cast<double>(scriptResult);
        returnValue = Fact_Value<double>::parse(doubleScriptResult);
    }
    else if(scriptResult.type() == typeid(bool))
    {
        bool boolScriptResult = any_cast<bool>(scriptResult);
        returnValue = Fact_Value<bool>::parse(boolScriptResult);
    }
    else
    {
        string stringScriptResult = any_cast<string>(scriptResult);
        returnValue = Fact_Value<string>::parse(stringScriptResult);
    }
    
    return returnValue;
    }
