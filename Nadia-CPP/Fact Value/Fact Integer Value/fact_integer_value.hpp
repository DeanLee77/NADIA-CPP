//
//  fact_integer_value.hpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 23/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef fact_integer_value_hpp
#define fact_integer_value_hpp

#include "fact_value.hpp"

template<typename T>
class Fact_Integer_Value : public Fact_Value<T>
{
public:
    Fact_Integer_Value();
    Fact_Integer_Value(shared_ptr<Fact_Integer_Value<int>> const &fivPtr);
    Fact_Integer_Value(int intValue);
    void setValue(int value) override;
    shared_ptr<Fact_Value_Type> getFactValueType() override;
    shared_ptr<int> getValue() override;
private:
    shared_ptr<int> value;
};
#endif /* fact_integer_value_hpp */
