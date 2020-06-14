//
//  fact_double_value.hpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 23/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef fact_double_value_hpp
#define fact_double_value_hpp

#include "fact_value.hpp"

template<typename T>
class Fact_Double_Value: public Fact_Value<T>
{
private:
    shared_ptr<double> value;
    
public:
    Fact_Double_Value();
    Fact_Double_Value(shared_ptr<Fact_Double_Value<double>> const &fdouvPtr);
    Fact_Double_Value(double d);
    void setValue(double d) override;
    shared_ptr<double> getValue() override;
    shared_ptr<Fact_Value_Type> getFactValueType() override;
};

#endif /* fact_double_value_hpp */
