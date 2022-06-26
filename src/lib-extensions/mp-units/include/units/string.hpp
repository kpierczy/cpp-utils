/* ============================================================================================================================ *//**
 * @file       string.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Friday, 28th January 2022 1:45:30 pm
 * @modified   Sunday, 26th June 2022 11:56:59 am
 * @project    cpp-utils
 * @brief      Set of helper tools to be used to stringify quantities
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __UNITS_STRING_H__
#define __UNITS_STRING_H__

/* =========================================================== Includes =========================================================== */

#include <string_view>
#include "units/quantity.h"

/* =========================================================== Namespace ========================================================== */

namespace units {
    
/* ========================================================= Declarations ========================================================= */

/**
 * @brief Helper function returning @ref units::basic_symbol_text representing symbol
 *    of the unit of the given @tparam Q quantity
 * @tparam Q 
 *     quantity type to be processed
 */
template<Quantity Q>
constexpr auto quantity_unit_to_string();

/**
 * @brief Helper function returning @ref units::fixed_string containing standard symbol of the
 *     unit of the given @tparam Q quantity. The returned string is equivalent to 
 *     @c quantity_unit_to_string<Q>.standard().
 * @tparam Q 
 *     quantity type to be processed
 */
template<Quantity Q>
constexpr auto quantity_unit_to_standard_string();

/**
 * @brief Helper function returning @ref units::fixed_string containing ASCII symbol of the
 *     unit of the given @tparam Q quantity. The returned string is equivalent to 
 *     @c quantity_unit_to_string<Q>.standard().
 * @tparam Q 
 *     quantity type to be processed
 */
template<Quantity Q>
constexpr auto quantity_unit_to_ascii_string();

/* ================================================================================================================================ */

} // End namespace units

/* ==================================================== Implementation includes =================================================== */

#include "units/string/impl/string.hpp"

/* ================================================================================================================================ */

#endif
