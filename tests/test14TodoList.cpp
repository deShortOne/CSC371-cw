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

std::string filename = "./tests/myowntest.json";

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

SCENARIO("Edit projects")
{
    Task task1{"task1"};
    task1.addTag("a");
    task1.addTag("b");

    Task task2{"task2"};
    task1.addTag("c");
    task1.addTag("d");

    Project project{"project1"};
    project.addTask(task1);
    project.addTask(task2);

    Project project2{"project2"};
    project2.addTask(task1);
    project2.addTask(task2);

    TodoList tl{};
    REQUIRE(tl.addProject(project));
    REQUIRE(tl.addProject(project2));

    REQUIRE_FALSE(tl.addProject(project2));
    REQUIRE(tl.containsProject("project1"));
    REQUIRE(tl.containsProject("project2"));
    REQUIRE_FALSE(tl.containsProject("project3"));
    REQUIRE(tl.size() == 2);

    REQUIRE(tl.getProject("project1") == project);
    REQUIRE(tl.getProject("project2") == project2);
    REQUIRE_THROWS_AS(tl.getProject("project3"), std::out_of_range);
    REQUIRE_THROWS_WITH(tl.getProject("project3"), "That project doesn't exist!");

    REQUIRE(tl.deleteProject("project1"));
    REQUIRE_THROWS_AS(tl.deleteProject("project1"), std::out_of_range);
    REQUIRE_THROWS_WITH(tl.deleteProject("project1"), "That project doesn't exist!");
    REQUIRE(tl.size() == 1);
}

SCENARIO("save and load")
{
    Task task1{"task1"};
    task1.addTag("a");
    task1.addTag("b");

    Task task2{"task2"};
    task1.addTag("c");
    task1.addTag("d");

    Project project{"project1"};
    project.addTask(task1);
    project.addTask(task2);

    Project project2{"project2"};
    project2.addTask(task1);
    project2.addTask(task2);

    TodoList tl{};
    REQUIRE(tl.addProject(project));
    REQUIRE(tl.addProject(project2));

    tl.save(filename);

    TodoList tl2{};
    tl2.load(filename);

    REQUIRE(tl == tl2);
}
