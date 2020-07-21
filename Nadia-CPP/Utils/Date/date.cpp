//
//  date.cpp
//  Nadia-CPP
//
//  Created by Dean Lee on 11/2/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "date.hpp"
#include <regex>
#include <array>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <map>
using namespace std;

string day[] = {"Mon", "Tue", "Wed", "Thur", "Fri", "Sat", "Sun"};
map<string, int> monthMap = {{"Jan", 0}, {"Feb", 1}, {"Mar", 2}, {"Apr", 3}, {"May", 4}, {"Jun", 5}, {"Jul", 6}, {"Aug", 7}, {"Sep", 8}, {"Oct", 9}, {"Nov", 10}, {"Dec", 11}};
regex dateFormat1("D{1,2}/M{1,3}/Y{4}"); //handles 'D/M/YYYY', 'DD/MM/YYYY', 'D/MMM/YYYY', and 'DD/MMM/YYYY'
regex dateFormat2("M{1,3}/D{1,2}/Y{4}"); //handles 'M/D/YYYY', 'MM/DD/YYYY', 'MMM/D/YYYY', and 'MMM/DD/YYYY'
regex dateFormat3("Y{4}-M{1,3}-D{1,2}"); //handles 'YYYY-M-D', 'YYYY-MM-DD', 'YYYY-MMM-D', and 'YYYY-MMM-DD'
regex dateFormat4("Y{4} M{1,3} D{1,2}"); //handles 'YYYY M D', 'YYYY MM DD','YYYY MMM D', and 'YYYY MMM DD'
regex dateFormat5("D{1,2} M{1,3} Y{4}"); //handles 'D M YYYY', 'DD MM YYYY', D MMM YYYY' and 'DD MMM YYYY'
regex dateFormat6("M{1,3} D{1,2} Y{4}"); //handles 'M D YYYY', 'MM DD YYYY', 'MMM D YYYY' and 'MMM DD YYYY'
array<regex,11> DateFormatReg = {dateFormat1, dateFormat2, dateFormat3, dateFormat4, dateFormat5, dateFormat6};

regex format1("[0-9]{1,2}/[0-9]{1,2}/[0-9]{4}"); //handles 'D/M/YYYY', 'DD/MM/YYYY'
regex format2("[0-9]{1,2}/[a-zA-Z]{3}/[0-9]{4}"); //handles 'D/MMM/YYYY', and 'DD/MMM/YYYY'
regex format3("[a-zA-Z]{3}/[0-9]{1,2}/[0-9]{4}"); //handles 'MMM/D/YYYY', and 'MMM/DD/YYYY'
regex format4("[0-9]{4}-[a-zA-Z]{1,3}-[0-9]{1,2}"); //handles 'YYYY-MMM-D', and 'YYYY-MMM-DD'
regex format5("[0-9]{4}-[0-9]{1,2}-[0-9]{1,2}");  //handles 'YYYY-M-D', 'YYYY-MM-DD',
regex format6("[0-9]{4}\\s[a-zA-Z]{3}\\s[0-9]{1,2}"); //handles 'YYYY MMM D', and 'YYYY MMM DD'
regex format7("[0-9]{1,2}\\s[0-9]{1,2}\\s[0-9]{4}");//handles 'D M YYYY' and 'DD MM YYYY',
regex format8("[0-9][1,2}\\s[a-zA-Z]{3}\\s[0-9]{4}"); //handles 'D MMM YYYY' and 'DD MMM YYYY'
regex format9("[a-zA-Z]{3}\\s[0-9]{1,2}\\s[0-9]{4}");//handles 'MMM D YYYY' and 'MMM DD YYYY'
array<regex,11> DateInStringFormatReg = {format1, format2, format3, format4, format5, format6, format7, format8, format9};
smatch match;

regex slashDelimiter("\\/");
regex hyphenDelimiter("\\-");
regex spaceDelimiter("\\s");



Date::Date()
{
    time_t now = time(0);
    date = gmtime(&now);
    
    mDay = date->tm_mday; //represents date from 1 to 31
    wDayString = day[date->tm_wday]; //represents day from Mon to Sun
    wDayInt = date->tm_wday; //represnts day from 0 to 6
    year = date->tm_year+1900;  //represents year e.g. 2020
    monthInt = date->tm_mon+1; //represents month from 1 to 12

    for(auto it = monthMap.begin(); it != monthMap.end(); it++)
    {
        if(it->second == date->tm_mon)
        {
            monthString = it->first;
        }
    }
}


