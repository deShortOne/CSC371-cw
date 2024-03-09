// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: Thomas Reitmaier
//         thomas.reitmaier@swansea.ac.uk
//         Martin Porcheron (adapted from)
//         m.a.w.porcheron@swansea.ac.uk
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------
// Catch2 — https://github.com/catchorg/Catch2
// Catch2 is licensed under the BOOST license
// -----------------------------------------------------
// This file contains tests for the action program
// argument.
// -----------------------------------------------------

#include "../src/lib_catch.hpp"

#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/371todo.h"

SCENARIO("Date")
{
    Date date1{"2024-03-06"};
    REQUIRE(date1.str() == "2024-3-6");
    date1.setDate(1111, 11, 11);
    REQUIRE(date1.str() == "1111-11-11");

    Date date2{"1111-11-11"};
    REQUIRE(date1 == date2);
}

SCENARIO("Leap year")
{
    Date date1{};
    REQUIRE(date1.isValidDate(2024, 2, 29));
    REQUIRE_FALSE(date1.isValidDate(2023, 2, 29));
    REQUIRE_FALSE(date1.isValidDate(2022, 2, 29));
    REQUIRE(date1.isValidDate(2028, 2, 29));
}

SCENARIO("Less than operator")
{
    Date date1{};
    Date date2{};

    REQUIRE(date1.str() == "");
    REQUIRE_FALSE(date1 < date2);

    date1.setDateFromString("2024-3-9");
    date2.setDateFromString("2024-3-10");
    REQUIRE(date1 < date2);
    REQUIRE_FALSE(date2 < date1);

    date1.setDateFromString("2024-2-9");
    date2.setDateFromString("2024-3-9");
    REQUIRE(date1 < date2);
    REQUIRE_FALSE(date2 < date1);

    date1.setDateFromString("2022-3-9");
    date2.setDateFromString("2024-3-9");
    REQUIRE(date1 < date2);
    REQUIRE_FALSE(date2 < date1);
}
