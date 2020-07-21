//
//  dependency_type.hpp
//  Nadia-CPP
//
//  Created by Dean Lee on 23/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef dependency_type_hpp
#define dependency_type_hpp

#include <stdio.h>

class Dependency_Type
{
    static int mandatoryDependency; // 1000000
    static int optionalDependency;  // 0100000
    static int possibleDependency;  // 0010000
    static int andDependency;        // 0001000
    static int orDependency;         // 0000100
    static int notDependency;        // 0000010
    static int knownDependency;      // 0000001
    
public:
    static int getMandatory();
    static int getOptional();
    static int getPossible();
    static int getAnd();
    static int getOr();
    static int getNot();
    static int getKnown();
};
#endif /* dependency_type_hpp */
