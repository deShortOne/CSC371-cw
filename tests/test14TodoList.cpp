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

SCENARIO("Compare todo lists")
{
    Task task1{"task1"};
    task1.addTag("a");
    task1.addTag("b");

    Task task2{"task2"};
    task2.addTag("a");
    task2.addTag("b");

    Project project1{"new Project1"};
    project1.addTask(task1);
    project1.addTask(task2);

    Project project2{"new Project2"};
    project2.addTask(task1);
    project2.addTask(task2);

    Project project3{"++++++++ Project"};
    project3.addTask(task1);
    project3.addTask(task2);

    TodoList tl1{};
    tl1.addProject(project1);
    tl1.addProject(project2);

    TodoList tl2{};
    tl2.addProject(project1);
    tl2.addProject(project2);

    TodoList tl3{};
    tl3.addProject(project1);
    tl3.addProject(project3); // project 3

    REQUIRE(tl1 == tl2);
    REQUIRE_FALSE(tl1 == tl3);
}

SCENARIO("Add project")
{
    Task task1{"task1"};
    task1.addTag("a");
    task1.addTag("b");

    Task task2{"task2"};
    task1.addTag("c");
    task1.addTag("d");

    Project project{"new Project"};
    project.addTask(task1);
    project.addTask(task2);

    Project project2{"new Project 2"};
    project2.addTask(task1);
    project2.addTask(task2);

    TodoList tl{};
    tl.addProject(project);
    tl.addProject(project2);

    REQUIRE(tl.size() == 2);
}
