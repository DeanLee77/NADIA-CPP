//
//  metadata_line.hpp
//  Nadia-CPP
//
//  Created by Dean Lee on 18/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef metadata_line_hpp
#define metadata_line_hpp

#include <stdio.h>

#include "node.hpp"

namespace MetaType {
    enum Meta_Type{
        LINE, FIXED, INPUT, ITEM, GOAL, CLICK_LINK, SOP_DOC
    };
    
    inline unordered_map<Meta_Type, string> metaTypeMap{{Meta_Type::LINE, "LINE"}, {Meta_Type::FIXED, "FIXED"}, {Meta_Type::INPUT, "INPUT"}, {Meta_Type::ITEM, "ITEM"}, {Meta_Type::GOAL, "GOAL"}, {Meta_Type::CLICK_LINK, "CLICK_LINK"}, {Meta_Type::SOP_DOC, "SOP_DOC"}};
}

using namespace std;
using namespace MetaType;

class Metadata_Line : public Node
{
    
    //    Pattern metaPatternMatcher = Pattern.compile("^ULU?[OU]?[NoDaMLDe]?");
    /*
     * Meta type pattern list
     * 1. ULU[NoDaMLDe]
     * 2. U[NoDaMLDe]
     * 3. U
     */
    Meta_Type metaType;
    static Line_Type lineType;
    
public:
    Metadata_Line(string& parentText, shared_ptr<Tokens> tokens);
    
    void initialisation(string& parentText, shared_ptr<Tokens> tokens) override;
    void setValue(string& valueInString, shared_ptr<Tokens> tokens);
    void setMetaType(string& parentText);    
    Meta_Type* getMetaType();
    Line_Type* getLineType() override;
   
    any selfEvaluate(unordered_map<string, any>& workingMemory) override;
};

#endif /* metadata_line_hpp */
