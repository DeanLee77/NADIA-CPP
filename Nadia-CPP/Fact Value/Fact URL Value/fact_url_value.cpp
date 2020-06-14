//
//  fact_url_value.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 23/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "fact_url_value.hpp"

template<>
Fact_URL_Value<string>::Fact_URL_Value()
{
    
}

template<>
Fact_URL_Value<string>::Fact_URL_Value(shared_ptr<Fact_URL_Value<string>> const &fuvPtr)
{
    this->value = fuvPtr->getValue();
}

template<>
Fact_URL_Value<string>::Fact_URL_Value(string url) : value(make_shared<string>(url))
{
    
}

template<>
void Fact_URL_Value<string>::setValue(string url)
{
    value = make_shared<string>(url);
}

template<>
shared_ptr<Fact_Value_Type> Fact_URL_Value<string>::getFactValueType()
{
    return make_shared<Fact_Value_Type>(Fact_Value_Type::URL);
}

template<typename T>
shared_ptr<string> Fact_URL_Value<T>::getValue()
{
    return value;
}
