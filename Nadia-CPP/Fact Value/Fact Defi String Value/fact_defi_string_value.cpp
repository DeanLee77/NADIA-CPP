//
//  fact_defi_string_value.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 23/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "fact_defi_string_value.hpp"

template<>
Fact_Defi_String_Value<string>::Fact_Defi_String_Value()
{
    
}

template<>
Fact_Defi_String_Value<string>::Fact_Defi_String_Value(shared_ptr<Fact_Defi_String_Value<string>> const &fdsvPtr )
{
    this->value = fdsvPtr->getValue();
}

template<>
Fact_Defi_String_Value<string>::Fact_Defi_String_Value(string s)
{
    regex re("^([\"\\“])(.*)([\"\\”])(\\.)*");
    smatch match;
    bool matched = regex_match(s, match, re);
    if(matched == true)
    {
        setValue(match.str(2));
    }
}

template<typename T>
void Fact_Defi_String_Value<T>::setValue(string s)
{
    value = make_shared<string>(s);
}

template<>
shared_ptr<Fact_Value_Type> Fact_Defi_String_Value<string>::getFactValueType()
{
    return make_shared<Fact_Value_Type>(Fact_Value_Type::DEFI_STRING);
}

template<typename T>
shared_ptr<string> Fact_Defi_String_Value<T>::getValue()
{
    return value;
}
