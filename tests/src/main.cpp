/* ============================================================================================================================ *//**
 * @file       main.cpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 3rd February 2022 7:26:04 pm
 * @modified   Thursday, 29th December 2022 5:52:32 am
 * @project    cpp-utils
 * @brief      Main source file of host-based tests
 *    
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

/* =========================================================== Includes =========================================================== */

#include "tests/main.hpp"
#include "tests/estl.hpp"

/* ====================================================== Injected namespaces ===================================================== */

using namespace boost::ut::literals;
using namespace boost::ut::operators::terse;

/* ============================================================= Tests ============================================================ */

int main()
{
    "tests"_test = [] { };
}


/* ================================================================================================================================ */