Date::Date(string dateInString, string dateFormat)
{
    date = dateInit();
    for(int i = 0; i < DateFormatReg.size(); i++)
    {
        if(regex_match(dateFormat, match, DateFormatReg[i]))
        {
            switch(i)
            {
                case 0://handles 'D/M/YYYY', 'DD/MM/YYYY', 'D/MMM/YYYY', and 'DD/MMM/YYYY'
                {
                    vector<string> dateFormatSplitList(
                                                       sregex_token_iterator(dateFormat.begin(), dateFormat.end(), slashDelimiter, -1),
                                                       sregex_token_iterator()
                                                       );

                    if(dateFormatSplitList.at(1).compare("MMM") == 0)
                    {
                        char monthChar[3];
                        sscanf(dateInString.c_str(), "%d/%3c/%d",&date->tm_mday, monthChar, &year);
                        string tempMonthString(monthChar, 3);

                        date->tm_mon = monthMap[monthString];

                        monthString = tempMonthString;
                        monthInt = (monthMap[monthString]+1);
                        
                    }
                    else
                    {
                        int month = 0;
                        sscanf(dateInString.c_str(), "%d/%d/%d",&date->tm_mday, &month, &year);

                        date->tm_mon = (month -1);
                        
                        monthInt = month;
                        for(auto it = monthMap.begin(); it != monthMap.end(); it++)
                        {
                            if(it->second == date->tm_mon)
                            {
                                monthString = it->first;
                            }
                        }
                    }
                    break;
                }
                case 1://handles 'M/D/YYYY', 'MM/DD/YYYY', 'MMM/D/YYYY', and 'MMM/DD/YYYY'
                {
                    vector<string> dateFormatSplitList(
                                                       sregex_token_iterator(dateFormat.begin(), dateFormat.end(), slashDelimiter, -1),
                                                       sregex_token_iterator()
                                                       );
                    
                    if(dateFormatSplitList.at(0).compare("MMM") == 0)
                    {
                        char monthChar[3];
                        sscanf(dateInString.c_str(), "%3c/%d/%d",monthChar, &date->tm_mday, &year);
                        string tempMonthString(monthChar, 3);
                        date->tm_mon = monthMap[monthString];
                        
                        monthString = tempMonthString;
                        monthInt = (monthMap[monthString]+1);
                    }
                    else
                    {
                        int month = 0;
                        sscanf(dateInString.c_str(), "%d/%d/%d", &month, &date->tm_mday, &year);
                        date->tm_mon = (month -1);
                        monthInt = month;
                        for(auto it = monthMap.begin(); it != monthMap.end(); it++)
                        {
                            if(it->second == date->tm_mon)
                            {
                                monthString = it->first;
                            }
                        }
                    }
                    break;
                }
                case 2://handles 'YYYY-M-D', 'YYYY-MM-DD', 'YYYY-MMM-D', and 'YYYY-MMM-DD'
                {
                    vector<string> dateFormatSplitList(
                                                       sregex_token_iterator(dateFormat.begin(), dateFormat.end(), hyphenDelimiter, -1),
                                                       sregex_token_iterator()
                                                       );
                    
                    if(dateFormatSplitList.at(1).compare("MMM") == 0)
                    {
                        char monthChar[3];
                        sscanf(dateInString.c_str(), "%d-%3c-%d", &year, monthChar, &date->tm_mday);
                        string tempMonthString(monthChar, 3);
                        date->tm_mon = monthMap[monthString];
                        
                        monthString = tempMonthString;
                        monthInt = (monthMap[monthString]+1);
                    }
                    else
                    {
                        int month = 0;
                        sscanf(dateInString.c_str(), "%d-%d-%d", &year, &month, &date->tm_mday);
                        date->tm_mon = (month -1);
                        monthInt = month;
                        for(auto it = monthMap.begin(); it != monthMap.end(); it++)
                        {
                            if(it->second == date->tm_mon)
                            {
                                monthString = it->first;
                            }
                        }
                    }
                    break;
                }
                case 3:///handles 'YYYY M D', 'YYYY MM DD','YYYY MMM D', and 'YYYY MMM DD'
                {
                    vector<string> dateFormatSplitList(
                                                       sregex_token_iterator(dateFormat.begin(), dateFormat.end(), spaceDelimiter, -1),
                                                       sregex_token_iterator()
                                                       );
                    
                    if(dateFormatSplitList.at(1).compare("MMM") == 0)
                    {
                        char monthChar[3];
                        sscanf(dateInString.c_str(), "%d %3c %d", &year, monthChar, &date->tm_mday);
                        string tempMonthString(monthChar, 3);
                        date->tm_mon = monthMap[monthString];
                        
                        monthString = tempMonthString;
                        monthInt = (monthMap[monthString]+1);
                    }
                    else
                    {
                        int month = 0;
                        sscanf(dateInString.c_str(), "%d %d %d", &year, &month, &date->tm_mday);
                        date->tm_mon = (month -1);
                        monthInt = month;
                        for(auto it = monthMap.begin(); it != monthMap.end(); it++)
                        {
                            if(it->second == date->tm_mon)
                            {
                                monthString = it->first;
                            }
                        }
                    }
                    break;
                }
                case 4://handles 'D M YYYY', 'DD MM YYYY', D MMM YYYY' and 'DD MMM YYYY'
                {
                    vector<string> dateFormatSplitList(
                                                       sregex_token_iterator(dateFormat.begin(), dateFormat.end(), spaceDelimiter, -1),
                                                       sregex_token_iterator()
                                                       );
                    
                    if(dateFormatSplitList.at(1).compare("MMM") == 0)
                    {
                        char monthChar[3];
                        sscanf(dateInString.c_str(), "%d %3c %d", &date->tm_mday, monthChar, &year);
                        string tempMonthString(monthChar, 3);
                        date->tm_mon = monthMap[monthString];
                        
                        monthString = tempMonthString;
                        monthInt = (monthMap[monthString]+1);
                    }
                    else
                    {
                        int month = 0;
                        sscanf(dateInString.c_str(), "%d %d %d", &date->tm_mday, &month, &year);
                        date->tm_mon = (month -1);
                        monthInt = month;
                        for(auto it = monthMap.begin(); it != monthMap.end(); it++)
                        {
                            if(it->second == date->tm_mon)
                            {
                                monthString = it->first;
                            }
                        }
                    }
                    break;
                }
                default: //handles 'M D YYYY', 'MM DD YYYY', 'MMM D YYYY' and 'MMM DD YYYY'
                {
                    vector<string> dateFormatSplitList(
                                                       sregex_token_iterator(dateFormat.begin(), dateFormat.end(), spaceDelimiter, -1),
                                                       sregex_token_iterator()
                                                       );
                    
                    if(dateFormatSplitList.at(0).compare("MMM") == 0)
                    {
                        char monthChar[3];
                        sscanf(dateInString.c_str(), "%3c %d %d", monthChar, &date->tm_mday, &year);
                        string tempMonthString(monthChar, 3);
                        date->tm_mon = monthMap[monthString];
                        
                        monthString = tempMonthString;
                        monthInt = (monthMap[monthString]+1);
                    }
                    else
                    {
                        int month = 0;
                        sscanf(dateInString.c_str(), "%d %d %d", &month, &date->tm_mday, &year);
                        date->tm_mon = (month -1);
                        monthInt = month;
                        for(auto it = monthMap.begin(); it != monthMap.end(); it++)
                        {
                            if(it->second == date->tm_mon)
                            {
                                monthString = it->first;
                            }
                        }
                    }
                    break;
                }
            }
            date->tm_year = year - 1900;
            
            mDay = date->tm_mday; //represents date from 1 to 31
            wDayString = day[date->tm_wday]; //represents day from Mon to Sun
            wDayInt = date->tm_wday; //represnts day from 0 to 6
        }
    }
}

