// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: 2010573
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------
// An Date class that contains the following member variables
// - year
// - month
// - day
// - initialised
//
// A Date object should only be set to initialised if it is a valid date.
// Otherwise it is should remain unintialised.
// -----------------------------------------------------

#ifndef DATE_H
#define DATE_H

#include <regex>
#include "lib_json.hpp"

class Date
{
private:
    unsigned int year, month, day;
    bool initialized;

public:
    static std::regex dateRegex;
    static bool isValidDate(const unsigned int year, const unsigned int month, const unsigned int day);

    Date();
    Date(std::string date);
    void resetValues() noexcept;
    void setDateFromString(const std::string &dateArgs);
    bool isInitialised() const noexcept;
    const std::string str() const noexcept;
    void setDate(const unsigned int year, const unsigned int month, const unsigned int day);
    unsigned int getYear() const noexcept;
    unsigned int getMonth() const noexcept;
    unsigned int getDay() const noexcept;
    bool operator==(const Date &rhs) const noexcept;
    bool operator<(const Date &rhs) const noexcept;
};

#endif // DATE_H
