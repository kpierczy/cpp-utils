/** ==================================================================================================================================
 * @file       foreach.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 30th December 2021 5:32:36 pm
 * @modified   Thursday, 3rd February 2022 11:38:04 am
 * @project    cpp-utils
 * @brief      Declaration of the foreach macro
 *    
 * @see https://www.scs.stanford.edu/~dm/blog/va-opt.pdf
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __ESTD_PREPROCESSOR_FOREACH_H__
#define __ESTD_PREPROCESSOR_FOREACH_H__

/* =========================================================== Includes =========================================================== */

#include "estd/preprocessor/va_opt_detect.hpp"
#include "estd/preprocessor/parens.hpp"
#include "estd/preprocessor/expand.hpp"
#include "estd/preprocessor/variadic.hpp"
#include "boost/preprocessor/if.hpp"
#include "boost/preprocessor/variadic/size.hpp"
#include "boost/preprocessor/comparison/greater_equal.hpp"
#include "boost/preprocessor/facilities/empty.hpp"
#include "boost/preprocessor/control/expr_if.hpp"

/* ========================================================= Requirements ========================================================= */

// Require __VA_OPT__ support
static_assert(VA_OPT_SUPPORTED);

/* =================================================== Declarations (foreach-n) =================================================== */

/**
 * @brief For-each-n macro aplying @p macro to each n-length tuples of arguments in the 
 *    passed arguments list
 * @param macro 
 *    macro to be applied
 * @param n 
 *    size of the tuple
 * 
 * @example
 *    
 *    FOR_EACH_N(F, 4, 1,2,3,4,5,6,7,8,9) -> F(1,2,3,4) F(5,6,7,8)
 * 
 * @note Macros uses EXPAND5 macro to allow 256-times reevaluation
 *   of recursed macros which should be enough for all daily usecases.
 *   If it's not, change expansion range
 */
#define FOR_EACH_N(macro, n, ...) \
    __VA_OPT__(EXPAND5(FOR_EACH_N_HELPER(DEFER(macro), n, __VA_ARGS__)))

/**
 * @brief Helper macro implementing For-each-n algorithm
 */
#define FOR_EACH_N_HELPER(macro, n, ...) \
    __VA_OPT__(DEFER(macro)(VARIADIC_FIRST_N_ELEMS(n, __VA_ARGS__))) \
    __VA_OPT__(FOR_EACH_N_AGAIN PARENS (DEFER(macro), n, VARIADIC_REMOVE_FIRST_N_ELEMS(n, __VA_ARGS__)))

/**
 * @brief Helper macro inserting FOR_EACH_N macro's name
 */
#define FOR_EACH_N_AGAIN() FOR_EACH_N_HELPER

/* ------------------------------------ Specialization of the for-each with n common arguments ------------------------------------ */

// One common argument
#define FOR_EACH_N_COM1(macro, n, com1, ...) \
    __VA_OPT__(EXPAND5(FOR_EACH_N_HELPER_COM1(DEFER(macro), n, com1, __VA_ARGS__)))
#define FOR_EACH_N_HELPER_COM1(macro, n, com1, ...) \
    __VA_OPT__(DEFER(macro)(com1, VARIADIC_FIRST_N_ELEMS(n, __VA_ARGS__))) \
    __VA_OPT__(FOR_EACH_N_AGAIN_COM1 PARENS (DEFER(macro), n, com1, VARIADIC_REMOVE_FIRST_N_ELEMS(n, __VA_ARGS__)))
#define FOR_EACH_N_AGAIN_COM1() FOR_EACH_N_HELPER_COM1

/* ================================================ Declarations (specializations) ================================================ */

/// Specialization of for-each-n for a single argument
#define FOR_EACH(macro, ...) FOR_EACH_N(macro, 1, __VA_ARGS__)
/// Specialization of for-each-n for pair of arguments
#define FOR_EACH_TUPLE2(macro, ...) FOR_EACH_N(macro, 2, __VA_ARGS__)
#define FOR_EACH_PAIR(macro, ...)   FOR_EACH_TUPLE2(macro, __VA_ARGS__)
/// Specialization of for-each-n for 3-length tuples of arguments
#define FOR_EACH_TUPLE3(macro, ...)  FOR_EACH_N(macro, 3, __VA_ARGS__)
#define FOR_EACH_TRIPLET(macro, ...) FOR_EACH_TUPLE3(macro, __VA_ARGS__)
/// Specialization of for-each-n for 4-length tuples of arguments
#define FOR_EACH_TUPLE4(macro, ...)     FOR_EACH_N(macro, 4, __VA_ARGS__)
#define FOR_EACH_QUADRUPLET(macro, ...) FOR_EACH_TUPLE4(macro, __VA_ARGS__)
// Higher-rank specializations
#define FOR_EACH_TUPLE5(macro, ...) FOR_EACH_N(macro, 5, __VA_ARGS__)
#define FOR_EACH_TUPLE6(macro, ...) FOR_EACH_N(macro, 6, __VA_ARGS__)
#define FOR_EACH_TUPLE7(macro, ...) FOR_EACH_N(macro, 7, __VA_ARGS__)
#define FOR_EACH_TUPLE8(macro, ...) FOR_EACH_N(macro, 8, __VA_ARGS__)
#define FOR_EACH_TUPLE9(macro, ...) FOR_EACH_N(macro, 9, __VA_ARGS__)

