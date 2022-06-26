/* ============================================================================================================================ *//**
 * @file       expand.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 30th December 2021 5:32:36 pm
 * @modified   Sunday, 26th June 2022 11:56:58 am
 * @project    cpp-utils
 * @brief      Declaration of the expand macros
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_PREPROCESSOR_EXPAND_H__
#define __ESTD_PREPROCESSOR_EXPAND_H__

/* ========================================================= Declarations ========================================================= */

/**
 * @brief EXPANDx macros are used to trigger n-time rescan of the passed arguments
 *    enabling recursive macros expansion. E.g. when calling EXPAND5(...), passed
 *    arguments (i.e. EXPAND1 macro) are expanded 256 times. Number of evaluations
 *    grows exponentially with the x with exponence factor @c 4 (equal to number
 *    of calls to the lowe-range macro in each macro)
 * 
 * @see https://www.scs.stanford.edu/~dm/blog/va-opt.pdf
 */

#define EXPAND9(...) EXPAND8(EXPAND8(EXPAND8(EXPAND8(__VA_ARGS__))))
#define EXPAND8(...) EXPAND7(EXPAND7(EXPAND7(EXPAND7(__VA_ARGS__))))
#define EXPAND7(...) EXPAND6(EXPAND6(EXPAND6(EXPAND6(__VA_ARGS__))))
#define EXPAND6(...) EXPAND5(EXPAND5(EXPAND5(EXPAND5(__VA_ARGS__))))
#define EXPAND5(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__
#define  EXPAND(...) __VA_ARGS__

/**
 * @brief Helper macro used to defer expansion of the macro in nested
 *    macros
 */
#define EMPTY()
#define DEFER(macro) macro EMPTY()

/* ================================================================================================================================ */

#endif
