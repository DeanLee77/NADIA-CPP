//
//  metadata_line.cpp
//  Nadia-CPP
//
//  Created by Dean Lee on 18/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "metadata_line.hpp"
#include "fact_list_value.hpp"
#include "date.hpp"
//inline smatch match;

Line_Type Metadata_Line::lineType = Line_Type::META;
Metadata_Line::Metadata_Line(string& parentText, shared_ptr<Tokens> tokens) : Node(parentText, tokens)
{
    initialisation(parentText, tokens);
}

void Metadata_Line::initialisation(string& parentText, shared_ptr<Tokens> tokens)
{
    this->nodeName = parentText;
    setMetaType(parentText);
    
    regex metaPattern;
    
    if(metaType == Meta_Type::FIXED)
    {
        metaPattern = regex("^(FIXED)(.*)(\\s+(AS|IS)\\s+.*)");
        if(regex_match(parentText, match, metaPattern))
        {
            string variableName = match.str(2);
            this->variableName = String_Handler::stringTrim(variableName);
            
            string valueInString = match.str(3);
            string trimmedValueInString = String_Handler::stringTrim(valueInString);
            setValue(trimmedValueInString, tokens);
        }
    }
    else if(metaType == Meta_Type::INPUT)
    {
        metaPattern = regex("^(INPUT)(.*)(AS)(.*)[(IS)(.*)]?");
        if(regex_match(parentText, match, metaPattern))
        {
            string variableName = match.str(2);
            this->variableName = String_Handler::stringTrim(variableName);

            string valueInString = match.str(4);
            string trimmedValueInString = String_Handler::stringTrim(valueInString);
            setValue(trimmedValueInString, tokens);
        }
    }
}


