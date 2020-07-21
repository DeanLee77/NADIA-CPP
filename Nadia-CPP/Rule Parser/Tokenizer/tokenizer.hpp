//
//  tokenizer.hpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 5/5/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef tokenizer_hpp
#define tokenizer_hpp

#include <regex>
#include <map>

#include "tokens.hpp"
#include "string_handler.hpp"

class Tokenizer
{
    static regex spaceRegex;
    static regex iterateRegex;
    static regex upperRegex;
    static regex lowerRegex;
    static regex mixedRegex;
    static regex operatorRegex;
    static regex calculationRegex;
    static regex numberRegex;
    static regex decimalNumberRegex;
    static regex dateRegex;
    static regex urlRegex;
    static regex guidRegex;
    static regex hashRegex;
    static regex quotedRegex;
    /*
     * the order of Pattern in the array of 'matchPatterns' is extremely important because some patterns won't work if other patterns are invoked earlier than them
     * especially 'I' pattern. 'I' pattern must come before 'U' pattern, 'Url' pattern must come before 'L' pattern with current patterns.
     */
    static regex matchPatterns[];
    static string tokenType[];
    static map<string, int> tokenTypeMap;
public:
    Tokenizer();
    static shared_ptr<Tokens> getTokens(string& text);
    static shared_ptr<int> getTokenTypeIndex(string& token);
};

#endif /* tokenizer_hpp */
