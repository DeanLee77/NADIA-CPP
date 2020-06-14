//
//  fact_uuid_value.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 23/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "fact_uuid_value.hpp"

template<>
Fact_UUID_Value<string>::Fact_UUID_Value()
{
    
}

template<>
Fact_UUID_Value<string>::Fact_UUID_Value(shared_ptr<Fact_UUID_Value<string>> const &fidvPtr)
{
    this->value = fidvPtr->getValue();
}

template<>
Fact_UUID_Value<string>::Fact_UUID_Value(string uuid) : value(make_shared<string>(uuid))
{
    
}

template<>
void Fact_UUID_Value<string>::setValue(string uuid)
{
    value = make_shared<string>(uuid);
}

template<>
shared_ptr<Fact_Value_Type> Fact_UUID_Value<string>::getFactValueType() {
    return make_shared<Fact_Value_Type>(Fact_Value_Type::UUID);
}

template<typename T>
shared_ptr<string> Fact_UUID_Value<T>::getValue()
{
    return value;
}
