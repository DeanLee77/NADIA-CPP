//
//  fact_value.hpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 21/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef fact_value_hpp
#define fact_value_hpp

#include <memory>
#include <string>
#include <map>
#include <vector>
#include <variant>

using namespace std;

namespace FactValuType {
    enum Fact_Value_Type
    {
       DEFI_STRING, TEXT, STRING, INTEGER, DOUBLE, NUMBER, DATE, DECIMAL, BOOLEAN, LIST, RULE, RULE_SET, OBJECT, UNKNOWN, URL, HASH, UUID, NULL_VALUE
    };
}

using namespace FactValuType;

template<typename T>
class Fact_Boolean_Value;

template<typename T>
class Fact_String_Value;

template<typename T>
class Fact_Date_Value;
class Date;

template<typename T>
class Fact_Defi_String_Value;

template<typename T>
class Fact_Double_Value;

template<typename T>
class Fact_Hash_Value;

template<typename T>
class Fact_Integer_Value;

template<typename T>
class Fact_URL_Value;

template<typename T>
class Fact_UUID_Value;

template<typename T>
class Fact_List_Value;

using var = variant<shared_ptr<Fact_Boolean_Value<bool>>, shared_ptr<Fact_String_Value<string>>, shared_ptr<Fact_Date_Value<Date>>, shared_ptr<Fact_Defi_String_Value<string>>, shared_ptr<Fact_Double_Value<double>>, shared_ptr<Fact_Hash_Value<string>>, shared_ptr<Fact_Integer_Value<int>>, shared_ptr<Fact_URL_Value<string>>, shared_ptr<Fact_UUID_Value<string>>>;

template<typename T>
class Fact_Value
{
public:

    static shared_ptr<Fact_Boolean_Value<bool>> parse(bool& boolValue);
    static shared_ptr<Fact_String_Value<string>> parse(string& stringValue);
    static shared_ptr<Fact_Date_Value<Date>> parse(Date& dateValue);
    static shared_ptr<Fact_Defi_String_Value<string>> parseDefiString(string& stringValue);
    static shared_ptr<Fact_Double_Value<double>> parse(double& doubleValue);
    static shared_ptr<Fact_Hash_Value<string>> parseHash(string& hashValue);
    static shared_ptr<Fact_Integer_Value<int>> parse(int& intValue);
    static shared_ptr<Fact_URL_Value<string>> parseURL(string& urlValue);
    static shared_ptr<Fact_UUID_Value<string>> parseUUID(string& uuidValue);
    static shared_ptr<Fact_List_Value<vector<var>>> parse(vector<var>& listValue);
//    static shared_ptr<Fact_Value_Type> findFactValueType(string& value);
//    static bool isBoolean(string& str);
//    static shared_ptr<Fact_Value> generateFactValue(string& factValueTypeInString, string& str);
//    static string getValueInString(Fact_Value& factValue);
//
protected:
    virtual void setValue(T value) = 0;
    virtual shared_ptr<T> getValue() = 0;
    virtual shared_ptr<Fact_Value_Type> getFactValueType() = 0;
//    static string getFactValueTypeInString(Fact_Value_Type fvt);
};
#endif /* fact_value_hpp */
