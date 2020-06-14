//
//  fact_boolean_value.hpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 21/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef fact_boolean_value_hpp
#define fact_boolean_value_hpp

#include "fact_value.hpp"

template<typename T>
class Fact_Boolean_Value : public Fact_Value<T>
{
public:
    Fact_Boolean_Value();
    Fact_Boolean_Value(shared_ptr<Fact_Boolean_Value<bool>> const &fbvPtr);
    Fact_Boolean_Value(bool booleanValue);
    void setValue(bool booleanValue) override;
    shared_ptr<Fact_Boolean_Value<bool>> negatingValue();
    shared_ptr<bool> getValue() override;
    shared_ptr<Fact_Value_Type> getFactValueType() override;
        
private:
    shared_ptr<bool> value;
    
};
#endif /* fact_boolean_value_hpp */
