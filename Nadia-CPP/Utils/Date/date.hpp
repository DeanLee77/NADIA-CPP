//
//  date.hpp
//  Nadia-CPP
//
//  Created by Dean Lee on 11/2/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#ifndef date_hpp
#define date_hpp

#include <stdio.h>
#include <string>
#include <ctime>
using namespace std;
class Date
{
private:
    int mDay; //represents date from 1 to 31
    string wDayString; //represents day from Mon to Sun
    int wDayInt; //represnts day from 1 to 7
    int year;  //represents year e.g. 2020
    int monthInt; //represents month from 1 to 12
    string monthString; //represents month from Jan to Dec
    tm* date;
    tm* dateInit();
public:
    Date();
    Date(string dateInString, string dateFormat);
    Date(string dateInString);
    Date(int date, int month, int year);
    Date(string date, string month, string year);
    ~Date();
    
    int getDateInInt();
    string getDateInString();
    
    int getWDayInt();
    string getWDayString();
    
    int getMonthInt();
    string getMonthString();
    
    int getYearInInt();
    string getYearInString();
    
    string getWholeDateValueInFormattedString(string formatInString);
    string getWholeDateValueInString();
    bool isEqual(Date& anotherDate);
    bool isAfter(Date& anotherDate);
    bool isBefore(Date& anotherDate);
    
    static int daysDiffBetween(Date& date1, Date& date2);
    static int monthsDiffBetween(Date& date1, Date& date2);
    static int yearsDiffBetween(Date& date1, Date& date2);
    
    tm* getDateInTm();
    
};
#endif /* date_hpp */
