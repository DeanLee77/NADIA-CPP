//
//  value_conclusion_line.cpp
//  Nadia-CPP
//
//  Created by Dean Lee on 18/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "value_conclusion_line.hpp"
#include "fact_value.hpp"
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

Line_Type Value_Conclusion_Line::lineType = Line_Type::VALUE_CONCLUSION;

Value_Conclusion_Line::Value_Conclusion_Line(string& nodeText, shared_ptr<Tokens> tokens) : Node(nodeText, tokens)
{
    initialisation(nodeText, tokens);
}

void Value_Conclusion_Line::initialisation(string& nodeText, shared_ptr<Tokens> tokens)
{
    int tokensStringListSize = (int)tokens.get()->tokensStringList.size(); //tokens.tokensStringList.size is same as tokens.tokensList.size
    
    for(auto token : tokens.get()->tokensList)
    {
        if(!regex_search(*token.get(), match, regex("IS"))) //this will exclude 'IS' and 'IS IN  LIST:' within the given 'tokens'
       {
           isPlainStatementFormat = true;
       }
    }
    
    string lastToken;
    if(!isPlainStatementFormat) //the line must be a parent line in this case other than a case of the rule contains 'IS IN LIST:'
    {
        string toBeTrimmed = nodeText.substr(0, nodeText.find("IS") - 1);
        this->variableName = String_Handler::stringTrim(toBeTrimmed);
        
        lastToken = *(tokens.get()->tokensList.at(tokensStringListSize - 1).get());
    }
    else //this is a case of that the line is in a 'A-statement' format
    {
        
        this->variableName = nodeText;
        lastToken = "false";
        
    }
    
    this->nodeName = nodeText;
    string lastTokenString = *(const_cast<vector<shared_ptr<string>>&>(tokens.get()->tokensStringList).at(tokensStringListSize-1).get());
    
    this->setValue(lastTokenString, lastToken);
}


bool* Value_Conclusion_Line::getIsPlainStatementFormat()
{
    return &isPlainStatementFormat;
}


Line_Type* Value_Conclusion_Line::getLineType()
{
    return &lineType;
}


bool Value_Conclusion_Line::anyMatchVariable(string& variableName, vector<any>& factList)
{
    bool returnValue = false;
    for(any item : factList)
    {
        if(item.type() == typeid(shared_ptr<Fact_String_Value<string>>))
        {
            returnValue = variableName.compare(*(any_cast<shared_ptr<Fact_String_Value<string>>>(item).get()->getValue().get())) == 0;
            
        }
        else if(item.type() == typeid(shared_ptr<Fact_Defi_String_Value<string>>))
        {
            returnValue = variableName.compare(*(any_cast<shared_ptr<Fact_Defi_String_Value<string>>>(item).get()->getValue().get())) == 0;
        }
    }
    
    return returnValue;
}


