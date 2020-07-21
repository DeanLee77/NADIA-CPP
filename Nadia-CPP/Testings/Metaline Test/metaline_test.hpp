//
//  metaline_test.hpp
//  Nadia-CPP
//
//  Created by Dean Lee on 23/6/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef metaline_test_hpp
#define metaline_test_hpp

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <stack>
#include <memory>
#include "node.hpp"
#include "metadata_line.hpp"
using namespace std;

class Metaline_Testing
{
    static void handlingParent(string parentText, stack<string> parentStack, unordered_map<string, shared_ptr<Node>>& nodeMap);
    static void handlingChild(string parentText, string childText, string dependencyKeyword, stack<string> parentStack, unordered_map<string, shared_ptr<Node>>& nodeMap);
    static void handleListItem(string parentText, string childText, unordered_map<string, shared_ptr<Node>>& nodeMap);
    static void handleWarning(string trimmedLine);
    static stack<string> HandlingStackPop(stack<string> parentStack, int indentationDifference);
public:
    
    static bool testing();
    
};
#endif /* metaline_test_hpp */
