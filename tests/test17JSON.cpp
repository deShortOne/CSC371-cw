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

#include <fstream>
#include <iostream>
#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/371todo.h"
#include "BaseTest.h"

SCENARIO("SET UP17")
{
    REQUIRE(fileExists(filePath));
    REQUIRE_NOTHROW(resetDbFile());
}

SCENARIO("Print out not found things")
{
    GIVEN("Invalid project name")
    {
        Argv argvObj({"test", "--action", "JsOn", "--project", "_project1"});
        auto **argv = argvObj.argv();
        auto argc = argvObj.argc();

        std::stringstream buffer;
        CoutRedirectv2 originalBuffer{buffer.rdbuf()};
        std::stringstream bufferError;
        CerrRedirect originalBufferError{bufferError.rdbuf()};

        REQUIRE_NOTHROW(App::run(argc, argv));

        std::string output = buffer.str();
        REQUIRE(output == "");
        std::string outputError = bufferError.str();
        REQUIRE(outputError == "Error: invalid project argument(s).");
    }
    GIVEN("Valid project, invalid task")
    {
        Argv argvObj({"test", "--action", "JsOn", "--project", "CSC371", "--task", "do actual work"});
        auto **argv = argvObj.argv();
        auto argc = argvObj.argc();

        std::stringstream buffer;
        CoutRedirectv2 originalBuffer{buffer.rdbuf()};
        std::stringstream bufferError;
        CerrRedirect originalBufferError{bufferError.rdbuf()};

        REQUIRE_NOTHROW(App::run(argc, argv));

        std::string output = buffer.str();
        REQUIRE(output == "");
        std::string outputError = bufferError.str();
        REQUIRE(outputError == "Error: invalid task argument(s).");
    }
    GIVEN("Invalid project, invalid task")
    {
        Argv argvObj({"test", "--action", "JsOn", "--project", "_project1", "--task", "write unit tests"});
        auto **argv = argvObj.argv();
        auto argc = argvObj.argc();

        std::stringstream buffer;
        CoutRedirectv2 originalBuffer{buffer.rdbuf()};
        std::stringstream bufferError;
        CerrRedirect originalBufferError{bufferError.rdbuf()};

        REQUIRE_NOTHROW(App::run(argc, argv));

        std::string output = buffer.str();
        REQUIRE(output == "");
        std::string outputError = bufferError.str();
        REQUIRE(outputError == "Error: invalid project argument(s).");
    }
}
