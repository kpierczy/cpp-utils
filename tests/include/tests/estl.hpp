/* ============================================================================================================================ *//**
 * @file       estl.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Tuesday, 15th February 2022 11:44:39 pm
 * @modified   Tuesday, 28th February 2023 8:49:04 pm
 * @project    cpp-utils
 * @brief      
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __TESTS_ESTL_H__
#define __TESTS_ESTL_H__

/* =========================================================== Includes =========================================================== */

// Compilation test for 'circular_buffer'
#include "estl/circular_buffer.hpp"

// Functional test for 'namedtuple'
#include "tests/estl/namedtuple.hpp"

/* ========================================================== Definitions ========================================================= */

inline void estl_tests()
{
    namedtuple_test();
}

/* ================================================================================================================================ */

#endif

