//
//  fact_value.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 21/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "fact_value.hpp"
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
//#include "tokenizer.hpp"

template<typename T>
shared_ptr<Fact_Boolean_Value<bool>> Fact_Value<T>::parse(bool& boolValue)
{
    return make_shared<Fact_Boolean_Value<bool>>(boolValue);
}

template<typename T>
shared_ptr<Fact_String_Value<string>> Fact_Value<T>::parse(string& stringValue)
{
    return make_shared<Fact_String_Value<string>>(stringValue);
}

template<typename T>
shared_ptr<Fact_Date_Value<Date>> Fact_Value<T>::parse(Date& dateValue)
{
    return make_shared<Fact_Date_Value<Date>>(dateValue);
}

template<typename T>
shared_ptr<Fact_Defi_String_Value<string>> Fact_Value<T>::parseDefiString(string& stringValue)
{
    return make_shared<Fact_Defi_String_Value<string>>(stringValue);
}

template<typename T>
shared_ptr<Fact_Double_Value<double>> Fact_Value<T>::parse(double& doubleValue)
{
    return make_shared<Fact_Double_Value<double>>(doubleValue);
}

template<typename T>
shared_ptr<Fact_Hash_Value<string>> Fact_Value<T>::parseHash(string& hashValue)
{
    return make_shared<Fact_Hash_Value<string>>(hashValue);
}

template<typename T>
shared_ptr<Fact_Integer_Value<int>> Fact_Value<T>::parse(int& intValue)
{
    return make_shared<Fact_Integer_Value<int>>(intValue);
}

template<typename T>
shared_ptr<Fact_URL_Value<string>> Fact_Value<T>::parseURL(string& urlValue)
{
    return make_shared<Fact_URL_Value<string>>(urlValue);
}

template<typename T>
shared_ptr<Fact_UUID_Value<string>> Fact_Value<T>::parseUUID(string& uuidValue)
{
    return make_shared<Fact_UUID_Value<string>>(uuidValue);
}

template<typename T>
shared_ptr<Fact_List_Value<vector<var>>> parse(vector<var>& listValue)
{
    return make_shared<Fact_List_Value<vector<var>>>(listValue);
}
