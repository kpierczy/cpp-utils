/** ==================================================================================================================================
 * @file     string.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Friday, 28th January 2022 1:48:57 pm
 * @modified Thursday, 3rd February 2022 11:42:00 am
 * @project  Winder
 * @brief
 *    
 *    Implementation of helper tools to be used to stringify quantities
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __UNITS_STRING_IMPL_STRING_H__
#define __UNITS_STRING_IMPL_STRING_H__

/* =========================================================== Includes =========================================================== */

#include <type_traits>
#include "units/string.hpp"
#include "units/bits/unit_text.h"

/* =========================================================== Namespace ========================================================== */

namespace units {

/* ========================================================== Definitions ========================================================= */

template<Quantity Q>
constexpr auto quantity_unit_to_string() {
    return ::units::detail::unit_text<typename Q::dimension, typename Q::unit>();
}

template<Quantity Q>
constexpr auto quantity_unit_to_standard_string() {

    // Get the standard symbol
    constexpr auto symbol = quantity_unit_to_string<Q>().standard();
    // Calculate it's size
    constexpr auto size = symbol.size();

    // Initialize an array holding the name
    char name[size + 1];
    // Construct the symbol manually
    for(unsigned i = 0; i != size; ++i)
        name[i] = symbol[i];
        
    return basic_fixed_string<char, size>(name);
    
}

template<Quantity Q>
constexpr auto quantity_unit_to_ascii_string() {

    // Get the ASCII symbol
    constexpr auto symbol = quantity_unit_to_string<Q>().ascii();
    // Calculate it's size
    constexpr auto size = symbol.size();

    // Initialize an array holding the name
    char name[size + 1];
    // Construct the symbol manually
    for(unsigned i = 0; i != size; ++i)
        name[i] = symbol[i];
        
    return basic_fixed_string<char, size>(name);
}

/* ================================================================================================================================ */

} // End namespace units

#endif
