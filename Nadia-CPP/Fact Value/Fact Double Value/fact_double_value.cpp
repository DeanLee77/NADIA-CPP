//
//  fact_double_value.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 23/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "fact_double_value.hpp"

template<>
Fact_Double_Value<double>::Fact_Double_Value()
{
    
}

template<>
Fact_Double_Value<double>::Fact_Double_Value(shared_ptr<Fact_Double_Value<double>> const &fdouvPtr)
{
    this->value = fdouvPtr->getValue();
}

template<>
Fact_Double_Value<double>::Fact_Double_Value(double d) : value(make_shared<double>(d))
{

}

template<>
void Fact_Double_Value<double>::setValue(double d)
{
    value = make_shared<double>(d);
}

template<typename T>
shared_ptr<double> Fact_Double_Value<T>::getValue()
{
    return value;
}

template<>
shared_ptr<Fact_Value_Type> Fact_Double_Value<double>::getFactValueType()
{
    return make_shared<Fact_Value_Type>(Fact_Value_Type::DECIMAL);
}
