//
//  fact_date_value.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 23/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "fact_date_value.hpp"

template<>
Fact_Date_Value<Date>::Fact_Date_Value()
{
    
}

template<>
Fact_Date_Value<Date>::Fact_Date_Value(shared_ptr<Fact_Date_Value<Date>> const &fdvPtr)
{
    this->value = fdvPtr->getValue();
}

template<>
Fact_Date_Value<Date>::Fact_Date_Value(Date date) : value(make_shared<Date>(date))
{
    
}

template<>
void Fact_Date_Value<Date>::setValue(Date date)
{
    value = make_shared<Date>(date);
}

template<typename T>
shared_ptr<Date> Fact_Date_Value<T>::getValue()
{
    return value;
}

template<>
shared_ptr<Fact_Value_Type> Fact_Date_Value<Date>::getFactValueType()
{
    return make_shared<Fact_Value_Type>(Fact_Value_Type::DATE);
}

