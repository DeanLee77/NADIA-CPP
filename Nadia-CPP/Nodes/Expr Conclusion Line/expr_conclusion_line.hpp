//
//  expr_conclusion_line.hpp
//  Nadia-CPP
//
//  Created by Dean Lee on 22/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef expr_conclusion_line_hpp
#define expr_conclusion_line_hpp

#include <stdio.h>

#include "node.hpp"

using namespace std;

class Expr_Conclusion_Line : public Node
{
    static Line_Type lineType;
    any equation;
    
public:
    Expr_Conclusion_Line(string& parentText, shared_ptr<Tokens> tokens);
    void initialisation(string& parentText, shared_ptr<Tokens> tokens) override;
    any getEquation();
    void setEquation(any newEquation);
    Line_Type* getLineType() override;
    any selfEvaluate(unordered_map<string , any>& workingMemory) override;
};
#endif /* expr_conclusion_line_hpp */
