//
//  fact_defi_string_value.hpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 23/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef fact_defi_string_value_hpp
#define fact_defi_string_value_hpp

#include <regex>
#include "fact_value.hpp"

template<typename T>
class Fact_Defi_String_Value : public Fact_Value<T>
{
private:
    shared_ptr<string> value;
    
public:
    Fact_Defi_String_Value();
    Fact_Defi_String_Value(shared_ptr<Fact_Defi_String_Value<string>> const &fdsvPtr );
    Fact_Defi_String_Value(string s);
    void setValue(string s) override;
    shared_ptr<Fact_Value_Type>  getFactValueType() override;
    shared_ptr<string> getValue() override;

};    

#endif /* fact_defi_string_value_hpp */
