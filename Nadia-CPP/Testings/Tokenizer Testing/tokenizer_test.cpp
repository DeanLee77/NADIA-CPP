//
//  tokenizer_test.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 6/5/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "tokenizer_test.hpp"

using namespace std;

void Tokenizer_Test::tesing()
{
    ifstream inFile("tokenizer_testing.txt");
    if(!inFile)
    {
        cout << "tokenizer_test.txt file cannot be read" << endl;
        exit(0);
    }
    else
    {
        string strLine;
        string textstring = "";
        int lineTracking = 0;
        string tokenString;
        regex re("^\\/.*");
        smatch match;
        while(getline(inFile, strLine))
        {
            strLine = String_Handler::stringTrim(strLine);
            if(strLine.compare("") != 0 && !regex_match(strLine, match, re))
            {
                if(lineTracking == 0)
                {
                    textstring = strLine;
                    tokenString = *Tokenizer::getTokens(strLine)->tokensString.get();
                    lineTracking++;

                }
                else if(lineTracking == 1)
                {
                    cout << "text string: " << textstring << endl;
                    cout << "tk.tokenstring: " << tokenString << endl;
                    cout << "expected tokenstring line :" << strLine << endl;
                    cout << "\n";
                    assert(tokenString.compare(strLine) == 0);
                    if(tokenString.compare(strLine) != 0)
                    {
                        cout << "above line is not same as below line" << endl;
                        return ;
                    }
                    else
                    {
                        lineTracking = 0;
                    }
                }
            }
        }
    }
    
    
    
}
