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

SCENARIO("Date in task")
{
    Task task1{"task1"};

    Date date1{"2024-03-06"};
    task1.setDueDate(date1);
    REQUIRE(date1 == task1.getDueDate());
    REQUIRE(task1.getDueDate().str() == "2024-3-6");

    Date date2{"1111-11-11"};
    task1.getDueDate().setDate(1111, 11, 11);
    REQUIRE(task1.getDueDate().str() == "1111-11-11");

    REQUIRE(date2 == task1.getDueDate());

    REQUIRE(task1.str() == "{\"completed\":false,\"dueDate\":\"1111-11-11\",\"tags\":[]}");
} // SCENARIO

SCENARIO("tag editing")
{
    Task task1{"task1"};

    task1.addTag("a");
    task1.addTag("b");
    task1.addTag("c");
    task1.addTag("d");

    REQUIRE(task1.numTags() == 4);
    REQUIRE(task1.containsTag("a"));

    REQUIRE(task1.deleteTag("a"));
    REQUIRE(task1.numTags() == 3);
    REQUIRE_THROWS_AS(task1.deleteTag("a"), std::out_of_range);
    REQUIRE_THROWS_WITH(task1.deleteTag("a"), "tag not found");

    REQUIRE(task1.numTags() == 3);
    REQUIRE_FALSE(task1.containsTag("a"));

    REQUIRE_FALSE(task1.addTag("b"));

    std::vector<std::string> listOfTags{"b", "c", "d"};
    REQUIRE(task1.getTags() == listOfTags);

    REQUIRE(task1.str() == "{\"completed\":false,\"dueDate\":\"\",\"tags\":[\"b\",\"c\",\"d\"]}");
}

SCENARIO("tag comparison")
{
    Task task1{"task1"};
    task1.addTag("a");
    task1.addTag("b");

    Task task1Alt{"task1"};
    task1Alt.addTag("a");
    task1Alt.addTag("b");

    Task task2{"task2"};
    task2.addTag("a");
    task2.addTag("b");

    Task task3{"task3"};
    task3.addTag("1");
    task3.addTag("b");

    Task task4{"task4"};
    task4.addTag("1");
    task4.addTag("2");

    Task task5{"task1"};
    task4.addTag("1");
    task4.addTag("2");

    Task task6{"task1"};
    task4.addTag("a");
    task4.addTag("2");

    REQUIRE(task1 == task1);
    REQUIRE(task1 == task1Alt);
    REQUIRE_FALSE(task1 == task2);
    REQUIRE_FALSE(task1 == task3);
    REQUIRE_FALSE(task1 == task4);
    REQUIRE_FALSE(task1 == task5);
    REQUIRE_FALSE(task1 == task6);
}