Date::Date(string dateInString)
{
    date = dateInit();
    string dateFormat;
    for(int i = 0; i < DateInStringFormatReg.size(); i++)
    {
        if(regex_match(dateInString, match, DateInStringFormatReg[i]))
        {
            switch(i)
            {
                case 0:  //handles 'D/M/YYYY', 'DD/MM/YYYY'
                    dateFormat = "DD/MM/YYYY";
                    new(this) Date(dateInString, dateFormat);
                    break;
                case 1:  //handles 'D/MMM/YYYY', and 'DD/MMM/YYYY'
                    dateFormat = "DD/MMM/YYYY";
                    new(this) Date(dateInString, dateFormat);
                    break;
                case 2:  //handles 'MMM/D/YYYY', and 'MMM/DD/YYYY'
                    dateFormat = "MMM/DD/YYYY";
                    new(this) Date(dateInString, dateFormat);
                    break;
                case 3: //handles 'YYYY-MMM-D', and 'YYYY-MMM-DD'
                    dateFormat = "YYYY/MMM/DD";
                    new(this) Date(dateInString, dateFormat);
                    break;
                case 4:  //handles 'YYYY-M-D', 'YYYY-MM-DD',
                    dateFormat = "YYYY/MM/DD";
                    new(this) Date(dateInString, dateFormat);
                    break;
                case 5://handles 'YYYY MMM D', and 'YYYY MMM DD'
                {
                    dateFormat = "YYYY MMM DD";
                    new(this) Date(dateInString, dateFormat);
                    break;
                }
                case 6:  //handles 'D M YYYY' and 'DD MM YYYY',
                {
                    dateFormat = "DD MM YYYY";
                    new(this) Date(dateInString, dateFormat);
                    break;
                }
                case 7:  //handles 'D MMM YYYY' and 'DD MMM YYYY'
                {
                    dateFormat = "DD MMM YYYY";
                    new(this) Date(dateInString, dateFormat);
                    break;
                }
                default:  //handles 'MMM D YYYY' and 'MMM DD YYYY'
                {
                    dateFormat = "MMM DD YYYY";
                    new(this) Date(dateInString, dateFormat);
                    break;
                }
            }
        }
    }
    
}

