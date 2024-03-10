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

SCENARIO("SET UP15")
{
    REQUIRE(fileExists(filePath));
    REQUIRE_NOTHROW(resetDbFile());
}

SCENARIO("./371todo ‑‑action 123")
{
    Argv argvObj({"test", "--action", "123"});
    auto **argv = argvObj.argv();
    auto argc = argvObj.argc();

    REQUIRE_THROWS_AS(App::run(argc, argv), std::invalid_argument);
    REQUIRE_THROWS_WITH(App::run(argc, argv), "action");
}

SCENARIO("1) ./371todo ‑‑action json")
{
    Argv argvObj({"test", "--action", "json"});
    auto **argv = argvObj.argv();
    auto argc = argvObj.argc();

    std::stringstream buffer;
    CoutRedirectv2 originalBuffer{buffer.rdbuf()};
    std::stringstream bufferError;
    CerrRedirect originalBufferError{bufferError.rdbuf()};

    REQUIRE_NOTHROW(App::run(argc, argv));

    std::string output = buffer.str();
    REQUIRE(output ==
            "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSC371\":{\"Lab Assignment 1\":{\"completed\":true,\"dueDate\":\"2024-2-13\",\"tags\":[\"uni\",\"c\",\"programming\"]},\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]}}}");
    std::string outputError = bufferError.str();
    REQUIRE(outputError == "");
}

SCENARIO("2) ./371todo-output --action json --project \"CSC371\"")
{
    Argv argvObj({"test", "--action", "json", "--project", "CSC371"});
    auto **argv = argvObj.argv();
    auto argc = argvObj.argc();

    std::stringstream buffer;
    CoutRedirectv2 originalBuffer{buffer.rdbuf()};
    std::stringstream bufferError;
    CerrRedirect originalBufferError{bufferError.rdbuf()};

    REQUIRE_NOTHROW(App::run(argc, argv));

    std::string output = buffer.str();
    REQUIRE(output ==
            "{\"Lab Assignment 1\":{\"completed\":true,\"dueDate\":\"2024-2-13\",\"tags\":[\"uni\",\"c\",\"programming\"]},\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]}}");
    std::string outputError = bufferError.str();
    REQUIRE(outputError == "");
}

SCENARIO("3) ./371todo-output --action json --project \"CSC371\" --task \"Lab Assignment 1\"")
{
    Argv argvObj({"test", "--action", "json", "--project", "CSC371", "--task", "Lab Assignment 1"});
    auto **argv = argvObj.argv();
    auto argc = argvObj.argc();

    std::stringstream buffer;
    CoutRedirectv2 originalBuffer{buffer.rdbuf()};
    std::stringstream bufferError;
    CerrRedirect originalBufferError{bufferError.rdbuf()};

    REQUIRE_NOTHROW(App::run(argc, argv));

    std::string output = buffer.str();
    REQUIRE(output ==
            "{\"completed\":true,\"dueDate\":\"2024-2-13\",\"tags\":[\"uni\",\"c\",\"programming\"]}");
    std::string outputError = bufferError.str();
    REQUIRE(outputError == "");
}

SCENARIO("4) ./371todo-output --action json --project \"CSC371\" --task \"Lab Assignment 1\" --tag \"programming\"")
{
    Argv argvObj({"test", "--action", "json", "--project", "CSC371", "--task", "Lab Assignment 1", "--tag", "programming"});
    auto **argv = argvObj.argv();
    auto argc = argvObj.argc();

    std::stringstream buffer;
    CoutRedirectv2 originalBuffer{buffer.rdbuf()};
    std::stringstream bufferError;
    CerrRedirect originalBufferError{bufferError.rdbuf()};

    REQUIRE_NOTHROW(App::run(argc, argv));

    std::string output = buffer.str();
    REQUIRE(output == "programming");
    std::string outputError = bufferError.str();
    REQUIRE(outputError == "");
}

