//
//  tokens.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 6/5/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "tokens.hpp"

Tokens::Tokens(vector<shared_ptr<string>> tl, vector<shared_ptr<string>> tsl, shared_ptr<string> ts) : tokensList(tl), tokensStringList(tsl), tokensString(ts)
{
    
}

Tokens::~Tokens()
{
    vector<shared_ptr<string>>().swap(const_cast<vector<shared_ptr<string>>&>(this->tokensList));
    vector<shared_ptr<string>>().swap(const_cast<vector<shared_ptr<string>>&>(this->tokensStringList));
}
