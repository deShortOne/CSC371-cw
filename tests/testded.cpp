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

SCENARIO("Create new project named _project1")
{
    GIVEN("We create _project1")
    {
        // also testing for case insensitivity
        Argv argvObj({"test", "--action", "CREATE", "--project", "asdf", "--project", "ad"});
        auto **argv = argvObj.argv();
        auto argc = argvObj.argc();

        REQUIRE_NOTHROW(App::run(argc, argv));
    }
}