/* ============================================= Declarations (foreach-contiguous-n) ============================================== */

/**
 * @brief For-each-contiguous-n macro aplying @p macro to each n-length tuples of contiguous 
 *    arguments in the passed arguments list
 * @param macro 
 *    macro to be applied
 * @param n 
 *    size of the tuple
 * 
 * @example
 *    
 *    FOR_EACH_COTIGUOUS_N(F, 4, 1,2,3,4,5) -> F(1,2,3,4) F(2,3,4,5)
 * 
 * @note Macros uses EXPAND5 macro to allow 256-times reevaluation
 *   of recursed macros which should be enough for all daily usecases.
 *   If it's not, change expansion range
 */
#define FOR_EACH_COTIGUOUS_N(macro, n, ...) \
    __VA_OPT__(EXPAND5(FOR_EACH_COTIGUOUS_N_HELPER(DEFER(macro), n, __VA_ARGS__)))

/**
 * @brief Helper macro implementing For-each-contiguous-n algorithm
 */
#define FOR_EACH_COTIGUOUS_N_HELPER(macro, n, ...)                                                                                     \
    __VA_OPT__(                                                                                                                        \
        BOOST_PP_EXPR_IF(BOOST_PP_GREATER_EQUAL(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), n),                                               \
            DEFER(macro)(                                                                                                              \
                VARIADIC_FIRST_N_ELEMS(BOOST_PP_IF(BOOST_PP_GREATER_EQUAL(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), n), n, 1), __VA_ARGS__) \
            )                                                                                                                          \
        )                                                                                                                              \
    ) \
    __VA_OPT__(FOR_EACH_COTIGUOUS_N_AGAIN PARENS (DEFER(macro), n, VARIADIC_REMOVE_FIRST_N_ELEMS(1, __VA_ARGS__)))

/**
 * @brief Helper macro inserting FOR_EACH_COTIGUOUS_N macro's name
 */
#define FOR_EACH_COTIGUOUS_N_AGAIN() FOR_EACH_COTIGUOUS_N_HELPER

/* ================================================ Declarations (specializations) ================================================ */

/// Specialization of for-each-n for a single argument
#define FOR_EACH_COTIGUOUS(macro, ...) FOR_EACH_COTIGUOUS_N(macro, 1, __VA_ARGS__)
/// Specialization of for-each-n for pair of arguments
#define FOR_EACH_COTIGUOUS_TUPLE2(macro, ...) FOR_EACH_COTIGUOUS_N(macro, 2, __VA_ARGS__)
#define FOR_EACH_COTIGUOUS_PAIR(macro, ...)   FOR_EACH_COTIGUOUS_TUPLE2(macro, __VA_ARGS__)
/// Specialization of for-each-n for 3-length tuples of arguments
#define FOR_EACH_COTIGUOUS_TUPLE3(macro, ...)  FOR_EACH_COTIGUOUS_N(macro, 3, __VA_ARGS__)
#define FOR_EACH_COTIGUOUS_TRIPLET(macro, ...) FOR_EACH_COTIGUOUS_TUPLE3(macro, __VA_ARGS__)
/// Specialization of for-each-n for 4-length tuples of arguments
#define FOR_EACH_COTIGUOUS_TUPLE4(macro, ...)     FOR_EACH_COTIGUOUS_N(macro, 4, __VA_ARGS__)
#define FOR_EACH_COTIGUOUS_QUADRUPLET(macro, ...) FOR_EACH_COTIGUOUS_TUPLE4(macro, __VA_ARGS__)
// Higher-rank specializations
#define FOR_EACH_COTIGUOUS_TUPLE5(macro, ...) FOR_EACH_COTIGUOUS_N(macro, 5, __VA_ARGS__)
#define FOR_EACH_COTIGUOUS_TUPLE6(macro, ...) FOR_EACH_COTIGUOUS_N(macro, 6, __VA_ARGS__)
#define FOR_EACH_COTIGUOUS_TUPLE7(macro, ...) FOR_EACH_COTIGUOUS_N(macro, 7, __VA_ARGS__)
#define FOR_EACH_COTIGUOUS_TUPLE8(macro, ...) FOR_EACH_COTIGUOUS_N(macro, 8, __VA_ARGS__)
#define FOR_EACH_COTIGUOUS_TUPLE9(macro, ...) FOR_EACH_COTIGUOUS_N(macro, 9, __VA_ARGS__)

/* ================================================================================================================================ */

#endif