SCENARIO("5) ./371todo-output --action json --project \"CSC371\" --task \"Lab Assignment 2\" --tag \"programming\"")
{
    Argv argvObj({"test", "--action", "json", "--project", "CSC371", "--task", "Lab Assignment 2", "--tag", "programming"});
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

SCENARIO("6) ./371todo-output --action json --project \"CSC173\" --task \"Lab Assignment 2\"")
{
    Argv argvObj({"test", "--action", "json", "--project", "CSC173", "--task", "Lab Assignment 2"});
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

SCENARIO("7) ./371todo-output --action json --task \"Lab Assignment 2\"")
{
    Argv argvObj({"test", "--action", "json", "--task", "Lab Assignment 2"});
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
    REQUIRE(outputError == "Error: missing project argument(s).");
}

SCENARIO("8) ./371todo-output --action create")
{
    Argv argvObj({"test", "--action", "create"});
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
    REQUIRE(outputError == "Error: missing project, task, tag, due, completed/incomplete argument(s).");
}

SCENARIO("9) ./371todo-output --action create --project \"CSC371\" --task \"Lab Assignment 2\" --tag \"programming,c,uni\"")
{
    Argv argvObj({"test", "--action", "create", "--project", "CSC371", "--task", "Lab Assignment 2", "--tag", "programming,c,uni"});
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
    REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSC371\":{\"Lab Assignment 1\":{\"completed\":true,\"dueDate\":\"2024-2-13\",\"tags\":[\"uni\",\"c\",\"programming\"]},\"Lab Assignment 2\":{\"completed\":false,\"dueDate\":\"\",\"tags\":[\"programming\",\"c\",\"uni\"]},\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]}}}");
    f.close();
}

SCENARIO("10: ./371todo-output --action update --project \"CSC371\" --task \"Lab Assignment 2\" --due \"2024-02-20\" --incomplete")
{
    Argv argvObj({"test", "--action", "update", "--project", "CSC371", "--task", "Lab Assignment 2", "--due", "2024-02-20", "--incomplete"});
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
    REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSC371\":{\"Lab Assignment 1\":{\"completed\":true,\"dueDate\":\"2024-2-13\",\"tags\":[\"uni\",\"c\",\"programming\"]},\"Lab Assignment 2\":{\"completed\":false,\"dueDate\":\"2024-2-20\",\"tags\":[\"programming\",\"c\",\"uni\"]},\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]}}}");
    f.close();
}

SCENARIO("11) ./371todo-output --action update --project \"CSC371\" --task \"Lab Assignment 2\" --completed")
{
    Argv argvObj({"test", "--action", "update", "--project", "CSC371", "--task", "Lab Assignment 2", "--completed"});
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
    REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSC371\":{\"Lab Assignment 1\":{\"completed\":true,\"dueDate\":\"2024-2-13\",\"tags\":[\"uni\",\"c\",\"programming\"]},\"Lab Assignment 2\":{\"completed\":true,\"dueDate\":\"2024-2-20\",\"tags\":[\"programming\",\"c\",\"uni\"]},\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]}}}");
    f.close();
}

SCENARIO("12: ./371todo-output --action delete --project \"CSC371\" --task \"Lab Assignment 2\" --tag \"uni\"")
{
    Argv argvObj({"test", "--action", "delete", "--project", "CSC371", "--task", "Lab Assignment 2", "--tag", "uni"});
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
    REQUIRE(bufferFile.str() == "{\"CSC307\":{\"Write Mobile App\":{\"completed\":true,\"dueDate\":\"2023-11-30\",\"tags\":[\"uni\",\"programming\",\"android\"]}},\"CSC371\":{\"Lab Assignment 1\":{\"completed\":true,\"dueDate\":\"2024-2-13\",\"tags\":[\"uni\",\"c\",\"programming\"]},\"Lab Assignment 2\":{\"completed\":true,\"dueDate\":\"2024-2-20\",\"tags\":[\"programming\",\"c\"]},\"Lab Assignment 6\":{\"completed\":false,\"dueDate\":\"2024-4-23\",\"tags\":[\"uni\",\"c++\",\"programming\",\"standard library\"]}}}");
    f.close();
}

SCENARIO("13: ./371todo-output --action delete --project \"CSC371\"")
{
    Argv argvObj({"test", "--action", "delete", "--project", "CSC371"});
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
