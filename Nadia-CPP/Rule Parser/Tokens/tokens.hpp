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
#include <memory>

using namespace std;
class Tokens
{
public:
    ~Tokens();
    const vector<shared_ptr<string>> tokensList;
    const vector<shared_ptr<string>> tokensStringList;
    const shared_ptr<string> tokensString;
    Tokens(vector<shared_ptr<string>> tl, vector<shared_ptr<string>> tsl, shared_ptr<string> ts);
};
#endif /* tokens_hpp */
