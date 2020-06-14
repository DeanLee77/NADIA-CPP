//
//  fact_integer_value.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 23/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "fact_integer_value.hpp"

template<>
Fact_Integer_Value<int>::Fact_Integer_Value()
{
    
}

template<>
Fact_Integer_Value<int>::Fact_Integer_Value(shared_ptr<Fact_Integer_Value<int>> const &fivPtr)
{
    this->value = fivPtr->getValue();
}

template<>
Fact_Integer_Value<int>::Fact_Integer_Value(int intValue) : value(make_shared<int>(intValue))
{
//    setValue(intValue);
}

template<>
void Fact_Integer_Value<int>::setValue(int intValue)
{
    value = make_shared<int>(intValue);
}

template<>
shared_ptr<Fact_Value_Type> Fact_Integer_Value<int>::getFactValueType()
{
    return make_shared<Fact_Value_Type>(Fact_Value_Type::INTEGER);
}

template<typename T>
shared_ptr<int> Fact_Integer_Value<T>::getValue()
{
    return value;
}
