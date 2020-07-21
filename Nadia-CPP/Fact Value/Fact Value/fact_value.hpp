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
#include <any>
#include <variant>
#include <unordered_map>
#include <typeindex>

using namespace std;

namespace FactValuType {
    enum Fact_Value_Type
    {
       DEFI_STRING, TEXT, STRING, INTEGER, DOUBLE, NUMBER, DATE, DECIMAL, BOOLEAN, LIST, RULE, RULE_SET, OBJECT, UNKNOWN, URL, HASH, UUID, NULL_VALUE
    };
    
    inline map<Fact_Value_Type, string> factValueTypeMap{{Fact_Value_Type::DEFI_STRING, "DEFI_STRING"}, {Fact_Value_Type::TEXT, "TEXT"}, {Fact_Value_Type::STRING, "STRING"}, {Fact_Value_Type::INTEGER, "INTEGER"}, {Fact_Value_Type::DOUBLE, "DOUBLE"}, {Fact_Value_Type::NUMBER, "NUMBER"}, {Fact_Value_Type::DATE, "DATE"}, {Fact_Value_Type::DECIMAL, "DECIMAL"},{Fact_Value_Type::BOOLEAN, "BOOLEAN"}, {Fact_Value_Type::LIST, "LIST"}, {Fact_Value_Type::RULE, "RULE"}, {Fact_Value_Type::RULE_SET, "RULE_SET"}, {Fact_Value_Type::OBJECT, "OBJECT"}, {Fact_Value_Type::UNKNOWN, "UNKNOWN"}, {Fact_Value_Type::URL, "URL"}, {Fact_Value_Type::HASH, "HASH"}, {Fact_Value_Type::UUID, "UUID"}, {Fact_Value_Type::NULL_VALUE, "NULL_VALUE"}};
    
   
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

//using var = variant<shared_ptr<Fact_Boolean_Value<bool>>, shared_ptr<Fact_String_Value<string>>, shared_ptr<Fact_Date_Value<Date>>, shared_ptr<Fact_Defi_String_Value<string>>, shared_ptr<Fact_Double_Value<double>>, shared_ptr<Fact_Hash_Value<string>>, shared_ptr<Fact_Integer_Value<int>>, shared_ptr<Fact_URL_Value<string>>, shared_ptr<Fact_UUID_Value<string>>>;

inline unordered_map<type_index, int> typeIndexMap{{typeid(shared_ptr<Fact_Boolean_Value<bool>>), 0}, {typeid(shared_ptr<Fact_String_Value<string>>), 1}, {typeid(shared_ptr<Fact_Date_Value<Date>>), 2}, {typeid(shared_ptr<Fact_Defi_String_Value<string>>), 3}, {typeid(shared_ptr<Fact_Double_Value<double>>), 4}, {typeid(shared_ptr<Fact_Hash_Value<string>>), 5}, {typeid(shared_ptr<Fact_Integer_Value<int>>), 6}, {typeid(shared_ptr<Fact_URL_Value<string>>), 7}, {typeid(shared_ptr<Fact_UUID_Value<string>>), 8}};

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
    static shared_ptr<Fact_List_Value<vector<any>>> parse(vector<any>& listValue);
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
