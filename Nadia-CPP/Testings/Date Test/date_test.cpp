//
//  date_test.cpp
//  Nadia-CPP
//
//  Created by Dean Lee on 13/2/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "date_test.hpp"
#include <iostream>

Date Date_Test::generateDate0()
{
    return Date("1/12/2019");
}

Date Date_Test::generateDate1()
{
    return Date(1, 12, 2020);
}

Date Date_Test::generateDate2()
{
    return Date("12", "2", "2020");
}

Date Date_Test::generateDate3()
{
    return Date("12/5/2020", "DD/M/YYYY");
}

Date Date_Test::generateDate4()
{
    return Date("12/01/2020", "DD/MM/YYYY");
}

Date Date_Test::generateDate5()
{
    return Date("12/Jun/2020", "DD/MMM/YYYY");
}

Date Date_Test::generateDate6()
{
    return Date("12 2 2020", "DD M YYYY");
}

Date Date_Test::generateDate7()
{
    return Date("23 05 2020", "DD MM YYYY");
}

void Date_Test::printDate(Date date)
{
    cout << "date value: " << date.getWholeDateValueInString() << endl;
}

void Date_Test::printDateInFormat(Date date)
{
    cout << "date value in format (DD MMM YYYY): " << date.getWholeDateValueInFormattedString("DD MMM YYYY") << endl;
    cout << "date value in format (DD MM YYYY): " << date.getWholeDateValueInFormattedString("DD MM YYYY") << endl;
    cout << "date value in format (D M YYYY): " << date.getWholeDateValueInFormattedString("D M YYYY") << endl;
    cout << "date value in format (DD/MMM/YYYY): " << date.getWholeDateValueInFormattedString("DD/MMM/YYYY") << endl;
    cout << "date value in format (MMM/DD/YYYY): " << date.getWholeDateValueInFormattedString("MMM/DD/YYYY") << endl;
    cout << "date value in format (M/D/YYYY): " << date.getWholeDateValueInFormattedString("M/D/YYYY") << endl;
}

void Date_Test::generateDatesAndPrint()
{
    cout << "1. ";
    printDate(generateDate1());
    printDateInFormat(generateDate1());
    cout << "2. ";
    printDate(generateDate2());
    printDateInFormat(generateDate2());
    cout << "3. ";
    printDate(generateDate3());
    printDateInFormat(generateDate3());
    cout << "4. ";
    printDate(generateDate4());
    printDateInFormat(generateDate4());
    cout << "5. ";
    printDate(generateDate5());
    printDateInFormat(generateDate5());
    cout << "6. ";
    printDate(generateDate6());
    printDateInFormat(generateDate6());
    cout << "7. ";
    printDate(generateDate7());
    printDateInFormat(generateDate7());
}
