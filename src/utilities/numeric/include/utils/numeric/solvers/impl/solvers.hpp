/** ==================================================================================================================================
 * @file       solvers.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Tuesday, 1st February 2022 10:16:35 am
 * @modified   Thursday, 3rd February 2022 12:04:37 pm
 * @project    cpp-utils
 * @brief      Implementation of tools related to solving polynomial equations
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * ================================================================================================================================ */

#ifndef __NUMERIC_SOVLERS_IMPL_SOVLERS_H__
#define __NUMERIC_SOVLERS_IMPL_SOVLERS_H__

/* =========================================================== Includes =========================================================== */

#include "numeric/solvers.hpp"

/* ========================================================== Namespaces ========================================================== */

namespace numeric::solvers {

/* ============================================================ Aliases =========================================================== */

/// 'zero' constant
template <typename T> constexpr T zero = T{0};
/// 'one' constant
template <typename T> constexpr T one = T{1};
/// NaN constant
template <typename T> constexpr T NaN = std::numeric_limits<T>::quiet_NaN();
/// 'epsilon' constant
template <typename T> constexpr T epsilon = std::numeric_limits<T>::epsilon();

/* ============================================================ Helpers =========================================================== */

template<typename T, unsigned comp_precision>
constexpr bool is_equal(T a, T b) {
    return (std::abs(a - b) <= (epsilon<T> * comp_precision));
}

/* ============================================================ Solvers =========================================================== */

template<typename T, unsigned comp_precision>
constexpr T linear(T a, T b) {

    // Comparison function
    constexpr auto equal = [](T x, T y) { return is_equal<T, comp_precision>(x, y); };

    // If (a = 0), the equaition has no single root
    if(equal(a, zero<T>)) {
        
        return NaN<T>;

    // Otherwise, the equation MAY have representable solution
    } else {

        // Calculate solution
        T x = (-b/a);

        // Check if solution overflows
        return (std::isfinite(x)) ? x : NaN<T>;
    }
}


template<typename T, unsigned comp_precision>
constexpr std::pair<T, T> quadratic(T a, T b, T c) {

    /**
     * @note solution is based on @see https://stackoverflow.com/questions/898076/solve-quadratic-equation-in-c#answer-900119
     *    and @see https://math.stackexchange.com/questions/866331/numerically-stable-algorithm-for-solving-the-quadratic-equation-when-a-is-very#answer-2007723
     */

    // Comparison function
    constexpr auto equal = [](T x, T y) { return is_equal<T, comp_precision>(x, y); };

    /* ---------------------------- Linear case ---------------------------- */

    // If (a = 0), the equation is linear
    if(equal(a, zero<T>))
        return std::pair{ linear(b, c), NaN<T> };

    // Scale equation to (a = 1)
    c = c / a;
    b = b / a;
    a = one<T>;
    
    /* ------------------------- Non-constant case ------------------------- */

    // If (c = 0), the equation can be simplified to ax² + bx = x(ax + b) = 0 
    if(equal(c, zero<T>))
        return std::pair{ zero<T>, linear(a, b) };

    /* -------------------------- Quadratic case --------------------------- */

    // Calculate amximum value of the square root
    constexpr T max_sqrt = std::sqrt(std::numeric_limits<double>::max());

    /**
     * @brief If @p b is higher than the max_sqrt, the @p b*b will overflow. In this case we
     *    can approximate the equation as x² + (b/a)x = x(x + b/a) = 0 to solve for x₁ = -b/a, 
     *    and use x₂ = (c/a) / x₁ = (c/a) / (-b/a) to find the second one. This should work even 
     *    with large constant values
     * @note At this point coefficients @p b and @p c are already scaled to @p b/a and @p c/a 
     *    respectively
     */
    if ((b > max_sqrt) or (b < -max_sqrt))
        return std::pair{ -b, linear(b, c) };

    // Calculate delta
    T delta = b * b - 4 * c;

    // Check if equation has no solutions
    if(delta < zero<T>)
        return std::pair{ NaN<T>, NaN<T> };
    // Check if equation has one double solution, then x = -(b/a) / 2
    if(equal(delta, zero<T>)) {

        // Calculate solution
        T x = -b / T{2};

        // Return solution
        return std::pair{ x, x };
    }

    // Calculate both roots
    T x_1 = -(b + std::copysign(std::sqrt(delta), b)) * 0.5;;
    T x_2 = c / x_1;
    
    // Return result
    return std::pair{ x_1, x_2 };
}

/* ================================================================================================================================ */

} // End namespace numeric::solvers

#endif
