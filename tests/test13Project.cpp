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

SCENARIO("Merge 2 tasks with same identifier")
{
    Task task1{"task1"};
    task1.addTag("a");
    task1.addTag("b");
    task1.addTag("c");
    task1.addTag("d");

    Task task2{"task1"};
    task2.addTag("c");
    task2.addTag("d");
    task2.addTag("e");
    task2.addTag("f");

    Task taskAnswer{"task1"};
    taskAnswer.addTag("a");
    taskAnswer.addTag("b");
    taskAnswer.addTag("c");
    taskAnswer.addTag("d");
    taskAnswer.addTag("e");
    taskAnswer.addTag("f");

    Project project{"new Project"};
    project.addTask(task1);
    project.addTask(task2);

    REQUIRE(project.size() == 1);
    REQUIRE(project.getTask("task1") == taskAnswer);
}

SCENARIO("add tasks with different identifiers")
{
    Task task1{"task1"};
    task1.addTag("a");
    task1.addTag("b");

    Task task2{"task2"};
    task2.addTag("c");
    task2.addTag("d");

    Task task3{"task3"};

    Project project{"new Project"};
    project.addTask(task1);
    project.addTask(task2);

    REQUIRE(project.size() == 2);
    REQUIRE(project.getTask("task1") == task1);
    REQUIRE(project.getTask("task2") == task2);

    std::vector<Task> allProjects{task1, task2};
    REQUIRE(project.getTasks() == allProjects);

    REQUIRE(project.newTask("task1") == task1);
    REQUIRE(project.newTask("task2") == task2);
    REQUIRE(project.newTask("task3") == task3); // Added task here!
    REQUIRE(project.findTask("task2").base()->str() == task2.str());
    REQUIRE(project.containsTask("task1"));
    REQUIRE(project.containsTask("task2"));

    REQUIRE_THROWS_AS(project.deleteTask("bad"), NoTaskError);
    REQUIRE_THROWS_WITH(project.deleteTask("bad"), "unknown task with identifier 'bad'");
    REQUIRE(project.size() == 3);
    REQUIRE(project.deleteTask("task1"));
    REQUIRE(project.size() == 2);
    REQUIRE_FALSE(project.containsTask("task1"));
    REQUIRE(project.containsTask("task2"));
}
