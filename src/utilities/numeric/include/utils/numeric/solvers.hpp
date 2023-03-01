/* ============================================================================================================================ *//**
 * @file       quadratic.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Tuesday, 1st February 2022 10:16:35 am
 * @modified   Wednesday, 1st March 2023 12:15:32 am
 * @project    cpp-utils
 * @brief      Definitions of tools related to solving polynomial equations
 *    
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __NUMERIC_SOLVERS_H__
#define __NUMERIC_SOLVERS_H__

/* =========================================================== Includes =========================================================== */

#include <utility>
#include <cmath>
#include <limits>

/* ========================================================== Namespaces ========================================================== */

namespace numeric::solvers {

/* ============================================================ Helpers =========================================================== */

/**
 * @brief Helper template comparing two values with the given precision
 * @tparam T ( optional, default: double )
 *    type of compared values
 * @tparam comp_precision ( optional, default: std::numeric_limits<T>::epsilon() )
 *    comparison's precision expressed in multiple of std::numeric_limits<T>::epsilon()
 * @param a 
 *    first value to be compared
 * @param b 
 *    second value to be compared
 * @returns 
 *    @c true fi values are equal, @c false otherwise
 */
template<typename T = double, unsigned comp_precision = 1>
constexpr bool is_equal(T a, T b);

/* ============================================================ Solvers =========================================================== */

/**
 * @brief Solves linear equation described by @p a and @p b coefficients in form of
 *   
 *                               ax + b = 0
 * 
 * @tparam T ( optional, default: double )
 *    type of the coefficients and result
 * @tparam comp_precision ( optional, default: std::numeric_limits<T>::epsilon() )
 *    comparison's precision expressed in multiple of std::numeric_limits<T>::epsilon()
 * @param a 
 *    a coefficient of the linear part of the equatuon
 * @param b 
 *    b coefficient of the constant part of the equatuon
 * @returns 
 *    soluton of the equation. In case when a = 0 and b ≠ 0 the equation has no solution
 *    and so the @ref std::numeric_limits<T>::quiet_NaN is returned
 */
template<typename T = double, unsigned comp_precision = 1>
constexpr T linear(T a, T b);

/**
 * @brief Solves quadratic equation described by @p a , @p b and @p c coefficients in form of
 *   
 *                               ax² + bx + c = 0
 * 
 * @tparam T ( optional, default: double )
 *    type of the coefficients and result
 * @tparam comp_precision ( optional, default: std::numeric_limits<T>::epsilon() )
 *    comparison's precision expressed in multiple of std::numeric_limits<T>::epsilon()
 * @param a 
 *    a coefficient of the quadratic part of the equatuon
 * @param b 
 *    b coefficient of the linear part of the equatuon
 * @param c 
 *    c coefficient of the constant part of the equatuon
 * @returns 
 *    pair of solutons of the equation. In cases when Δ ≤ 0 one or both of values are set to be
 *    @ref std::numeric_limits<T>::quiet_NaN
 * 
 * @note Smaller solution is returned as @a first
 */
template<typename T = double, unsigned comp_precision = 1>
constexpr std::pair<T, T> quadratic(T a, T b, T c);

/* ================================================================================================================================ */

} // End namespace numeric::solvers

/* ==================================================== Implementation includes =================================================== */

#include "utils/numeric/solvers/impl/solvers.hpp"

/* ================================================================================================================================ */

#endif
