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

// Regex for date format
// Change to "^[[:digit:]]{4}-[[:digit:]]{2}-[[:digit:]]{2}$" to enforce YYYY-MM-DD
std::regex Date::dateRegex("^[[:digit:]]{1,4}-[[:digit:]]{1,2}-[[:digit:]]{1,2}$");

/**
 * Returns true if valid date is input.
 *
 * @param year year
 * @param month month
 * @param day day
 * @return true if valid date is input
 */
bool Date::isValidDate(const unsigned int year, const unsigned int month, const unsigned int day)
{
    if (month < 1 || month > 12 ||
        day < 1 || day > 31)
    {
        return false;
    }
    bool monthHas31Days = month == 1 ||
                          month == 3 ||
                          month == 5 ||
                          month == 7 ||
                          month == 8 ||
                          month == 10 ||
                          month == 12;

    if (day > 28)
    {
        if (day == 29 && (month != 2 || year % 4 != 0))
        {
            return false;
        }
        else if (day == 30 && month == 2)
        {
            return false;
        }
        else if (day == 31 && !monthHas31Days)
        {
            return false;
        }
    }
    return true;
}

/**
 * Provided default constructor to create an unitialised date.
 */
Date::Date()
{
    resetValues();
}

/**
 * Provided default constructor to create an itialised date. Calls @code{setDateFromString()}.
 *
 * @throw invalid date
 */
Date::Date(std::string date)
{
    resetValues();
    setDateFromString(date);
}

/**
 * Reset date to unitialised date.
 */
void Date::resetValues() noexcept
{
    this->year = 0;
    this->month = 0;
    this->day = 0;
    this->initialized = false;
}

/**
 * Sets the date based on the input string.
 *
 * If date is valid, this object sets @code{initialised} to true.
 *
 * @param dateArgs format is YYYY-MM-DD
 * @throw runtime_error if date is invalid
 */
void Date::setDateFromString(const std::string &dateArgs)
{
    if (!dateArgs.length())
    {
        resetValues();
        return;
    }

    std::cmatch m;
    if (!std::regex_match(dateArgs.c_str(), m, dateRegex))
    {
        resetValues();
        throw std::runtime_error("Invalid date argument, ensure format is YYYY-MM-DD, instead got '" + dateArgs + "'");
    }

    std::stringstream test(dateArgs);
    std::string yearString;
    std::string monthString;
    std::string dayString;
    std::getline(test, yearString, '-');
    std::getline(test, monthString, '-');
    std::getline(test, dayString, '-');

    this->year = std::stoi(yearString);
    this->month = std::stoi(monthString);
    this->day = std::stoi(dayString);
    this->initialized = true;

    if (!isValidDate(this->year, this->month, this->day))
    {
        resetValues();
        throw std::runtime_error("Invalid date, got '" + dateArgs + "'");
    }
}

/**
 * Returns true if this object is initialised.
 *
 * @return true if object is initialised.
 */
bool Date::isInitialised() const noexcept
{
    return this->initialized;
}
/**
 * Returns string format of the date. If uninitialised, an empty string will be returned.
 *
 * @return std::string representation of the Date object in YYYY-MM-DD format
 */
const std::string Date::str() const noexcept
{
    if (!isInitialised())
    {
        return "";
    }
    std::stringstream ss;
    ss
        // << std::setw(4) << std::setfill('0')
        << this->year
        << "-"
        // << std::setw(2) << std::setfill('0')
        << this->month
        << "-"
        // << std::setw(2) << std::setfill('0')
        << this->day;

    return ss.str();
}

/**
 * Sets the date based on inputs. If date is invalid, then the previous state will be kept.
 *
 * @param year year
 * @param month month
 * @param day day
 * @throw invalid date
 */
void Date::setDate(const unsigned int year, const unsigned int month, const unsigned int day)
{
    if (!isValidDate(year, month, day))
    {
        throw std::runtime_error("Invalid input date, reverting to previous state");
    }
    this->year = year;
    this->month = month;
    this->day = day;
    this->initialized = true;
}

/**
 * If initialised, returns the year, otherwise returns 0.
 *
 * @return year
 */
unsigned int Date::getYear() const noexcept
{
    return initialized ? this->year : 0;
}

/**
 * If initialised, returns the month, otherwise returns 0.
 *
 * @return month
 */
unsigned int Date::getMonth() const noexcept
{
    return initialized ? this->month : 0;
}

/**
 * If initialised, returns the day, otherwise returns 0.
 *
 * @return day
 */
unsigned int Date::getDay() const noexcept
{
    return initialized ? this->day : 0;
}

/**
 * Returns true if date inputs are the same.
 *
 * @param rhs other date to compare with
 * @return true if other date is the same
 */
bool Date::operator==(const Date &rhs) const noexcept
{
    return rhs.initialized == this->initialized &&
           rhs.day == this->day &&
           rhs.month == this->month &&
           rhs.year == this->year;
}

/**
 * Less than operator compares data, ignores initialised.
 *
 * @return true if first date is chronologically before second
 */
bool Date::operator<(const Date &rhs) const noexcept
{
    if (this->year != rhs.year)
    {
        return this->year < rhs.year;
    }
    else if (this->month != rhs.month)
    {
        return this->month < rhs.month;
    }
    else if (this->day != rhs.day)
    {
        return this->day < rhs.day;
    }
    return false; // they the same
}
