//
//  Template_test.cpp
//  Nadia-CPP
//
//  Created by Dean Lee on 4/2/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "Template_test.hpp"
#include <iostream>
using namespace std;

template <class T>
Template_Test<T>::Template_Test(string s)
{
    cout << s << endl;
}

template<class T>
Template_Test<T>::~Template_Test()
{
    cout << "destroyed Template Test" << endl;
}
