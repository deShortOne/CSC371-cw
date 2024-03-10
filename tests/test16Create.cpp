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

SCENARIO("SET UP")
{
    REQUIRE(fileExists(filePath));
    REQUIRE_NOTHROW(resetDbFile());
}

SCENARIO("Create new project named _project1")
{
    GIVEN("We create _project1")
    {
        // also testing for case insensitivity
        Argv argvObj({"test", "--action", "CREATE", "--project", "_project1"});
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
        REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSC371\":{\"Lab Assignment 1\":{\"completed\":true,\"dueDate\":\"2024-2-13\",\"tags\":[\"uni\",\"c\",\"programming\"]},\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]}},\"_project1\":{}}");
        f.close();

        WHEN("We attempt to create it again")
        {
            REQUIRE_NOTHROW(App::run(argc, argv));

            THEN("No ouput nor should it be added to file")
            {
                std::string output = buffer.str();
                REQUIRE(output == "");
                std::string outputError = bufferError.str();
                REQUIRE(outputError == "");

                std::ifstream f(filePath);
                std::stringstream bufferFile;
                bufferFile << f.rdbuf();
                REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSC371\":{\"Lab Assignment 1\":{\"completed\":true,\"dueDate\":\"2024-2-13\",\"tags\":[\"uni\",\"c\",\"programming\"]},\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]}},\"_project1\":{}}");
                f.close();
            }
        }
    }
    GIVEN("We created _project1")
    {
        THEN("Create a task inside of it")
        {
            // also testing for case insensitivity
            Argv argvObj({"test", "--action", "CREATE", "--project", "_project1", "--task", "write unit tests"});
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
            REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSC371\":{\"Lab Assignment 1\":{\"completed\":true,\"dueDate\":\"2024-2-13\",\"tags\":[\"uni\",\"c\",\"programming\"]},\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]}},\"_project1\":{\"write unit tests\":{\"completed\":false,\"dueDate\":\"\",\"tags\":[]}}}");
            f.close();

            THEN("Attempt to recreate the same task with no changes")
            {
                REQUIRE_NOTHROW(App::run(argc, argv));
                std::string output = buffer.str();
                REQUIRE(output == "");
                std::string outputError = bufferError.str();
                REQUIRE(outputError == "");

                std::ifstream f(filePath);
                std::stringstream bufferFile;
                bufferFile << f.rdbuf();
                REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSC371\":{\"Lab Assignment 1\":{\"completed\":true,\"dueDate\":\"2024-2-13\",\"tags\":[\"uni\",\"c\",\"programming\"]},\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]}},\"_project1\":{\"write unit tests\":{\"completed\":false,\"dueDate\":\"\",\"tags\":[]}}}");
                f.close();
            }
        }
    }
    GIVEN("We created _project1 with task write unit tests")
    {
        THEN("Add some tags to it")
        {
            // also testing for case insensitivity
            Argv argvObj({"test", "--action", "CREATE", "--project", "_project1", "--task", "write unit tests", "--tag", "a,b,c,d,  e,f  "});
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
            REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSC371\":{\"Lab Assignment 1\":{\"completed\":true,\"dueDate\":\"2024-2-13\",\"tags\":[\"uni\",\"c\",\"programming\"]},\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]}},\"_project1\":{\"write unit tests\":{\"completed\":false,\"dueDate\":\"\",\"tags\":[\"a\",\"b\",\"c\",\"d\",\"  e\",\"f  \"]}}}");
            f.close();

            THEN("Add same tags to no effect")
            {
                REQUIRE_NOTHROW(App::run(argc, argv));

                std::string output = buffer.str();
                REQUIRE(output == "");
                std::string outputError = bufferError.str();
                REQUIRE(outputError == "");

                std::ifstream f(filePath);
                std::stringstream bufferFile;
                bufferFile << f.rdbuf();
                REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSC371\":{\"Lab Assignment 1\":{\"completed\":true,\"dueDate\":\"2024-2-13\",\"tags\":[\"uni\",\"c\",\"programming\"]},\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]}},\"_project1\":{\"write unit tests\":{\"completed\":false,\"dueDate\":\"\",\"tags\":[\"a\",\"b\",\"c\",\"d\",\"  e\",\"f  \"]}}}");
                f.close();
            }
        }
    }
    GIVEN("We created _project1 with task write unit tests")
    {
        THEN("Add a valid date")
        {
            // also testing for case insensitivity
            Argv argvObj({"test", "--action", "CREATE", "--project", "_project1", "--task", "write unit tests", "--due", "2024-03-10"});
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
            REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSC371\":{\"Lab Assignment 1\":{\"completed\":true,\"dueDate\":\"2024-2-13\",\"tags\":[\"uni\",\"c\",\"programming\"]},\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]}},\"_project1\":{\"write unit tests\":{\"completed\":false,\"dueDate\":\"2024-3-10\",\"tags\":[\"a\",\"b\",\"c\",\"d\",\"  e\",\"f  \"]}}}");
            f.close();

            THEN("Update the date to another date")
            {
                Argv argvObj2({"test", "--action", "CREATE", "--project", "_project1", "--task", "write unit tests", "--due", "2024-07-6"});
                auto **argv2 = argvObj2.argv();
                auto argc2 = argvObj2.argc();

                REQUIRE_NOTHROW(App::run(argc2, argv2));

                std::string output = buffer.str();
                REQUIRE(output == "");
                std::string outputError = bufferError.str();
                REQUIRE(outputError == "");

                std::ifstream f(filePath);
                std::stringstream bufferFile;
                bufferFile << f.rdbuf();
                REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSC371\":{\"Lab Assignment 1\":{\"completed\":true,\"dueDate\":\"2024-2-13\",\"tags\":[\"uni\",\"c\",\"programming\"]},\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]}},\"_project1\":{\"write unit tests\":{\"completed\":false,\"dueDate\":\"2024-7-6\",\"tags\":[\"a\",\"b\",\"c\",\"d\",\"  e\",\"f  \"]}}}");
                f.close();
            }
            THEN("Update date to empty")
            {
                Argv argvObj2({"test", "--action", "CREATE", "--project", "_project1", "--task", "write unit tests", "--due", ""});
                auto **argv2 = argvObj2.argv();
                auto argc2 = argvObj2.argc();

                REQUIRE_NOTHROW(App::run(argc2, argv2));

                std::string output = buffer.str();
                REQUIRE(output == "");
                std::string outputError = bufferError.str();
                REQUIRE(outputError == "");

                std::ifstream f(filePath);
                std::stringstream bufferFile;
                bufferFile << f.rdbuf();
                REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSC371\":{\"Lab Assignment 1\":{\"completed\":true,\"dueDate\":\"2024-2-13\",\"tags\":[\"uni\",\"c\",\"programming\"]},\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]}},\"_project1\":{\"write unit tests\":{\"completed\":false,\"dueDate\":\"\",\"tags\":[\"a\",\"b\",\"c\",\"d\",\"  e\",\"f  \"]}}}");
                f.close();
            }
            THEN("Set to completed")
            {
                Argv argvObj2({"test", "--action", "CREATE", "--project", "_project1", "--task", "write unit tests", "--due", "", "--completed"});
                auto **argv2 = argvObj2.argv();
                auto argc2 = argvObj2.argc();

                REQUIRE_NOTHROW(App::run(argc2, argv2));

                std::string output = buffer.str();
                REQUIRE(output == "");
                std::string outputError = bufferError.str();
                REQUIRE(outputError == "");

                std::ifstream f(filePath);
                std::stringstream bufferFile;
                bufferFile << f.rdbuf();
                REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSC371\":{\"Lab Assignment 1\":{\"completed\":true,\"dueDate\":\"2024-2-13\",\"tags\":[\"uni\",\"c\",\"programming\"]},\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]}},\"_project1\":{\"write unit tests\":{\"completed\":true,\"dueDate\":\"\",\"tags\":[\"a\",\"b\",\"c\",\"d\",\"  e\",\"f  \"]}}}");
                f.close();
            }
            THEN("Set to incomplete")
            {
                Argv argvObj2({"test", "--action", "CREATE", "--project", "_project1", "--task", "write unit tests", "--due", "", "--incomplete"});
                auto **argv2 = argvObj2.argv();
                auto argc2 = argvObj2.argc();

                REQUIRE_NOTHROW(App::run(argc2, argv2));

                std::string output = buffer.str();
                REQUIRE(output == "");
                std::string outputError = bufferError.str();
                REQUIRE(outputError == "");

                std::ifstream f(filePath);
                std::stringstream bufferFile;
                bufferFile << f.rdbuf();
                REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSC371\":{\"Lab Assignment 1\":{\"completed\":true,\"dueDate\":\"2024-2-13\",\"tags\":[\"uni\",\"c\",\"programming\"]},\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]}},\"_project1\":{\"write unit tests\":{\"completed\":false,\"dueDate\":\"\",\"tags\":[\"a\",\"b\",\"c\",\"d\",\"  e\",\"f  \"]}}}");
                f.close();
            }
        }
    }
}

SCENARIO("Create all information from scratch")
{
    // also testing for case insensitivity
    Argv argvObj({"test", "--action", "CREATE", "--project", "_project2", "--task", "kekeke", "--tag", "p,q,r,s,t,u", "--due", "2024-03-21", "--completed"});
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
    REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSC371\":{\"Lab Assignment 1\":{\"completed\":true,\"dueDate\":\"2024-2-13\",\"tags\":[\"uni\",\"c\",\"programming\"]},\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]}},\"_project1\":{\"write unit tests\":{\"completed\":false,\"dueDate\":\"\",\"tags\":[\"a\",\"b\",\"c\",\"d\",\"  e\",\"f  \"]}},\"_project2\":{\"kekeke\":{\"completed\":true,\"dueDate\":\"2024-3-21\",\"tags\":[\"p\",\"q\",\"r\",\"s\",\"t\",\"u\"]}}}");
    f.close();
}
