//
//  fact_list_value.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 23/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "fact_list_value.hpp"
#include "fact_boolean_value.hpp"
#include "fact_string_value.hpp"
#include "fact_date_value.hpp"
#include "fact_defi_string_value.hpp"
#include "fact_double_value.hpp"
#include "fact_hash_value.hpp"
#include "fact_integer_value.hpp"
#include "fact_list_value.hpp"
#include "fact_url_value.hpp"
#include "fact_uuid_value.hpp"

template<>
Fact_List_Value<vector<var>>::Fact_List_Value()
{
    
}

template<>
Fact_List_Value<vector<var>>::Fact_List_Value(shared_ptr<Fact_List_Value<vector<var>>> const & flistvPtr)
{
    this->listValue = flistvPtr->getValue();
}

template<>
Fact_List_Value<vector<var>>::Fact_List_Value(vector<var> vectorValue) : listValue(make_shared<vector<var>>(vectorValue))
{
    
}

template<>
void Fact_List_Value<vector<var>>::setValue(vector<var> vectorValue)
{
    listValue = make_shared<vector<var>>(vectorValue);
}

template<>
void Fact_List_Value<vector<var>>::setDefaultValue(shared_ptr<var> initialDefaultValue)
{
    defaultValue = initialDefaultValue;
}

template<>
void Fact_List_Value<vector<var>>::addFactValueToListValue(var fv)
{
    listValue->push_back(fv);
}

template<>
shared_ptr<Fact_Value_Type> Fact_List_Value<vector<var>>::getFactValueType()
{
     return make_shared<Fact_Value_Type>(Fact_Value_Type::LIST);
}

template<typename T>
shared_ptr<vector<var>>  Fact_List_Value<T>::getValue()
{
    return listValue;
}

template<>
shared_ptr<var> Fact_List_Value<vector<var>>::getDefaultValue()
{
    return defaultValue;
}
