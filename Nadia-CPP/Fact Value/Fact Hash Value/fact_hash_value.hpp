//
//  fact_hash_value.hpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 23/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef fact_hash_value_hpp
#define fact_hash_value_hpp

#include "fact_value.hpp"

template<typename T>
class Fact_Hash_Value : public Fact_Value<T>
{
private:
    shared_ptr<string> value;
public:
    Fact_Hash_Value();
    Fact_Hash_Value(shared_ptr<Fact_Hash_Value<string>> fhvPtr);
    Fact_Hash_Value(string hash);
    void setValue(string hash) override;
    shared_ptr<Fact_Value_Type> getFactValueType() override;
    shared_ptr<string> getValue() override;
};
#endif /* fact_hash_value_hpp */
