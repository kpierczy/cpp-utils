/** ==================================================================================================================================
 * @file     helpers.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Saturday, 4th December 2021 6:58:00 pm
 * @modified Thursday, 3rd February 2022 11:42:00 am
 * @project  Winder
 * @brief
 *    
 *    Implementation of inline functions from the helper module
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __UNITS_HELPERS_IMPL_HELPERS_H__
#define __UNITS_HELPERS_IMPL_HELPERS_H__

/* =========================================================== Includes =========================================================== */

#include <type_traits>
#include "units/math.h"
#include "units/helpers.hpp"

/* =========================================================== Namespace ========================================================== */

namespace units {

/* ========================================================== Definitions ========================================================= */

template<units::Quantity Left, units::QuantityEquivalentTo<Left> Right, units::QuantityEquivalentTo<Left> Tol>
inline constexpr bool is_equal(Left left, Right right, Tol tol) {
    return (left - right < tol) && (left - right > -tol);
}


template<units::Quantity Left, units::QuantityEquivalentTo<Left> Right>
inline constexpr bool is_equal(Left left, Right right, unsigned tol) {

    // Get representation type of both quantities
    using lrep = typename Left::rep;
    using rrep = typename Right::rep;
    // Check if types are floating points
    constexpr bool is_l_floating = std::is_floating_point_v<lrep>;
    constexpr bool is_r_floating = std::is_floating_point_v<rrep>;
    // Get size of both types
    constexpr unsigned lsize = sizeof(lrep);
    constexpr unsigned rsize = sizeof(rrep);

    // Pick a type that is wider
    using WiderType = std::conditional_t<is_l_floating || is_r_floating,
        // If any of types is floating...
        std::conditional_t<is_l_floating && is_r_floating,
            // If both types are floating, pick wider
            std::conditional_t<(lsize > rsize), Left, Right>,
            // Else, pick the floating one
            std::conditional_t<is_l_floating, Left, Right>>,
        // If both types are integers, pick wider
        std::conditional_t<(lsize > rsize), Left, Right>
    >;

    // Get requested tolerance
    auto tolerance = units::epsilon<WiderType>() * tol;

    // Compare both quantities with respect to the multiple of epsilon of the wider representation
    return (left - right < tolerance) && (left - right > -tolerance);
}


template<Range range_type, Quantity Left, units::QuantityEquivalentTo<Left> Right>
constexpr range<range_type, Left, Right>::range(Left left, Right right) :
    left(left), right(right)
{ }


template<Range range_type, Quantity Left, units::QuantityEquivalentTo<Left> Right>
template<units::QuantityEquivalentTo<Left> Value>
constexpr bool range<range_type, Left, Right>::operator()(Value value) const {
    if constexpr (range_type == Range::Inclusive)
        return ((value >= left) and (value <= right));
    else
        return ((value > left) and (value < right));
}


template<Range range_type = Range::Inclusive>
constexpr auto in_range(auto left, auto right) -> range<range_type, decltype(left), decltype(right)> {
    return range<range_type, decltype(left), decltype(right)>{left, right};
}

/* ================================================================================================================================ */

} // End namespace units

#endif
