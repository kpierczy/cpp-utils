/** ==================================================================================================================================
 * @file     sstl_assert.h
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Wednesday, 5th January 2022 12:43:18 pm
 * @modified Sunday, 9th January 2022 6:40:40 pm
 * @project  Winder
 * @brief
 *    
 *    Implementation of the @macro sstl_assert definition
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * ================================================================================================================================ */

#ifndef __SSTL_ASSERT_H__
#define __SSTL_ASSERT_H__

/* =========================================================== Includes =========================================================== */

#ifdef MBED_TARGET
#include "mbed.h"
#else
#include <cassert>
#endif

/* ============================================================ Macros ============================================================ */

#ifdef MBED_ASSERT
#define sstl_assert MBED_ASSERT
#else
#define sstl_assert assert
#endif

/* ================================================================================================================================ */


#endif
