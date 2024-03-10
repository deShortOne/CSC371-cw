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

SCENARIO("SET UP19")
{
    REQUIRE(fileExists(filePath));
    REQUIRE_NOTHROW(resetDbFile());
}

SCENARIO("Invalid data")
{
    WHEN("Delete invalid project")
    {
        // also testing for case insensitivity
        Argv argvObj({"test", "--action", "dElEtE", "--project", "SCREE"});
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
        REQUIRE(outputError == "Error: invalid project argument(s) - project not found.");

        std::ifstream f(filePath);
        std::stringstream bufferFile;
        bufferFile << f.rdbuf();
        REQUIRE(bufferFile.str() == defaultDbContent);
        f.close();
    }
    WHEN("Delete invalid task")
    {
        // also testing for case insensitivity
        Argv argvObj({"test", "--action", "dElEtE", "--project", "CSC371", "--task", "SCREE"});
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
        REQUIRE(outputError == "Error: invalid task argument(s) - task not found.");

        std::ifstream f(filePath);
        std::stringstream bufferFile;
        bufferFile << f.rdbuf();
        REQUIRE(bufferFile.str() == defaultDbContent);
        f.close();
    }
    WHEN("Delete invalid tag")
    {
        // also testing for case insensitivity
        Argv argvObj({"test", "--action", "dElEtE", "--project", "CSC371", "--task", "Lab Assignment 1", "--tag", "SCREE"});
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
        REQUIRE(outputError == "Error: invalid tag argument(s), invalid: SCREE.");

        std::ifstream f(filePath);
        std::stringstream bufferFile;
        bufferFile << f.rdbuf();
        REQUIRE(bufferFile.str() == defaultDbContent);
        f.close();
    }
}

SCENARIO("Valid data")
{
    WHEN("Delete multiple valid tags")
    {
        // also testing for case insensitivity
        Argv argvObj({"test", "--action", "dElEtE", "--project", "CSC371", "--task", "Lab Assignment 1", "--tag", "uni,programming"});
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
        REQUIRE(outputError == "");

        std::ifstream f(filePath);
        std::stringstream bufferFile;
        bufferFile << f.rdbuf();
        REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSC371\":{\"Lab Assignment 1\":{\"completed\":true,\"dueDate\":\"2024-2-13\",\"tags\":[\"c\"]},\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]}}}");
        f.close();
    }
    WHEN("Delete valid task")
    {
        // also testing for case insensitivity
        Argv argvObj({"test", "--action", "dElEtE", "--project", "CSC371", "--task", "Lab Assignment 1"});
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
        REQUIRE(outputError == "");

        std::ifstream f(filePath);
        std::stringstream bufferFile;
        bufferFile << f.rdbuf();
        REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSC371\":{\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]}}}");
        f.close();

        GIVEN("Delete same task")
        {
            REQUIRE_NOTHROW(App::run(argc, argv));

            std::string output = buffer.str();
            REQUIRE(output == "");
            std::string outputError = bufferError.str();
            REQUIRE(outputError == "Error: invalid task argument(s) - task not found.");

            std::ifstream f(filePath);
            std::stringstream bufferFile;
            bufferFile << f.rdbuf();
            REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSC371\":{\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]}}}");
            f.close();
        }
    }
    WHEN("Delete valid project")
    {
        // also testing for case insensitivity
        Argv argvObj({"test", "--action", "dElEtE", "--project", "CSC371"});
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
        REQUIRE(outputError == "");

        std::ifstream f(filePath);
        std::stringstream bufferFile;
        bufferFile << f.rdbuf();
        REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}}}");
        f.close();
    }
}