Date::Date(int inputDay, int inputMonth, int inputYear)
{
    date = dateInit();
    date->tm_year = inputYear - 1900 ;
    date->tm_mon = inputMonth - 1;
    date->tm_mday = inputDay;
    
    mDay = inputDay; //represents date from 1 to 31
    wDayString = day[date->tm_wday]; //represents day from Mon to Sun
    wDayInt = date->tm_wday; //represnts day from 0 to 6
    year = inputYear;  //represents year e.g. 2020
    monthInt = inputMonth; //represents month from 1 to 12
    for(auto it = monthMap.begin(); it != monthMap.end(); it++)
    {
        if(it->second == date->tm_mon)
        {
            monthString = it->first;
            break;
        }
    }
}

Date::Date(string inputDay, string inputMonth, string inputYear)
{
    int intDay = 0;
    istringstream(inputDay) >> intDay;
    
    int intMonth = 0;
    istringstream(inputMonth) >> intMonth;
    
    int intYear = 0;
    istringstream(inputYear) >> intYear;
      
    new(this) Date(intDay, intMonth, intYear);
}

int Date::getDateInInt()
{
    return mDay;
}

string Date::getDateInString()
{
    return to_string(mDay);
}

int Date::getWDayInt()
{
    return wDayInt;
}
string Date::getWDayString()
{
    return wDayString;
}

int Date::getMonthInt()
{
    return monthInt;
}
string Date::getMonthString()
{
    return monthString;
}

int Date::getYearInInt()
{
    return year;
}
string Date::getYearInString()
{
    return to_string(year);
}

