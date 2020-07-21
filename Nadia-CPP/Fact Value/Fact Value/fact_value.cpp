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

template<>
shared_ptr<Fact_Boolean_Value<bool>> Fact_Value<bool>::parse(bool& boolValue)
{
    return make_shared<Fact_Boolean_Value<bool>>(boolValue);
}

template<>
shared_ptr<Fact_String_Value<string>> Fact_Value<string>::parse(string& stringValue)
{
    return make_shared<Fact_String_Value<string>>(stringValue);
}

template<>
shared_ptr<Fact_Date_Value<Date>> Fact_Value<Date>::parse(Date& dateValue)
{
    return make_shared<Fact_Date_Value<Date>>(dateValue);
}

template<>
shared_ptr<Fact_Defi_String_Value<string>> Fact_Value<string>::parseDefiString(string& stringValue)
{
    return make_shared<Fact_Defi_String_Value<string>>(stringValue);
}

template<>
shared_ptr<Fact_Double_Value<double>> Fact_Value<double>::parse(double& doubleValue)
{
    return make_shared<Fact_Double_Value<double>>(doubleValue);
}

template<>
shared_ptr<Fact_Hash_Value<string>> Fact_Value<string>::parseHash(string& hashValue)
{
    return make_shared<Fact_Hash_Value<string>>(hashValue);
}

template<>
shared_ptr<Fact_Integer_Value<int>> Fact_Value<int>::parse(int& intValue)
{
    return make_shared<Fact_Integer_Value<int>>(intValue);
}

template<>
shared_ptr<Fact_URL_Value<string>> Fact_Value<string>::parseURL(string& urlValue)
{
    return make_shared<Fact_URL_Value<string>>(urlValue);
}

template<>
shared_ptr<Fact_UUID_Value<string>> Fact_Value<string>::parseUUID(string& uuidValue)
{
    return make_shared<Fact_UUID_Value<string>>(uuidValue);
}

template<>
shared_ptr<Fact_List_Value<vector<any>>> Fact_Value<vector<any>>::parse(vector<any>& listValue)
{
    return make_shared<Fact_List_Value<vector<any>>>(listValue);
}
