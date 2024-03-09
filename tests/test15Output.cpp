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

// Redirect std::cout to a buffer
// by Björn Pollex
// via https://stackoverflow.com/a/5419388
// licensed under CC BY-SA 3.0.
class CoutRedirect
{
private:
    std::streambuf *old;

public:
    CoutRedirect(std::streambuf *new_buffer)
        : old(std::cout.rdbuf(new_buffer))
    { /* do nothing */
    }

    ~CoutRedirect() { std::cout.rdbuf(old); }
};

class CerrRedirect
{
private:
    std::streambuf *old;

public:
    CerrRedirect(std::streambuf *new_buffer)
        : old(std::cerr.rdbuf(new_buffer))
    { /* do nothing */
    }

    ~CerrRedirect() { std::cerr.rdbuf(old); }
};

const std::string filePath = "./database.json";

auto fileExists = [](const std::string &path)
{
    return std::ifstream(path).is_open();
};

auto writeFileContents = [](const std::string &path,
                            const std::string &contents)
{
    // Not a robust way to do this, but here it doesn't matter so much, if it
    // goes wrong we'll fail the test anyway…
    std::ofstream f{path};
    f << contents;
};

SCENARIO("SET UP")
{
    REQUIRE(fileExists(filePath));
    REQUIRE_NOTHROW(writeFileContents(
        filePath,
        "{ \"CSC371\": { \"Lab Assignment 1\": { \"completed\": true, "
        "\"dueDate\": \"2024-02-13\", \"tags\": [ \"uni\", \"c\", "
        "\"programming\" ] }, \"Lab Assignment 6\": { \"completed\": false, "
        "\"dueDate\": \"2024-04-23\", \"tags\": [ \"uni\", \"c++\", "
        "\"programming\", \"standard library\" ] } }, \"CSC307\": { \"Write "
        "Mobile App\": { \"completed\": true, \"dueDate\": \"2023-11-30\", "
        "\"tags\": [ \"uni\", \"programming\", \"android\" ] } } }"));
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
    CoutRedirect originalBuffer{buffer.rdbuf()};
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
    CoutRedirect originalBuffer{buffer.rdbuf()};
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
    CoutRedirect originalBuffer{buffer.rdbuf()};
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
    CoutRedirect originalBuffer{buffer.rdbuf()};
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
    CoutRedirect originalBuffer{buffer.rdbuf()};
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
    CoutRedirect originalBuffer{buffer.rdbuf()};
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
    CoutRedirect originalBuffer{buffer.rdbuf()};
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
    CoutRedirect originalBuffer{buffer.rdbuf()};
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
    CoutRedirect originalBuffer{buffer.rdbuf()};
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
