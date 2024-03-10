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

SCENARIO("SET UP18")
{
    REQUIRE(fileExists(filePath));
    REQUIRE_NOTHROW(resetDbFile());
}

SCENARIO("Update names")
{
    WHEN("Update project and task name")
    {
        // also testing for case insensitivity
        Argv argvObj({"test", "--action", "uPdAtE", "--project", "CSC371:CSM371", "--task", "Lab Assignment 1:Lab Easy mode"});
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
        REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSM371\":{\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]},\"Lab Easy mode\":{\"completed\":true,\"dueDate\":\"2024-2-13\",\"tags\":[\"uni\",\"c\",\"programming\"]}}}");
        f.close();
    }
    WHEN("Update invalid project name")
    {
        // also testing for case insensitivity
        Argv argvObj({"test", "--action", "uPdAtE", "--project", "asdf:hahah"});
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
        REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSM371\":{\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]},\"Lab Easy mode\":{\"completed\":true,\"dueDate\":\"2024-2-13\",\"tags\":[\"uni\",\"c\",\"programming\"]}}}");
        f.close();
    }
    WHEN("Update invalid task name")
    {
        // also testing for case insensitivity
        Argv argvObj({"test", "--action", "uPdAtE", "--project", "CSM371", "--task", "ree:wew"});
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
        REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSM371\":{\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]},\"Lab Easy mode\":{\"completed\":true,\"dueDate\":\"2024-2-13\",\"tags\":[\"uni\",\"c\",\"programming\"]}}}");
        f.close();
    }
}

SCENARIO("Update due date")
{
    WHEN("Due date is empty")
    {
        // also testing for case insensitivity
        Argv argvObj({"test", "--action", "uPdAtE", "--project", "CSM371", "--task", "Lab Easy mode", "--due", ""});
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
        REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSM371\":{\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]},\"Lab Easy mode\":{\"completed\":true,\"dueDate\":\"\",\"tags\":[\"uni\",\"c\",\"programming\"]}}}");
        f.close();
    }
    WHEN("Due date is invalid")
    {
        // also testing for case insensitivity
        Argv argvObj({"test", "--action", "uPdAtE", "--project", "CSM371", "--task", "Lab Easy mode", "--due", "13-13-13"});
        auto **argv = argvObj.argv();
        auto argc = argvObj.argc();

        std::stringstream buffer;
        CoutRedirectv2 originalBuffer{buffer.rdbuf()};
        std::stringstream bufferError;
        CerrRedirect originalBufferError{bufferError.rdbuf()};

        REQUIRE_THROWS_AS(App::run(argc, argv), std::runtime_error);
        REQUIRE_THROWS_WITH(App::run(argc, argv), "Invalid date, got '13-13-13'");

        std::string output = buffer.str();
        REQUIRE(output == "");
        std::string outputError = bufferError.str();
        REQUIRE(outputError == "");

        std::ifstream f(filePath);
        std::stringstream bufferFile;
        bufferFile << f.rdbuf();
        REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSM371\":{\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]},\"Lab Easy mode\":{\"completed\":true,\"dueDate\":\"\",\"tags\":[\"uni\",\"c\",\"programming\"]}}}");
        f.close();
    }
    WHEN("Due date is valid")
    {
        // also testing for case insensitivity
        Argv argvObj({"test", "--action", "uPdAtE", "--project", "CSM371", "--task", "Lab Easy mode", "--due", "12-12-12"});
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
        REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSM371\":{\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]},\"Lab Easy mode\":{\"completed\":true,\"dueDate\":\"12-12-12\",\"tags\":[\"uni\",\"c\",\"programming\"]}}}");
        f.close();
    }
    WHEN("Incomplete")
    {
        // also testing for case insensitivity
        Argv argvObj({"test", "--action", "uPdAtE", "--project", "CSM371", "--task", "Lab Easy mode", "--incomplete"});
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
        REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSM371\":{\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]},\"Lab Easy mode\":{\"completed\":false,\"dueDate\":\"12-12-12\",\"tags\":[\"uni\",\"c\",\"programming\"]}}}");
        f.close();
    }
    WHEN("Completed")
    {
        // also testing for case insensitivity
        Argv argvObj({"test", "--action", "uPdAtE", "--project", "CSM371", "--task", "Lab Easy mode", "--completed"});
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
        REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSM371\":{\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]},\"Lab Easy mode\":{\"completed\":true,\"dueDate\":\"12-12-12\",\"tags\":[\"uni\",\"c\",\"programming\"]}}}");
        f.close();
    }
}
