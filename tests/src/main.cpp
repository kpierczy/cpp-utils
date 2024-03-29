/* ============================================================================================================================ *//**
 * @file       main.cpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 3rd February 2022 7:26:04 pm
 * @modified   Tuesday, 28th February 2023 8:53:27 pm
 * @project    cpp-utils
 * @brief      Main source file of host-based tests
 *    
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

/* =========================================================== Includes =========================================================== */

#include "tests/estl.hpp"
#include "tests/estd.hpp"
#include "tests/lib-extensions.hpp"
#include "tests/utilities.hpp"

/* ============================================================= Tests ============================================================ */

int main()
{
    estl_tests();
    estd_tests();
    lib_extensions_tests();
    utilities_tests();
}

/* ================================================================================================================================ */
