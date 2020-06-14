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
    shared_ptr<vector<var>> listValue;
    shared_ptr<var> defaultValue;
public:
    Fact_List_Value();
    Fact_List_Value(shared_ptr<Fact_List_Value<vector<var>>> const & flistvPtr);
    Fact_List_Value(vector<var> vectorValue);
    void setDefaultValue(shared_ptr<var> defaultValue);
    void addFactValueToListValue(var addingValue);
    void setValue(vector<var> vectorValue) override;
    shared_ptr<Fact_Value_Type> getFactValueType() override;
    shared_ptr<vector<var>> getValue() override;
    shared_ptr<var> getDefaultValue();

};

#endif /* fact_list_value_hpp */
