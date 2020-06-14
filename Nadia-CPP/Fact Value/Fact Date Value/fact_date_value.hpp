//
//  fact_date_value.hpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 23/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef fact_date_value_hpp
#define fact_date_value_hpp

#include "fact_value.hpp"
#include "date.hpp"

template<typename T>
class Fact_Date_Value : public Fact_Value<T>
{
public:
    Fact_Date_Value();
    Fact_Date_Value(shared_ptr<Fact_Date_Value<Date>> const &fdvPtr);
    Fact_Date_Value(Date date);
    void setValue(Date str) override;
    shared_ptr<Fact_Value_Type> getFactValueType() override;
    shared_ptr<Date> getValue() override;
private:
    shared_ptr<Date> value;
};
#endif /* fact_date_value_hpp */
