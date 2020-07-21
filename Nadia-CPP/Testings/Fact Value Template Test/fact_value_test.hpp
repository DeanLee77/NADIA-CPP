//
//  fact_value_test.hpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 22/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef fact_value_test_hpp
#define fact_value_test_hpp

#include <iostream>
#include <stdio.h>
#include <optional>
#include "fact_value.hpp"
#include "date_test.hpp"

template<class... Ts>
struct overload : Ts... { using Ts::operator()...; };

template<class... Ts>
overload(Ts...) -> overload<Ts...>;

class Fact_Value_Test
{
 public:
//    static void generateAllFactValues();
    static shared_ptr<Fact_Boolean_Value<bool>> generateFactBooleanValue();
    static shared_ptr<Fact_String_Value<string>> generateFactStringValue();
    static shared_ptr<Fact_Date_Value<Date>> generateFactDateValue();
    static shared_ptr<Fact_Defi_String_Value<string>> generateFactDefiStringValue();
    static shared_ptr<Fact_Double_Value<double>> generateFactDoubleValue();
    static shared_ptr<Fact_Hash_Value<string>> generateFactHashValue();
    static shared_ptr<Fact_Integer_Value<int>> generateFactIntegerValue();
    static shared_ptr<Fact_URL_Value<string>> generateFactURLValue();
    static shared_ptr<Fact_UUID_Value<string>> generateFactUUIDValue();
    static shared_ptr<Fact_List_Value<vector<any>>> generateFactListValue();
    static void printFactListValue();
//    static void testFindFactValueType();
//    static shared_ptr<string> getFactValueTypeInString(Fact_Value_Type fvt);
    static void testGenerateFactValue();
};
#endif /* fact_value_test_hpp */
