//
//  metaline_test.cpp
//  Nadia-CPP
//
//  Created by Dean Lee on 23/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "metaline_test.hpp"
#include "string_handler.hpp"
#include "tokenizer.hpp"
#include "fact_string_value.hpp"
#include "fact_list_value.hpp"
#include "fact_boolean_value.hpp"
#include "fact_date_value.hpp"
#include "fact_defi_string_value.hpp"
#include "fact_double_value.hpp"
#include "fact_hash_value.hpp"
#include "fact_integer_value.hpp"
#include "fact_list_value.hpp"
#include "fact_url_value.hpp"
#include "fact_uuid_value.hpp"
#include "tokenizer.hpp"
#include "fact_value.hpp"
#include "date.hpp"

using namespace std;
bool Metaline_Testing::testing()
{
    bool returnValue = false;
    
    ifstream inFile("Metaline testing text.txt");
    stack<string> parentStack;
    unordered_map<string, shared_ptr<Node>> nodeMap;
    
    if(!inFile)
    {
        cout << "Metaline testing text.txt file cannot be read" << endl;
        exit(0);
    }
    else
    {
        string parent;
        string strLine;
        string textstring = "";
        int previousWhitespace = 0;
        
        while(getline(inFile, strLine))
        {
            int currentWhitespace = 0;
            string copyStrLine = strLine;
            string trimmedLine = String_Handler::stringTrim(copyStrLine);
            
            if(strLine.length() == trimmedLine.length())
            {
                while(!parentStack.empty())
                {
                    parentStack.pop();
                }
                parentStack.push(trimmedLine);
                handlingParent(trimmedLine, parentStack, nodeMap);
            }
            else
            {
                currentWhitespace = (int)(strLine.length() - trimmedLine.length());
                int indentationDifference = previousWhitespace - currentWhitespace;
                if (indentationDifference == 0 || indentationDifference > 0) //current line is at same level as previous line || current line is in upper level than previous line
                {
                    parentStack = HandlingStackPop(parentStack, indentationDifference);
                    
                }
                parent = parentStack.top();
                regex re("^(OR\\s?|AND\\s?)?(MANDATORY|OPTIONALLY|POSSIBLY)?(\\s?NOT|\\s?KNOWN)*(NEEDS|WANTS)?");
                string replacedLine = regex_replace(trimmedLine, re, "");
                replacedLine = String_Handler::stringTrim(replacedLine);
                
                string dependencyKeyword = regex_replace(trimmedLine, regex(replacedLine), "");
                parentStack.push(replacedLine);
                handlingChild(parent, trimmedLine, dependencyKeyword, parentStack, nodeMap);
                
            }
            previousWhitespace = currentWhitespace;
        }
    }
    
    unordered_map<string, shared_ptr<Node>>::iterator it = nodeMap.begin();
    
    for(; it != nodeMap.end(); it++)
    {
        cout << "node name: " << it->first << endl;
        any factValue = it->second.get()->getFactValue();
        const type_info &factValueType = factValue.type();
        if(factValueType == typeid(shared_ptr<Fact_List_Value<vector<any>>>))
        {
            shared_ptr<vector<any>> list = any_cast<shared_ptr<Fact_List_Value<vector<any>>>>(factValue).get()->getValue();
            for(auto item : *list)
            {
                const type_info& itemType = item.type();
                
                if(itemType == typeid(shared_ptr<Fact_Boolean_Value<bool>>))
                {
                    cout << "Fact Value in a list: " << *(any_cast<shared_ptr<Fact_Boolean_Value<bool>>>(item).get()->getValue())<< endl;
                }
                else if(itemType == typeid(shared_ptr<Fact_String_Value<string>>))
                {
                    cout << "Fact Value in a list: " << *(any_cast<shared_ptr<Fact_String_Value<string>>>(item).get()->getValue())<< endl;
                }
                else if(itemType == typeid(shared_ptr<Fact_Date_Value<Date>>))
                {
                    cout << "Fact Value in a list: " << any_cast<shared_ptr<Fact_Date_Value<Date>>>(item).get()->getValue()->getWholeDateValueInString() << endl;
                }
                else if(itemType == typeid(shared_ptr<Fact_Defi_String_Value<string>>))
                {
                    cout << "Fact Value in a list: " << *(any_cast<shared_ptr<Fact_Defi_String_Value<string>>>(item).get()->getValue())<< endl;
                }
                else if(itemType == typeid(shared_ptr<Fact_Double_Value<double>>))
                {
                    cout << "Fact Value in a list: " << *(any_cast<shared_ptr<Fact_Double_Value<double>>>(item).get()->getValue())<< endl;
                }
                else if(itemType == typeid(shared_ptr<Fact_Hash_Value<string>>))
                {
                    cout << "Fact Value in a list: " << *(any_cast<shared_ptr<Fact_Hash_Value<string>>>(item).get()->getValue())<< endl;
                }
                else if(itemType == typeid(shared_ptr<Fact_Integer_Value<int>>))
                {
                    cout << "Fact Value in a list: " << *(any_cast<shared_ptr<Fact_Integer_Value<int>>>(item).get()->getValue())<< endl;
                }
                else if(itemType == typeid(shared_ptr<Fact_URL_Value<string>>))
                {
                    cout << "Fact Value in a list: " << *(any_cast<shared_ptr<Fact_URL_Value<string>>>(item).get()->getValue())<< endl;
                }
                else if(itemType == typeid(shared_ptr<Fact_UUID_Value<string>>))
                {
                    cout << "Fact Value in a list: " << *(any_cast<shared_ptr<Fact_UUID_Value<string>>>(item).get()->getValue())<< endl;
                }
            }
        }
        else if(factValueType == typeid(shared_ptr<Fact_Boolean_Value<bool>>))
        {
            cout << "Fact Value: " << *(any_cast<shared_ptr<Fact_Boolean_Value<bool>>>(factValue).get()->getValue())<< endl;
        }
        else if(factValueType == typeid(shared_ptr<Fact_String_Value<string>>))
        {
            cout << "Fact Value : " << *(any_cast<shared_ptr<Fact_String_Value<string>>>(factValue).get()->getValue())<< endl;
        }
        else if(factValueType == typeid(shared_ptr<Fact_Date_Value<Date>>))
        {
            cout << "Fact Value: " << any_cast<shared_ptr<Fact_Date_Value<Date>>>(factValue).get()->getValue()->getWholeDateValueInString() << endl;
        }
        else if(factValueType == typeid(shared_ptr<Fact_Defi_String_Value<string>>))
        {
            cout << "Fact Value: " << *(any_cast<shared_ptr<Fact_Defi_String_Value<string>>>(factValue).get()->getValue())<< endl;
        }
        else if(factValueType == typeid(shared_ptr<Fact_Double_Value<double>>))
        {
            cout << "Fact Value: " << *(any_cast<shared_ptr<Fact_Double_Value<double>>>(factValue).get()->getValue())<< endl;
        }
        else if(factValueType == typeid(shared_ptr<Fact_Hash_Value<string>>))
        {
            cout << "Fact Value: " << *(any_cast<shared_ptr<Fact_Hash_Value<string>>>(factValue).get()->getValue())<< endl;
        }
        else if(factValueType == typeid(shared_ptr<Fact_Integer_Value<int>>))
        {
            cout << "Fact Value: " << *(any_cast<shared_ptr<Fact_Integer_Value<int>>>(factValue).get()->getValue())<< endl;
        }
        else if(factValueType == typeid(shared_ptr<Fact_URL_Value<string>>))
        {
            cout << "Fact Value: " << *(any_cast<shared_ptr<Fact_URL_Value<string>>>(factValue).get()->getValue())<< endl;
        }
        else if(factValueType == typeid(shared_ptr<Fact_UUID_Value<string>>))
        {
            cout << "Fact Value: " << *(any_cast<shared_ptr<Fact_UUID_Value<string>>>(factValue).get()->getValue())<< endl;
        }
    }
        
    return returnValue;
}