bool Value_Conclusion_Line::anyMatchVariable(any variableValueFromWorkingMemory, vector<any>& factList)
{
    bool returnValue = false;
    const type_info& variablevalueFromWorkingMemoryType = variableValueFromWorkingMemory.type();
    vector<any>::iterator it = factList.begin();
    for( ; it != factList.end(); it++)
    {
        if((*it).type() == variablevalueFromWorkingMemoryType)
        {
            switch(typeIndexMap[variablevalueFromWorkingMemoryType])
            {
                case 0:
                {
                    
                    returnValue = *(any_cast<shared_ptr<Fact_Boolean_Value<bool>>>(variableValueFromWorkingMemory).get()->getValue().get()) == *(any_cast<shared_ptr<Fact_Boolean_Value<bool>>>(*it).get()->getValue().get());
                    it = factList.end();
                    break;
                }
                case 1:
                {
                    returnValue = (*(any_cast<shared_ptr<Fact_String_Value<string>>>(variableValueFromWorkingMemory).get()->getValue().get())).compare((*(any_cast<shared_ptr<Fact_String_Value<string>>>(*it).get()->getValue().get()))) == 0;
                    it = factList.end();
                    break;
                }
                case 2:
                {
                    returnValue = (*(any_cast<shared_ptr<Fact_Date_Value<Date>>>(variableValueFromWorkingMemory).get()->getValue().get())).isEqual((*(any_cast<shared_ptr<Fact_Date_Value<Date>>>(*it).get()->getValue().get())));
                    it = factList.end();
                    break;
                }
                case 3:
                {
                    returnValue = (*(any_cast<shared_ptr<Fact_Defi_String_Value<string>>>(variableValueFromWorkingMemory).get()->getValue().get())).compare((*(any_cast<shared_ptr<Fact_Defi_String_Value<string>>>(*it).get()->getValue().get()))) == 0;
                    it = factList.end();
                    break;
                }
                case 4:
                {
                    returnValue = (*(any_cast<shared_ptr<Fact_Double_Value<double>>>(variableValueFromWorkingMemory).get()->getValue().get())) == ((*(any_cast<shared_ptr<Fact_Double_Value<double>>>(*it).get()->getValue().get())));
                    it = factList.end();
                    break;
                }
                case 5:
                {
                    returnValue = (*(any_cast<shared_ptr<Fact_Hash_Value<string>>>(variableValueFromWorkingMemory).get()->getValue().get())).compare((*(any_cast<shared_ptr<Fact_Hash_Value<string>>>(*it).get()->getValue().get()))) == 0;
                    it = factList.end();
                    break;
                }
                case 6:
                {
                    returnValue = (*(any_cast<shared_ptr<Fact_Integer_Value<int>>>(variableValueFromWorkingMemory).get()->getValue().get())) == ((*(any_cast<shared_ptr<Fact_Integer_Value<int>>>(*it).get()->getValue().get())));
                    it = factList.end();
                    break;
                }
                case 7:
                {
                    returnValue = (*(any_cast<shared_ptr<Fact_URL_Value<string>>>(variableValueFromWorkingMemory).get()->getValue().get())).compare((*(any_cast<shared_ptr<Fact_URL_Value<string>>>(*it).get()->getValue().get()))) == 0;
                    it = factList.end();
                    break;
                }
                case 8:
                {
                    returnValue = (*(any_cast<shared_ptr<Fact_UUID_Value<string>>>(variableValueFromWorkingMemory).get()->getValue().get())).compare((*(any_cast<shared_ptr<Fact_UUID_Value<string>>>(*it).get()->getValue().get()))) == 0;
                    it = factList.end();
                    break;
                }
            }
        }
    }
    
    return returnValue;
}


any Value_Conclusion_Line::selfEvaluate(unordered_map<string, any>& workingMemory)
{
    any fv;
    /*
     * Negation and Known type are a part of dependency
     * hence, only checking its variableName value against the workingMemory is necessary.
     * type is as follows;
     *    1. the rule is a plain statement
     *    2. the rule is a statement of 'A IS B'
     *    3. the rule is a statement of 'A IS IN LIST: B'
     *    4. the rule is a statement of 'needs(wants) A'. this is from a child node of ExprConclusionLine type
     */
    
    if(!isPlainStatementFormat)
    {        
        vector<shared_ptr<string>>::iterator it = const_cast<vector<shared_ptr<string>>&>(this->tokens.get()->tokensList).begin();
        
        for(; it != (this->tokens).get()->tokensList.end() ; it++)
        {
            if((*it->get()).compare("IS") == 0)
            {
                fv = this->value;
                it = const_cast<vector<shared_ptr<string>>&>(this->tokens.get()->tokensList).end();
            }
            else if((*it->get()).compare("IS IN LIST:") == 0)
            {
                string listName = *(any_cast<shared_ptr<Fact_String_Value<string>>>(this->getFactValue()).get()->getValue().get());

                if((workingMemory[listName]).has_value())
                {
                    vector<any> factList = *((any_cast<shared_ptr<Fact_List_Value<vector<any>>>>(workingMemory[listName])).get()->getValue().get());
                    
                    any variableValueFromWorkingMemory = workingMemory[*(this->getVariableName())];

                    if(variableValueFromWorkingMemory.has_value()) //variable has a value
                    {
                        fv = anyMatchVariable(variableValueFromWorkingMemory, factList);
                    }
                    else // variable does NOT have a value
                    {
                        fv = anyMatchVariable(this->variableName, factList);
                    }
                }
            
                it = const_cast<vector<shared_ptr<string>>&>(this->tokens.get()->tokensList).end();
            }
        }
    }
    return fv;
}
