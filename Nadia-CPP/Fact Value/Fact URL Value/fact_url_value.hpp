//
//  fact_url_value.hpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 23/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef fact_url_value_hpp
#define fact_url_value_hpp

#include "fact_value.hpp"

template<typename T>
class Fact_URL_Value : public Fact_Value<T>
{
private:
    shared_ptr<string> value;
public:
    Fact_URL_Value();
    Fact_URL_Value(shared_ptr<Fact_URL_Value<string>> const &fuvPtr);
    Fact_URL_Value(string url);
    void setValue(string url) override;
    shared_ptr<Fact_Value_Type> getFactValueType() override;
    shared_ptr<string> getValue() override;
};
#endif /* fact_url_value_hpp */
