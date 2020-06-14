//
//  string_handler_test.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 5/5/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//


#include "string_handler_test.hpp"
using namespace std;

void String_Handler_Test::testTrim()
{
    string toBeTrimmed = "   need to trimmed  ";
    cout << "toBeTrimmed String: " <<toBeTrimmed << endl;
    string trimmed = String_Handler::stringTrim(toBeTrimmed);
    cout << "trimmed String : " << trimmed << endl;
    string expectedString = "need to trimmed";
    
    assert(expectedString.compare(trimmed) == 0);

}

void String_Handler_Test::testSplit()
{
    string toBeSplit = "split : this : string";
    cout << "toBeSplit String: " << toBeSplit << endl;
    cout << "this string will split by \':\'" << endl;
    char delimiter = ':';
    vector<string> tokens = String_Handler::stringSplit(toBeSplit, delimiter);
    string firstString = "split ", secondString = " this ", thirdString = " string";
    vector<string> comparingStringList{firstString, secondString, thirdString};
    for(int i = 0 ; i < tokens.size() ; i ++)
    {
        assert(comparingStringList[i].compare(tokens[i]) == 0);
    }
}

void String_Handler_Test::testToString()
{
    bool boolToString = true;
    cout << "boolToString : true" << endl;
    string booleanString = String_Handler::toString<bool>(boolToString);
    cout << "ToString(boolToString): " << booleanString << endl;
    assert( booleanString.compare("true") == 0);
    
    const int& intToString = 4;
    cout << "intToString : " << intToString << endl;
    string intString = String_Handler::toString<int>(intToString);
    cout << "ToString(intToString) : " << intString << endl;
    assert(intString.compare("4") == 0);
    
    const double& doubleToString = 4.5;
    cout << "doubleToString : " << doubleToString << endl;
    string doubleString = String_Handler::toString<double>(doubleToString);
    cout << "ToString(doubleToString) : " << doubleString << endl;
    assert(doubleString.compare("4.5") == 0);
    
}

void String_Handler_Test::testAll()
{
    testTrim();
    testSplit();
    testToString();
}

