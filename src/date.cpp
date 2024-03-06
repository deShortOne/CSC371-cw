// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: 2010573
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "date.h"

// Provided default constructor to create an unitialised date.
Date::Date() : year(0), month(0), day(0), initialized(false) {}

// TODO write a function setDateFromString that takes a string argument in
// "YYYY-MM-DD" format and sets the appropriate member variables (year, month,
// day, and initialised). If dateString is empty reset the object to its
// uninitialised state (see default constructor). If dateString is not valid
// throw an appropriate exception.
// Example:
//  Date d = Date();
//  d.setDateString("2024-01-01");
void Date::setDateFromString(std::string dateArgs)
{
    if (!dateArgs.compare(""))
    {
        this->year = 0;
        this->month = 0;
        this->day = 0;
        this->initialized = false;
        return;
    }
    if (dateArgs.size() != 10 ||
        dateArgs.substr(4, 1).compare("-") ||
        dateArgs.substr(7, 1).compare("-"))
    {
        throw std::runtime_error("Invalid date argument, ensure format is YYYY-MM-DD, got '" + dateArgs + "'");
    }

    try
    {
        this->year = std::stoi(dateArgs.substr(0, 4));
        this->month = std::stoi(dateArgs.substr(5, 2));
        this->day = std::stoi(dateArgs.substr(8, 2));
        this->initialized = true;

        if (this->month < 1 || this->month > 12 ||
            this->day < 1 || this->day > 31)
        {
            throw std::exception();
        }
        bool monthHas31Days = this->month == 1 ||
                              this->month == 3 ||
                              this->month == 5 ||
                              this->month == 7 ||
                              this->month == 8 ||
                              this->month == 10 ||
                              this->month == 12;

        if (this->day > 28)
        {
            if (this->day == 29 && (this->month != 2 || this->year % 4 == 0))
            {
                throw std::exception();
            }
            else if (day == 30 && month == 2)
            {
                throw std::exception();
            }
            else if (day == 31 && !monthHas31Days)
            {
                throw std::exception();
            }
        }
    }
    catch (const std::exception &ex)
    {
        this->year = 0;
        this->month = 0;
        this->day = 0;
        this->initialized = false;
        throw std::runtime_error("Invalid date");
    }
}
// TODO Write a function, isInitialised, that takes no parameters and returns true
//  if the Date object is initialised, and false if it is NOT initialised.
// Example:
//  Date d = Date();
//  if(d.isInitialised()) {
//    ...
//  }
bool Date::isInitialised() const
{
    return this->initialized;
}
// TODO Write a function, str, that takes no parameters and returns a
// std::string representation of the Date object in YYYY-MM-DD format.  If the
// Date object is NOT initialised, return an empty string.
// Example:
//  Date d = Date();
//  d.setDate(2024,1,1);
//  std::cout << d.str() << std::endl;
std::string Date::str() const
{
    if (!isInitialised())
    {
        return "";
    }
    std::stringstream ss;
    ss << std::setw(4) << std::setfill('0')
       << this->year
       << "-"
       << std::setw(2) << std::setfill('0')
       << this->month
       << "-"
       << std::setw(2) << std::setfill('0')
       << this->day;

    return ss.str();
}
// TODO create a function, setDate, that takes three parameters: year, month,
// day and sets the appropriate member variables to those parameters and also
// sets the initilized flag.
// Example:
//  Date d = Date();
//  d.setDate(2024, 1, 1);
void Date::setDate(const int year, const int month, const int day)
{
    this->year = year;
    this->month = month;
    this->day = day;
    this->initialized = true;
}
// TODO Write a function, getYear, that takes no parameters and returns year
// member variable
//  Date d = Date();
//  auto year = d.getYear();
unsigned int Date::getYear() const
{
    return initialized ? this->year : -1;
}

// TODO Write a function, getMonth, that takes no parameters and returns month
// member variable
//  Date d = Date();
//  auto month = d.getMonth();
unsigned int Date::getMonth() const
{
    return initialized ? this->month : -1;
}

// TODO Write a function, getDay, that takes no parameters and returns day
// member variable
//  Date d = Date();
//  auto day = d.getDay();
unsigned int Date::getDay() const
{
    return initialized ? this->day : -1;
}

// TODO Write an == operator overload for the Date class, such that two
// Date objects are equal only if they have the same member variables.
// Example
//  Date d1 = Date();
//   d1.setDate(2024, 1, 1);
//   Date d2 = Date();
//   d2.setDate(2024, 1, 2);
//   if (d1 == d2) {
//     ...
//   }
// !!TODO check for initialised?
bool Date::operator==(const Date &rhs) const
{
    return rhs.initialized == this->initialized &&
           rhs.day == this->day &&
           rhs.month == this->month &&
           rhs.year == this->year;
}
// TODO Write an < operator overload for the Date class, that returns true if
// the first Date object is chronologically before the second date object.
// Otherwise return false. Note: You can ignore the 'initialised' member
// variable when drawing the comparison.
// Example
//  Date d1 = Date();
//   d1.setDate(2024, 1, 1);
//   Date d2 = Date();
//   d2.setDate(2024, 1, 2);
//   if (d1 < d2) {
//     ...
//   }
bool Date::operator<(const Date &rhs) const
{
    return this->day < rhs.day ||
           this->month < rhs.month ||
           this->year < rhs.year;
}
