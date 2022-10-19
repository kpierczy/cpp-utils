/* ============================================================================================================================ *//**
 * @file       enum.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 3rd February 2022 11:08:21 am
 * @modified   Wednesday, 19th October 2022 9:57:37 pm
 * @project    cpp-utils
 * @brief
 *    
 *    
 *    
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_ENUM_H__
#define __ESTD_ENUM_H__

/* =========================================================== Includes =========================================================== */

#include <type_traits>

/* ========================================================== Namespaces ========================================================== */

namespace estd {

/* ========================================================= Declarations ========================================================= */

/**
 * @brief Converts an arbitrary enumeration to it's underlying numerical type
 * @tparam Enum 
 *    Enum type
 * @param value
 *    value to be converted 
 * @returns 
 *    enum converted to numerical value
 */
template<typename Enum>
    requires std::is_enum_v<Enum>
inline constexpr std::underlying_type_t<Enum> to_underlying(const Enum &value) noexcept;

/**
 * @brief Converts a numerical value to an arbitrary enumeration
 * @tparam Enum 
 *    Enum type
 * @param value
 *    value to be converted 
 * @returns 
 *    numerical value converted to enum 
 */
template<typename Enum>
    requires std::is_enum_v<Enum>
inline constexpr Enum to_enum(const std::underlying_type_t<Enum> &value) noexcept;

/**
 * @brief Checks whether the @p value is a valid Enum in tange defined by @p min and @p max
 * @tparam Enum 
 *    Enum type
 * @param value
 *    value to be compared 
 * @param min
 *    minimal value represented by the enum
 * @param max
 *    maximal value represented by the enum
 * @returns 
 *    numerical value converted to enum 
 */
template<typename Enum>
    requires std::is_enum_v<Enum>
inline constexpr bool is_valid_enum(Enum value, Enum min, Enum max) noexcept;

/* ================================================================================================================================ */

} // End namespace estd

/* ==================================================== Implementation includes =================================================== */

#include "estd/enum/impl/enum.hpp"

/* ================================================================================================================================ */

#endif
