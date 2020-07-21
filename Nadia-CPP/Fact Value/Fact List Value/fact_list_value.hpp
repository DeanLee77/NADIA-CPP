//
//  fact_list_value.hpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 23/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef fact_list_value_hpp
#define fact_list_value_hpp

#include "fact_value.hpp"

using namespace std;

template<typename T>
class Fact_List_Value : public Fact_Value<T>
{
private:
    shared_ptr<vector<any>> listValue;
    shared_ptr<any> defaultValue;
public:
    Fact_List_Value();
    Fact_List_Value(shared_ptr<Fact_List_Value<vector<any>>> const & flistvPtr);
    Fact_List_Value(vector<any> vectorValue);
    void setDefaultValue(shared_ptr<any> defaultValue);
    void addFactValueToListValue(any addingValue);
    void setValue(vector<any> vectorValue) override;
    shared_ptr<Fact_Value_Type> getFactValueType() override;
    shared_ptr<vector<any>> getValue() override;
    shared_ptr<any> getDefaultValue();

};

#endif /* fact_list_value_hpp */
