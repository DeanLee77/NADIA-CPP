//
//  comparison_line.hpp
//  Nadia-CPP
//
//  Created by Dean Lee on 21/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef comparison_line_hpp
#define comparison_line_hpp

#include <stdio.h>
#include <algorithm>
//#include <iterator>

#include "node.hpp"

using namespace std;


class Comparison_Line : public Node
{
    static Line_Type lineType;
    string operatorString;
    string lhs;
    any rhs;
    
public:
    Comparison_Line(string& childText, shared_ptr<Tokens> tokens);
    void initialisation(string& childText, shared_ptr<Tokens> tokens) override;
    string* getLHS();
    any getRHS();
    Line_Type* getLineType() override;
    any selfEvaluate(unordered_map<string, any>& workingMemory) override;
};
#endif /* comparison_line_hpp */
