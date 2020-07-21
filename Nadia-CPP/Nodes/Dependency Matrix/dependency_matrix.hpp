//
//  dependency_matrix.hpp
//  Nadia-CPP
//
//  Created by Dean Lee on 23/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef dependency_matrix_hpp
#define dependency_matrix_hpp

#include <stdio.h>
#include <vector>

#include "dependency.hpp"

using namespace std;
class Dependency_Matrix
{
    /*
     *  order of dependency type
     *  1. MANDATORY
     *  2. OPTIONAL
     *  3. POSSIBLE
     *  4. AND
     *  5. OR
     *  6. NOT
     *  7. KNOWN
     *
     *  int value will be '1' if any one of them is true case otherwise '0'
     *  for instance, if a rule is in 'MANDATORY AND NOT' dependency then
     *  dependency type value is '1001010'
     *
     *  if there is no dependency then value is 0000000
     */
    
    const int dependencyMatrixSize;
    int* dependencyMatrix;
    
    int& getIndex(int& parentRuleId, int& childRuleId);
public:
    Dependency_Matrix(int& dependencyMatrixSize);
    Dependency_Matrix(int& dependencyMatrixSize, int* dependencyMatrix);
    ~Dependency_Matrix();
    int* getDependencyMatrixArray();
    
    int& getDependencyType(int& parentRuleId, int& childRuleId);
    vector<int> getToChildDependencyList(int& nodeId);
    vector<int> getOrToChildDependencyList(int& nodeId);
    vector<int> getAndToChildDependencyList(int& nodeId);
    vector<int> getMandatoryToChildDependencyList(int& nodeId);
    vector<int> getFromParentDependencyList(int& nodeId);
    bool hasMandatoryChildNode(int& nodeId);
};
#endif /* dependency_matrix_hpp */