void Metadata_Line::setValue(string& valueInString, shared_ptr<Tokens> tokens)
{
    int tokenStringListSize = (int)tokens.get()->tokensStringList.size();
    string lastTokenString = *(const_cast<vector<shared_ptr<string>>&>(tokens.get()->tokensStringList).at(tokenStringListSize - 1).get());
    char delimiter = ' ';
    
    vector<string> tempVector = String_Handler::stringSplit(valueInString, delimiter);
    string tempStr = tempVector.at(0);
    
    if(metaType == Meta_Type::FIXED)
    {
        string tempValue = tempVector.size()>2? const_cast<string&>(*tokens->tokensList.at(tokens->tokensList.size() - 1)) :tempVector.at(1);
        
        if(tempStr.compare("IS") == 0)
        {
            if(this->isDate(lastTokenString))
            {
                Date factValueInDate(tempValue);
                this->value = Fact_Value<Date>::parse(factValueInDate);
            }
            else if(this->isDouble(lastTokenString))
            {
                double tempDouble = stod(tempValue);
                this->value = Fact_Value<double>::parse(tempDouble);
            }
            else if(this->isInteger(lastTokenString))
            {
                int tempInt = stoi(tempValue);
                this->value = Fact_Value<int>::parse(tempInt);
            }
            else if(this->isBoolean(tempValue))
            {
                bool factValue = !regex_match(tempValue, match, regex("[fF][aA][lL][sS][eE]"));
                this->value = Fact_Value<bool>::parse(factValue);
            }
            else if(this->isHash(lastTokenString))
            {
                this->value = Fact_Value<string>::parseHash(tempValue);
            }
            else if(this->isURL(lastTokenString))
            {
                this->value = Fact_Value<string>::parseURL(tempValue);
            }
            else if(this->isUUID(lastTokenString))
            {
                this->value = Fact_Value<string>::parseUUID(tempValue);
            }
            else if(this->isQuoted(lastTokenString))
            {
                this->value = Fact_Value<string>::parseDefiString(tempValue);
            }
            else
            {
                this->value = Fact_Value<string>::parse(tempValue);
            }
        }
        else if(tempStr.compare("AS") == 0)
        {
            if(tempValue.compare("LIST") == 0)
            {
                vector<any> listValue;
                this->value = Fact_Value<vector<any>>::parse(listValue);
            }
            else
            {
                string warningMessage = "WARNING";
                this->value = Fact_Value<string>::parse(warningMessage);
            }
        }
    }
    else if(metaType == Meta_Type::INPUT)
    {
        if(tempVector.size() > 1)
        {
            
            /*
             * within this case 'DefaultValue' will be set due to the statement format is as follows;
             * 'A AS 'TEXT' IS B'
             * and 'A' is variable, 'TEXT' is a type of variable, and 'B' is a default value.
             * if the type is 'LIST' then variable is a list then the factValue has a default value.
             */
            string tempStr2 = tempVector.at(2);
            
            if(factValueTypeMap.find(Fact_Value_Type::LIST)->second.compare(tempStr) == 0)
            {
                vector<any> valueList;
                any tempValue;
                if(this->isDate(lastTokenString))
                {
                    Date factValueInDate(tempStr2);
                    tempValue = Fact_Value<Date>::parse(factValueInDate);
                }
                else if(this->isDouble(lastTokenString))
                {
                    double tempDouble = stod(tempStr2);
                    tempValue = Fact_Value<double>::parse(tempDouble);
                }
                else if(this->isInteger(lastTokenString))
                {
                    int tempInt = stoi(tempStr2);
                    tempValue = Fact_Value<int>::parse(tempInt);
                }
                else if(this->isHash(lastTokenString))
                {
                    tempValue = Fact_Value<string>::parseHash(tempStr2);
                }
                else if(this->isURL(lastTokenString))
                {
                    tempValue = Fact_Value<string>::parseURL(tempStr2);
                }
                else if(this->isUUID(lastTokenString))
                {
                    tempValue = Fact_Value<string>::parseUUID(tempStr2);
                }
                else if (this->isBoolean(tempStr2))
                {
                    bool factValue = !regex_match(tempStr2, match, regex("[fF][aA][lL][sS][eE]"));
                    tempValue = Fact_Value<bool>::parse(factValue);
                }
                else
                {
                    tempValue = Fact_Value<string>::parse(tempStr2);
                }
                
                valueList.push_back(tempValue);
                shared_ptr<Fact_List_Value<vector<any>>> factValueList = Fact_Value<vector<any>>::parse(valueList);
                factValueList.get()->setDefaultValue(make_shared<any>(tempValue));
                
                this->value = factValueList;
            }
            else if(factValueTypeMap.find(Fact_Value_Type::TEXT)->second.compare(tempStr) == 0)
            {
                this->value = Fact_Value<string>::parse(tempStr2);
            }
            else if(factValueTypeMap.find(Fact_Value_Type::DATE)->second.compare(tempStr) == 0)
            {
                Date factValueInDate(tempStr2);
                this->value = Fact_Value<Date>::parse(factValueInDate);
            }
            else if(factValueTypeMap.find(Fact_Value_Type::NUMBER)->second.compare(tempStr) == 0)
            {
                int factValueInInteger = stoi(tempStr2);
                this->value = Fact_Value<int>::parse(factValueInInteger);
            }
            else if(factValueTypeMap.find(Fact_Value_Type::DECIMAL)->second.compare(tempStr) == 0)
            {
                double factValueInDouble = stod(tempStr2);
                this->value = Fact_Value<double>::parse(factValueInDouble);
            }
            else if(factValueTypeMap.find(Fact_Value_Type::BOOLEAN)->second.compare(tempStr) == 0)
            {
                bool factValue = !regex_match(tempStr2, match, regex("[fF][aA][lL][sS][eE]"));
                this->value = Fact_Value<bool>::parse(factValue);
            }
            else if(factValueTypeMap.find(Fact_Value_Type::URL)->second.compare(tempStr) == 0)
            {
               this->value = Fact_Value<string>::parseURL(tempStr2);
            }
            else if(factValueTypeMap.find(Fact_Value_Type::HASH)->second.compare(tempStr) == 0)
            {
                this->value = Fact_Value<string>::parseHash(tempStr2);
            }
            else if(factValueTypeMap.find(Fact_Value_Type::UUID)->second.compare(tempStr) == 0)
            {
                this->value = Fact_Value<string>::parseUUID(tempStr2);
            }
        }
        else
        {
            /*
             * case of the statement does not have value, only contains a type of the variable
             * so that the value will not have any default values
             */
            if(factValueTypeMap.find(Fact_Value_Type::LIST)->second.compare(tempStr) == 0)
            {
                vector<any> newList;
                this->value = Fact_Value<vector<any>>::parse(newList);
            }
            else if(factValueTypeMap.find(Fact_Value_Type::TEXT)->second.compare(tempStr) == 0 ||
                    factValueTypeMap.find(Fact_Value_Type::URL)->second.compare(tempStr) == 0 ||
                    factValueTypeMap.find(Fact_Value_Type::HASH)->second.compare(tempStr) == 0 ||
                    factValueTypeMap.find(Fact_Value_Type::UUID)->second.compare(tempStr) == 0)
            {
                string emptyString;
                this->value = Fact_Value<string>::parse(emptyString);
            }
            else if(factValueTypeMap.find(Fact_Value_Type::DATE)->second.compare(tempStr) == 0)
            {
                Date newDate;
                this->value = Fact_Value<Date>::parse(newDate);
            }
            else if(factValueTypeMap.find(Fact_Value_Type::NUMBER)->second.compare(tempStr) == 0)
            {
                optional<int> intOp(-111111);
                this->value = Fact_Value<int>::parse(intOp.value());
            }
            else if(factValueTypeMap.find(Fact_Value_Type::DECIMAL)->second.compare(tempStr) == 0)
            {
                optional<double> doubleOp(-0.11111);
                this->value = Fact_Value<double>::parse(doubleOp.value());
            }
            else if(factValueTypeMap.find(Fact_Value_Type::BOOLEAN)->second.compare(tempStr) == 0)
            {
                optional<bool> boolOp(true);
                this->value = Fact_Value<bool>::parse(boolOp.value());
            }
        }
    }
}


void Metadata_Line::setMetaType(string& parentText)
{
    for(auto const& [key, value]: metaTypeMap)
    {
        if(regex_search(parentText, match, regex(value)))
        {
            this->metaType = key;
            break;
        }
    }
}


Meta_Type* Metadata_Line::getMetaType()
{
    return &(this->metaType);
}

Line_Type* Metadata_Line::getLineType()
{
    return &lineType;
}



//this function is supposed to return Fact_Value
any Metadata_Line::selfEvaluate(unordered_map<string, any>& workingMemory)
{
    optional<string> stringOp;
    return Fact_Value<string>::parse(stringOp.value());
}
