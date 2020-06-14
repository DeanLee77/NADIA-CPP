//
//  fact_uuid_value.hpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 23/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef fact_uuid_value_hpp
#define fact_uuid_value_hpp

#include "fact_value.hpp"

template<typename T>
class Fact_UUID_Value : public Fact_Value<T>
{
private:
    shared_ptr<string> value;
public:
    Fact_UUID_Value();
    Fact_UUID_Value(shared_ptr<Fact_UUID_Value<string>> const &fidvPtr);
    Fact_UUID_Value(string uuid);
    void setValue(string uuid) override;
    shared_ptr<Fact_Value_Type> getFactValueType() override;
    shared_ptr<string> getValue() override;
};
#endif /* fact_uuid_value_hpp */
