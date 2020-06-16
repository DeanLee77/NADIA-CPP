//
//  return.hpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 15/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef return_hpp
#define return_hpp

#include <stdio.h>
#include <any>

#include "runtime_exception.hpp"

class Return : public Interpreter_Runtime_Exception
{
public:
    const any value;
    
    Return(any value);
    
};



#endif /* return_hpp */
