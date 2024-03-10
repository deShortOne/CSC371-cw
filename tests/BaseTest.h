#ifndef BASE_TEST_H
#define BASE_TEST_H

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
class CoutRedirectv2 // v2 because it's also used in test 8
{
private:
    std::streambuf *old;

public:
    CoutRedirectv2(std::streambuf *new_buffer)
        : old(std::cout.rdbuf(new_buffer))
    { /* do nothing */
    }

    ~CoutRedirectv2() { std::cout.rdbuf(old); }
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

void resetDbFile()
{
    writeFileContents(
        filePath,
        "{ \"CSC371\": { \"Lab Assignment 1\": { \"completed\": true, "
        "\"dueDate\": \"2024-02-13\", \"tags\": [ \"uni\", \"c\", "
        "\"programming\" ] }, \"Lab Assignment 6\": { \"completed\": false, "
        "\"dueDate\": \"2024-04-23\", \"tags\": [ \"uni\", \"c++\", "
        "\"programming\", \"standard library\" ] } }, \"CSC307\": { \"Write "
        "Mobile App\": { \"completed\": true, \"dueDate\": \"2023-11-30\", "
        "\"tags\": [ \"uni\", \"programming\", \"android\" ] } } }");
}

#endif
