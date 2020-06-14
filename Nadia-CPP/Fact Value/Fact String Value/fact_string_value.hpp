//
//  fact_string_value.hpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 22/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef fact_string_value_hpp
#define fact_string_value_hpp

#include "fact_value.hpp"

template<typename T>
class Fact_String_Value : public Fact_Value<T>
{
public:
    Fact_String_Value();
    Fact_String_Value(shared_ptr<Fact_String_Value<string>> const &fsvPtr);
    Fact_String_Value(string str);
    void setValue(string str) override;
    shared_ptr<Fact_Value_Type> getFactValueType() override;
    shared_ptr<string> getValue() override;
    
private:
    shared_ptr<string> value;
};

#endif /* fact_string_value_hpp */
