//
//  value_conclusion_line.hpp
//  Nadia-CPP
//
//  Created by Dean Lee on 18/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef value_conclusion_line_hpp
#define value_conclusion_line_hpp

#include <stdio.h>

#include "node.hpp"
#include "fact_value.hpp"

using namespace std;

class Value_Conclusion_Line : public Node
{
    static Line_Type lineType;
    bool isPlainStatementFormat;
    bool anyMatchVariable(string& variableName, vector<any>& factList);
    bool anyMatchVariable(any variableValueFromWorkingMemory, vector<any>& factList);
    /*
     * ValueConclusionLine format is as follows;
     *  1. 'A-statement IS B-statement';
     *  2. 'A-item name IS IN LIST: B-list name'; or
     *  3. 'A-statement'(plain statement line) including statement of 'A' type from a child node of ExprConclusionLine type which are 'NEEDS' and 'WANTS'.
     * When the inference engine reaches at a ValueConclusionLine and needs to ask a question to a user,
     * this rule must be either 'A (plain statement)' or 'A IS B' format due to the reason that other than the two format cannot be a parent rule.
     * Hence, the question can be from either variableName or ruleName, and a result of the question will be inserted into the workingMemory.
     * However, when the engine reaches at the line during forward-chaining then the key for the workingMemory will be a ruleName,
     * and value for the workingMemory will be set as a result of propagation.
     *
     * If the rule statement is in a format of 'A-statement' then a default value of variable 'value' will be set as 'false'
     *
     */
public:
    Value_Conclusion_Line(string& nodeText, shared_ptr<Tokens> tokens);
    void initialisation(string& nodeText, shared_ptr<Tokens> tokens) override; 
    bool* getIsPlainStatementFormat();
    Line_Type* getLineType() override;
    any selfEvaluate(unordered_map<string, any>& workingMemory) override;
};
#endif /* value_conclusion_line_hpp */
