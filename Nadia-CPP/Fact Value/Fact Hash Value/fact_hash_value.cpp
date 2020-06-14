//
//  fact_hash_value.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 23/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "fact_hash_value.hpp"

template<>
Fact_Hash_Value<string>::Fact_Hash_Value()
{
    
}

template<>
Fact_Hash_Value<string>::Fact_Hash_Value(shared_ptr<Fact_Hash_Value<string>> fhvPtr)
{
    this->value = fhvPtr->getValue();
}

template<>
Fact_Hash_Value<string>::Fact_Hash_Value(string hash) : value(make_shared<string>(hash))
{
    
}

template<>
void Fact_Hash_Value<string>::setValue(string hash)
{
    value = make_shared<string>(hash);
}

template<>
shared_ptr<Fact_Value_Type> Fact_Hash_Value<string>::getFactValueType()
{
    return make_shared<Fact_Value_Type>(Fact_Value_Type::HASH);
}

template<typename T>
shared_ptr<string> Fact_Hash_Value<T>::getValue()
{
    return value;
}
