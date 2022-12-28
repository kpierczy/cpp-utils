/* ============================================================================================================================ *//**
 * @file       assert.h
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Wednesday, 5th January 2022 12:43:18 pm
 * @modified   Wednesday, 28th December 2022 10:16:36 pm
 * @project    cpp-common
 * @brief      Implementation of the @macro sstl_assert definition
 *    
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __SSTL_ASSERT_H__
#define __SSTL_ASSERT_H__

/* =========================================================== Includes =========================================================== */

#ifdef SSTL_ASSERT_HEADER
#include SSTL_ASSERT_HEADER
#else
#include <cassert>
#endif

/* ============================================================ Macros ============================================================ */

#ifdef SSTL_ASSERT
#define sstl_assert(condition) SSTL_ASSERT(condition)
#else
#define sstl_assert(condition) assert(condition)
#endif

/* ================================================================================================================================ */


#endif
