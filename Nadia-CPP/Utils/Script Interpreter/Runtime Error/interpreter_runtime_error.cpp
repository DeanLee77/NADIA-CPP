//
//  runtime_error.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 3/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "interpreter_runtime_error.hpp"

Runtime_Error::Runtime_Error(Interpreter_Token& token, string& message): runtime_error(message), token(token)
{
    
}

string Runtime_Error::getMessage()
{
    return this->what();
}