string Date::getWholeDateValueInFormattedString(string dateFormat)
{
    string dateInFormat;
    stringstream ss;
    
    for(int i = 0; i < DateFormatReg.size(); i++)
    {
        if(regex_match(dateFormat, match, DateFormatReg[i]))
        {
            switch(i)
            {
                case 0: //handles 'D/M/YYYY', 'DD/MM/YYYY', 'D/MMM/YYYY', and 'DD/MMM/YYYY'
                {
                    vector<string> dateFormatSplitList(
                                                       sregex_token_iterator(dateFormat.begin(), dateFormat.end(), slashDelimiter, -1),
                                                       sregex_token_iterator()
                                                       );
                    if((dateFormatSplitList.at(0).compare("DD") == 0) && (getDateInInt() < 10))
                    {
                        ss << "0" << to_string(getDateInInt()) << "/";
                    }
                    else
                    {
                        ss << to_string(getDateInInt()) << "/";
                    }
                    
                    if(dateFormatSplitList.at(1).compare("MMM") == 0)
                    {
                        ss << getMonthString() << "/";
                    }
                    else if((dateFormatSplitList.at(1).compare("MM") == 0) && (getMonthInt() < 10))
                    {
                        
                        ss << "0" << to_string(getMonthInt()) << "/";
                    }
                    else
                    {
                        ss << to_string(getMonthInt()) << "/";
                    }
                    
                    ss << getYearInString();
                    break;
                }
                case 1:  //handles 'M/D/YYYY', 'MM/DD/YYYY', 'MMM/D/YYYY', and 'MMM/DD/YYYY'
                {
                    vector<string> dateFormatSplitList(
                                                       sregex_token_iterator(dateFormat.begin(), dateFormat.end(), slashDelimiter, -1),
                                                       sregex_token_iterator()
                                                       );
                    if(dateFormatSplitList.at(0).compare("MMM") == 0)
                    {
                        ss << getMonthString() << "/";
                    }
                    else if((dateFormatSplitList.at(0).compare("MM") == 0) && (getMonthInt() < 10))
                    {
                        
                        ss << "0" << to_string(getMonthInt()) << "/";
                    }
                    else
                    {
                        ss << to_string(getMonthInt()) << "/";
                    }
                    
                    if((dateFormatSplitList.at(1).compare("DD") == 0) && (getDateInInt() < 10))
                    {
                        ss << "0" << to_string(getDateInInt()) << "/";
                    }
                    else
                    {
                        ss << to_string(getDateInInt()) << "/";
                    }
                    
                    ss << getYearInString();
                    break;
                }
                case 2: //handles 'YYYY-M-D', 'YYYY-MM-DD', 'YYYY-MMM-D', and 'YYYY-MMM-DD'
                {
                    vector<string> dateFormatSplitList(
                                                       sregex_token_iterator(dateFormat.begin(), dateFormat.end(), hyphenDelimiter, -1),
                                                       sregex_token_iterator()
                                                       );
                    ss << getYearInString() << "-";
                    
                    if(dateFormatSplitList.at(1).compare("MMM") == 0)
                    {
                        ss << getMonthString() << "-";
                    }
                    else if((dateFormatSplitList.at(1).compare("MM") == 0) && (getMonthInt() < 10))
                    {
                        
                        ss << "0" << to_string(getMonthInt()) << "-";
                    }
                    else
                    {
                        ss << to_string(getMonthInt()) << "-";
                    }
                    
                    if((dateFormatSplitList.at(2).compare("DD") == 0) && (getDateInInt() < 10))
                    {
                        ss << "0" << to_string(getDateInInt());
                    }
                    else
                    {
                        ss << to_string(getDateInInt());
                    }
                    
                    break;
                }
                case 3: //handles 'YYYY M D', 'YYYY MM DD','YYYY MMM D', and 'YYYY MMM DD'
                {
                    vector<string> dateFormatSplitList(
                                                       sregex_token_iterator(dateFormat.begin(), dateFormat.end(), spaceDelimiter, -1),
                                                       sregex_token_iterator()
                                                       );
                    ss << getYearInString() << " ";
                    
                    if(dateFormatSplitList.at(1).compare("MMM") == 0)
                    {
                        ss << getMonthString() << " ";
                    }
                    else if((dateFormatSplitList.at(1).compare("MM") == 0) && (getMonthInt() < 10))
                    {
                        
                        ss << "0" << to_string(getMonthInt()) << " ";
                    }
                    else
                    {
                        ss << to_string(getMonthInt()) << " ";
                    }
                    
                    if((dateFormatSplitList.at(2).compare("DD") == 0) && (getDateInInt() < 10))
                    {
                        ss << "0" << to_string(getDateInInt());
                    }
                    else
                    {
                        ss << to_string(getDateInInt());
                    }
                    break;
                }
                case 4: //handles 'D M YYYY', 'DD MM YYYY', D MMM YYYY' and 'DD MMM YYYY'
                {
                    vector<string> dateFormatSplitList(
                                                       sregex_token_iterator(dateFormat.begin(), dateFormat.end(), spaceDelimiter, -1),
                                                       sregex_token_iterator()
                                                       );
                    if((dateFormatSplitList.at(0).compare("DD") == 0) && (getDateInInt() < 10))
                    {
                        ss << "0" << to_string(getDateInInt()) << " ";
                    }
                    else
                    {
                        ss << to_string(getDateInInt()) << " ";
                    }
                    
                    if(dateFormatSplitList.at(1).compare("MMM") == 0)
                    {
                        ss << getMonthString() << " ";
                    }
                    else if((dateFormatSplitList.at(1).compare("MM") == 0) && (getMonthInt() < 10))
                    {
                        
                        ss << "0" << to_string(getMonthInt()) << " ";
                    }
                    else
                    {
                        ss << to_string(getMonthInt()) << " ";
                    }
                    
                    ss << getYearInString();
                    break;
                }
                default: //handles 'M D YYYY', 'MM DD YYYY', 'MMM D YYYY' and 'MMM DD YYYY'
                {
                    vector<string> dateFormatSplitList(
                                                       sregex_token_iterator(dateFormat.begin(), dateFormat.end(), spaceDelimiter, -1),
                                                       sregex_token_iterator()
                                                       );
                    
                    if(dateFormatSplitList.at(0).compare("MMM") == 0)
                    {
                        ss << getMonthString() << " ";
                    }
                    else if((dateFormatSplitList.at(0).compare("MM") == 0) && (getMonthInt() < 10))
                    {
                        
                        ss << "0" << to_string(getMonthInt()) << " ";
                    }
                    else
                    {
                        ss << to_string(getMonthInt()) << " ";
                    }
                    
                    if((dateFormatSplitList.at(1).compare("DD") == 0) && (getDateInInt() < 10))
                    {
                        ss << "0" << to_string(getDateInInt()) << " ";
                    }
                    else
                    {
                        ss << to_string(getDateInInt()) << " ";
                    }
                    
                    ss << getYearInString();
                    break;
                }
            }
        }
    }
    
    dateInFormat = ss.str();
    return dateInFormat;
}

