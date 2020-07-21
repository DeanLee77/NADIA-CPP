//
//  dependency_matrix.cpp
//  Nadia-CPP
//
//  Created by Dean Lee on 23/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "dependency_matrix.hpp"
#include "dependency_type.hpp"

#include <memory>

Dependency_Matrix::Dependency_Matrix(int& dependencyMatrixSize, int* dependencyMatrix): dependencyMatrixSize(dependencyMatrixSize), dependencyMatrix(dependencyMatrix)
{
    
}

Dependency_Matrix::Dependency_Matrix(int& dependencyMatrixSize) : dependencyMatrixSize(dependencyMatrixSize)
{
    this->dependencyMatrix = new int[dependencyMatrixSize * dependencyMatrixSize];
}

Dependency_Matrix::~Dependency_Matrix()
{
    delete[] dependencyMatrix;
}

int* Dependency_Matrix::getDependencyMatrixArray()
{
    return dependencyMatrix;
}

int& Dependency_Matrix::getIndex(int& parentRuleId, int& childRuleId)
{
    return dependencyMatrix[parentRuleId * dependencyMatrixSize + childRuleId];
}

int& Dependency_Matrix::getDependencyType(int& parentRuleId, int& childRuleId)
{
    return getIndex(parentRuleId, childRuleId);
}

vector<int> Dependency_Matrix::getToChildDependencyList(int& nodeId)
{
    vector<int> returnVector;
    for(int i = 0; i != dependencyMatrixSize; i++)
    {
        if(i != nodeId && (dependencyMatrix[nodeId * dependencyMatrixSize + i] != 0))
        {
            returnVector.push_back(i);
        }
    }
    
    return returnVector;
}

vector<int> Dependency_Matrix::getOrToChildDependencyList(int& nodeId)
{
    int orDependency = Dependency_Type::getOr();
    vector<int> returnVector;
    
    for(int i = 0; i != dependencyMatrixSize; i++)
    {
        if(i != nodeId && (dependencyMatrix[nodeId * dependencyMatrixSize + i] & orDependency) == orDependency)
        {
            returnVector.push_back(i);
        }
    }
    return returnVector;
}

vector<int> Dependency_Matrix::getAndToChildDependencyList(int& nodeId)
{
    int andDependency = Dependency_Type::getAnd();
    vector<int> returnVector;
    
    for(int i = 0; i != dependencyMatrixSize; i++)
    {
        if(i != nodeId && (dependencyMatrix[nodeId * dependencyMatrixSize +i] & andDependency) == andDependency)
        {
            returnVector.push_back(i);
        }
    }
    
    return returnVector;
}

vector<int> Dependency_Matrix::getMandatoryToChildDependencyList(int& nodeId)
{
    int mandatoryDependency = Dependency_Type::getMandatory();
    vector<int> returnVector;

    for(int i = 0; i !=  dependencyMatrixSize; i++)
    {
        if(i != nodeId && (dependencyMatrix[nodeId * dependencyMatrixSize +i] & mandatoryDependency) == mandatoryDependency)
        {
            returnVector.push_back(i);
        }
    }
    
    return returnVector;
}


vector<int> Dependency_Matrix::getFromParentDependencyList(int& nodeId)
{
    
    vector<int> returnVector;
    for(int i = 0; i != dependencyMatrixSize; i++)
    {
        if(i != nodeId && dependencyMatrix[i * dependencyMatrixSize + nodeId] != 0)
        {
            returnVector.push_back(i);
        }
    }
    
    return returnVector;
}

bool Dependency_Matrix::hasMandatoryChildNode(int& nodeId)
{
    return getMandatoryToChildDependencyList(nodeId).size() > 0;
}
