//
//  date_test.hpp
//  Nadia-CPP
//
//  Created by Dean Lee on 13/2/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef date_test_hpp
#define date_test_hpp

#include <stdio.h>
#include "date.hpp"


class Date_Test{

public:
    static Date generateDate0();
    static Date generateDate1();
    static Date generateDate2();
    static Date generateDate3();
    static Date generateDate4();
    static Date generateDate5();
    static Date generateDate6();
    static Date generateDate7();
    
    static void printDate(Date date);
    static void printDateInFormat(Date date);
    static void generateDatesAndPrint();
};
#endif /* date_test_hpp */
