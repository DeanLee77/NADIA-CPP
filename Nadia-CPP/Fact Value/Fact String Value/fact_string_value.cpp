//
//  fact_string_value.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 22/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "fact_string_value.hpp"

template<>
Fact_String_Value<string>::Fact_String_Value()
{}

template<>
Fact_String_Value<string>::Fact_String_Value(shared_ptr<Fact_String_Value<string>> const &fsvPtr)
{
    this->value = fsvPtr->getValue();
}

template<>
Fact_String_Value<string>::Fact_String_Value(string str) : value(make_shared<string>(str))
{
    
}

template<>
void Fact_String_Value<string>::setValue(string str)
{
    value = make_shared<string>(str);
}

template<>
shared_ptr<Fact_Value_Type> Fact_String_Value<string>::getFactValueType()
{
    return make_shared<Fact_Value_Type>(Fact_Value_Type::STRING);
}

template<typename T>
shared_ptr<string> Fact_String_Value<T>::getValue()
{
    return value;
}
