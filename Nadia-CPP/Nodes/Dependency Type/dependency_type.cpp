//
//  dependency_type.cpp
//  Nadia-CPP
//
//  Created by Dean Lee on 23/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "dependency_type.hpp"
int Dependency_Type::mandatoryDependency = 64; // 1000000
int Dependency_Type::optionalDependency = 32;  // 0100000
int Dependency_Type::possibleDependency = 16;  // 0010000
int Dependency_Type::andDependency = 8;        // 0001000
int Dependency_Type::orDependency = 4;         // 0000100
int Dependency_Type::notDependency = 2;        // 0000010
int Dependency_Type::knownDependency = 1;      // 0000001

int Dependency_Type::getMandatory()
{
    return mandatoryDependency;
}

int Dependency_Type::getOptional()
{
    return optionalDependency;
}

int Dependency_Type::getPossible()
{
    return possibleDependency;
}

int Dependency_Type::getAnd()
{
    return andDependency;
}

int Dependency_Type::getOr()
{
    return orDependency;
}

int Dependency_Type::getNot()
{
    return notDependency;
}

int Dependency_Type::getKnown()
{
    return knownDependency;
    }