string Date::getWholeDateValueInString()
{
    string dateInString;
    stringstream ss;
    ss << getYearInString() << "-" << getMonthInt() << "-" << getDateInInt();
    dateInString = ss.str();
    return dateInString;
}

bool Date::isEqual(Date& anotherDate)
{
    return this->getWholeDateValueInString().compare(anotherDate.getWholeDateValueInString()) == 0;
}

bool Date::isAfter(Date& anotherDate)
{
    bool isAfter = false;
    
    if(this->getYearInInt() > anotherDate.getYearInInt())
    {
        return true;
    }
    else if(this->getYearInInt() < anotherDate.getYearInInt())
    {
        return false;
    }
    
    if(this->getMonthInt() > anotherDate.getMonthInt())
    {
        return true;
    }
    else if(this->getMonthInt() < anotherDate.getMonthInt())
    {
        return false;
    }
    
    if(this->getDateInInt() > anotherDate.getDateInInt())
    {
        return true;
    }
    else if(this->getDateInInt() < anotherDate.getDateInInt())
    {
        return false;
    }
    
    return isAfter;
}

bool Date::isBefore(Date& anotherDate)
{
    bool isBefore = false;
    
    if(this->getYearInInt() < anotherDate.getYearInInt())
    {
        return true;
    }
    else if(this->getYearInInt() > anotherDate.getYearInInt())
    {
        return false;
    }
    
    if(this->getMonthInt() < anotherDate.getMonthInt())
    {
        return true;
    }
    else if(this->getMonthInt() > anotherDate.getMonthInt())
    {
        return false;
    }
    
    if(this->getDateInInt() < anotherDate.getDateInInt())
    {
        return true;
    }
    else if(this->getDateInInt() > anotherDate.getDateInInt())
    {
        return false;
    }
    
    return isBefore;
}

int Date::daysDiffBetween(Date& date1, Date& date2)
{
    long int diff = difftime(mktime(date1.getDateInTm()), mktime(date2.getDateInTm()));
    return (int)diff/86400;
}

int Date::monthsDiffBetween(Date& date1, Date& date2)
{
    long int diff = difftime(mktime(date1.getDateInTm()), mktime(date2.getDateInTm()));
    return (int)diff/86400*12;
}
int Date::yearsDiffBetween(Date& date1, Date& date2)
{
    long int diff = difftime(mktime(date1.getDateInTm()), mktime(date2.getDateInTm()));
    return (int)diff/86400*365.25;
}

tm* Date::getDateInTm()
{
    return date;
}

tm* Date::dateInit()
{
    time_t rawtime;
    time(&rawtime);
    return localtime(&rawtime);
}

Date::~Date()
{

}
