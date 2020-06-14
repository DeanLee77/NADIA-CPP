//
//  tokens.hpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 6/5/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef tokens_hpp
#define tokens_hpp

#include <vector>
#include <string>

using namespace std;
class Tokens
{
public:
    vector<string> tokensList;
    vector<string> tokensStringList;
    string tokensString;
    Tokens(vector<string> tl, vector<string> tsl, string ts);
};
#endif /* tokens_hpp */
