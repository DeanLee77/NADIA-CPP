//
//  dependency.hpp
//  Nadia-CPP
//
//  Created by Dean Lee on 23/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef dependency_hpp
#define dependency_hpp

#include <stdio.h>
#include "node.hpp"

class Dependency
{
  
    const int dependencyType; //this variable is to store 'AND/OR' DependencyType between Nodes
    const shared_ptr<Node> parent; // this variable is to store a parent Node of this dependency
    const shared_ptr<Node> child; // this variable is to store a child Node of this dependency
    
    
public:
    Dependency(shared_ptr<Node> parent, shared_ptr<Node> child, int& dependencyType);
    shared_ptr<Node> getParentNode();
    shared_ptr<Node> getChildNode();
    const int& getDependencyType();
};
#endif /* dependency_hpp */
