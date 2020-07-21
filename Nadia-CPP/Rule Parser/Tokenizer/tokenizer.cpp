//
//  tokenizer.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 5/5/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "tokenizer.hpp"
#include <cstring>

Tokenizer::Tokenizer()
{
    
    
}

regex Tokenizer::spaceRegex("^\\s+");
regex Tokenizer::iterateRegex("^(ITERATE:([\\s]*)LIST OF)(.*)");
regex Tokenizer::upperRegex("^([:'’,\\.A-Z_\\s]+(?![a-z]))");
regex Tokenizer::lowerRegex("^([[:lower:]-'’,\\.\\s]+(?!\\d))");
regex Tokenizer::mixedRegex("^([A-Z][a-z-'’,\\.\\s]+)+");
regex Tokenizer::operatorRegex("^([<>=]+)");
regex Tokenizer::calculationRegex("^(\\()([\\s|\\d+(?!/.)|\\w|\\W]*)(\\))");
regex Tokenizer::numberRegex("^(\\d+)(?!\\w|\\-|\\/|\\.|\\d)");
regex Tokenizer::decimalNumberRegex("^([\\d]+\\.\\d+)(?!\\d)");
regex Tokenizer::dateRegex("^([0-2]?[0-9]|3[0-1])/(0?[0-9]|1[0-2])/([0-9][0-9])?[0-9][0-9]|^([0-9][0-9])?[0-9][0-9]/(0?[0-9]|1[0-2])/([0-2]?[0-9]|3[0-1])");
regex Tokenizer::urlRegex("^(ht|f)tp[s*]?\\:([[:alnum:][:punct:]\\s])*$");
regex Tokenizer::guidRegex("^[0-9a-f]{8}-([0-9a-f]{4}-){3}[0-9a-f]{12}");
regex Tokenizer::hashRegex("^([-]?)([0-9a-fA-F]{10,}$)(?!\\-)");
regex Tokenizer::quotedRegex("^([\"\\“])(.*)([\"\\”])(\\.)*");

/*
 * the order of Pattern in the array of 'matchPatterns' is extremely important because some patterns won't work if other patterns are invoked earlier than them
 * especially 'I' pattern. 'I' pattern must come before 'U' pattern, 'Url' pattern must come before 'L' pattern with current patterns.
 */
regex Tokenizer::matchPatterns[] = { spaceRegex, quotedRegex, iterateRegex, mixedRegex, upperRegex, urlRegex, operatorRegex, calculationRegex, numberRegex, hashRegex, decimalNumberRegex, dateRegex, guidRegex, lowerRegex };
string Tokenizer::tokenType[] = { "S", "Q", "I", "M", "U", "Url", "O", "C", "No", "Ha", "De", "Da", "Id", "L" };
map<string, int> Tokenizer::tokenTypeMap = {{"S", 0}, {"Q", 1}, {"I", 2}, {"M", 3}, {"U", 4}, {"Url", 5}, {"O", 6}, {"C", 7}, {"No", 8},  {"Ha", 9},{"De", 10}, {"Da", 11}, {"Id", 12}, {"L", 13}};

shared_ptr<Tokens> Tokenizer::getTokens(string& text)
{
    vector<shared_ptr<string>> tokenStringList /* = vector<shared_ptr<string>>()*/;
    vector<shared_ptr<string>> tokenList /*= vector<shared_ptr<string>>();*/;
    string iniTokenString = "";
    shared_ptr<string> tokenString = make_shared<string>(iniTokenString);
    
    int textLength = (int)text.length();
    
    int matchPatternsLength = sizeof(matchPatterns)/sizeof(matchPatterns[0]);
    
    while (textLength != 0)
    {
        
        for (int i = 0; i < matchPatternsLength; i++)
        {
            regex regexPattern = matchPatterns[i];
            
            smatch match;
            bool matched = regex_search(text, match, regexPattern);
            
            if(matched == true)
            {
                string group = match[0].str();
                
                // ignore space tokens
                if (tokenType[i].compare("S") != 0)
                {
                    tokenStringList.push_back(make_shared<string>(tokenType[i]));
                    tokenList.push_back(make_shared<string>(String_Handler::stringTrim(group)));
                    *tokenString.get() += tokenType[i];
                }
                
                string subStr =text.substr(group.length());
                text = String_Handler::stringTrim(subStr);
                textLength = (int)text.length();
                break;
            }
            if (i >= matchPatternsLength - 1)
            {
                textLength = 0;
                *tokenString.get() = "WARNING";
            }
        }
        
    }
    
    auto tokens = make_shared<Tokens>(tokenList, tokenStringList, tokenString);
    return tokens;
    
}

shared_ptr<int> Tokenizer::getTokenTypeIndex(string& token)
{
    return make_shared<int>(Tokenizer::tokenTypeMap.find(token)->second);
}
