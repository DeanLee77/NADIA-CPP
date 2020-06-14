//
//  fact_boolean_value.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 21/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "fact_boolean_value.hpp"

template<>
Fact_Boolean_Value<bool>::Fact_Boolean_Value()
{}

template<>
Fact_Boolean_Value<bool>::Fact_Boolean_Value(shared_ptr<Fact_Boolean_Value<bool>> const &fbvPtr)
{
    this->value = fbvPtr->getValue();
}

template<>
Fact_Boolean_Value<bool>::Fact_Boolean_Value(bool booleanValue) : value(make_shared<bool>(booleanValue))
{

}

template<>
void Fact_Boolean_Value<bool>::setValue(bool booleanValue)
{
    value = make_shared<bool>(booleanValue);
}

template<>
shared_ptr<Fact_Boolean_Value<bool>> Fact_Boolean_Value<bool>::negatingValue()
{
    return make_shared<Fact_Boolean_Value<bool>>(!value);
}

template<>
shared_ptr<Fact_Value_Type> Fact_Boolean_Value<bool>::getFactValueType()
{
    return make_shared<Fact_Value_Type>(Fact_Value_Type::BOOLEAN);
}

template<typename T>
shared_ptr<bool> Fact_Boolean_Value<T>::getValue()
{
    return value;
}