void Metaline_Testing::handlingParent(string trimmedLine, stack<string> parentStack, unordered_map<string, shared_ptr<Node>>& nodeMap)
{
    string copyTrimmedLine = trimmedLine;
    shared_ptr<Tokens> tokens = Tokenizer::getTokens(copyTrimmedLine);
    Metadata_Line ml(trimmedLine, tokens);
    shared_ptr<Node> data = make_shared<Metadata_Line>(trimmedLine, tokens);
    if(data.get()->getFactValue().type() ==  typeid(shared_ptr<Fact_String_Value<string>>) &&
       (any_cast<shared_ptr<Fact_String_Value<string>>>(data.get()->getFactValue()).get()->getValue()->compare("WARNING") == 0))
    {
        handleWarning(trimmedLine);
    }
    else
    {
        parentStack.push(trimmedLine);
        nodeMap[*data->getVariableName()] = data;
    }
    
}


void Metaline_Testing::handlingChild(string parentText, string childText, string dependencyKeyword, stack<string> parentStack, unordered_map<string, shared_ptr<Node>>& nodeMap)
{
    
    /*
     * the reason for using '*' at the last group of pattern within comparison is that
     * the last group contains No, Da, De, Ha, Url, Id.
     * In order to track more than one character within the square bracket of last group '*'(Matches 0 or more occurrences of the preceding expression) needs to be used.
     *
     */
    
    regex re("(.*)(AS LIST)");
    
    if(!regex_match(parentText, match, re))
    {
        handleWarning(childText);
        return;
    }
    
    childText = regex_replace(childText, regex("ITEM"), "", regex_constants::format_first_only);
    Meta_Type mt;
    if(regex_match(parentText, match, regex("^(INPUT)(.*)")))
    {
        mt = Meta_Type::INPUT;
    }
    else
    {
        mt = Meta_Type::FIXED;
    }
    
    handleListItem(parentText, childText, nodeMap);
    
}
void Metaline_Testing::handleListItem(string parentText, string childText, unordered_map<string, shared_ptr<Node>>& nodeMap)
{
    string copyChildText = childText;
    shared_ptr<Tokens> tokens = Tokenizer::getTokens(copyChildText);
    any factValue;
    if(tokens.get()->tokensString.get()->compare("Da") == 0)
    {
        Date date(childText);
        factValue = Fact_Value<Date>::parse(date);
    }
    else if(tokens.get()->tokensString.get()->compare("De") == 0)
    {
        double doubleInString = stod(childText);
        factValue = Fact_Value<double>::parse(doubleInString);
    }
    else if(tokens.get()->tokensString.get()->compare("No") == 0)
    {
        int intInString = stoi(childText);
        factValue = Fact_Value<int>::parse(intInString);
    }
    else if(tokens.get()->tokensString.get()->compare("Ha") == 0)
    {
        factValue = Fact_Value<string>::parse(childText);
    }
    else if(tokens.get()->tokensString.get()->compare("Url") == 0)
    {
        factValue = Fact_Value<string>::parse(childText);
    }
    else if(tokens.get()->tokensString.get()->compare("Id") == 0)
    {
        factValue = Fact_Value<string>::parse(childText);
    }
    else if(regex_match(childText, match, regex("[fF][aA][lL][sS][eE]"))|| regex_match(childText, match, regex("[tT][rR][uU][eE]")))
    {
        bool regexMatch = regex_match(childText, match, regex("[tT][rR][uU][eE]"));
        factValue = Fact_Value<bool>::parse(regexMatch);
    }
    else
    {
        factValue = Fact_Value<string>::parse(childText);
    }
    long index = parentText.find("AS");
    string parentVariable = parentText.substr(5, parentText.find("AS") - 5);
    string parentVariableTrimmed = String_Handler::stringTrim(parentVariable);
    
    any_cast<shared_ptr<Fact_List_Value<vector<any>>>>(nodeMap[parentVariableTrimmed]->getFactValue())->getValue()->push_back(factValue);
}
void Metaline_Testing::handleWarning(string trimmedLine)
{
    cout << trimmedLine << ": rule format is not matched. Please check the format again"<< endl;;
}

stack<string> Metaline_Testing::HandlingStackPop(stack<string> parentStack, int indentationDifference)
{
    for (int i = 0; i < indentationDifference + 1; i++)
    {
        parentStack.pop();
    }
    return parentStack;
}
