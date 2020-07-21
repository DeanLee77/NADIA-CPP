//
//  dependency.cpp
//  Nadia-CPP
//
//  Created by Dean Lee on 23/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "dependency.hpp"

Dependency::Dependency(shared_ptr<Node> parent, shared_ptr<Node> child, int& dependencyType) : parent(parent), child(child), dependencyType(dependencyType)
{
    
}

shared_ptr<Node> Dependency::getParentNode()
{
    return parent;
}

shared_ptr<Node> Dependency::getChildNode()
{
    return child;
}

const int& Dependency::getDependencyType()
{
    return dependencyType;
}
