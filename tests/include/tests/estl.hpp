/** ==================================================================================================================================
 * @file       estl.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Tuesday, 15th February 2022 11:44:39 pm
 * @modified   Sunday, 26th June 2022 11:45:05 am
 * @project    cpp-utils
 * @brief      
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 * ================================================================================================================================ */

#ifndef __TESTS_ESTL_H__
#define __TESTS_ESTL_H__

/* ========================================================= Configuration ======================================================== */

#if defined(__GNUC__) or defined(__GNUG__)
#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif

/* =========================================================== Includes =========================================================== */

#if GCC_VERSION >= 11'02'00
#include "tests/estl/namedtuple.hpp"
#endif

/* ================================================================================================================================ */

#endif

