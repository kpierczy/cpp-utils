/** ==================================================================================================================================
 * @file     enum.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Thursday, 3rd February 2022 11:10:53 am
 * @modified Thursday, 3rd February 2022 11:11:56 am
 * @project  cpp-utils
 * @brief
 *    
 *    
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * ================================================================================================================================ */

#ifndef __ESTD_ENUM_IMPL_ENUM_H__
#define __ESTD_ENUM_IMPL_ENUM_H__

/* =========================================================== Includes =========================================================== */

#include "estd/enum.hpp"

/* ========================================================== Namespaces ========================================================== */

namespace enum {

/* ========================================================== Definitions ========================================================= */

template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr std::underlying_type_t<Enum> to_underlying(const Enum &value) noexcept {
    return static_cast<std::underlying_type_t<Enum>>(value);
}


template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr Enum to_enum(const std::underlying_type_t<Enum> &value) noexcept {
    return static_cast<Enum>(value);
}


template<typename Enum>
    requires std::is_enum_v<Enum>
inline constexpr bool is_valid_enum(Enum value, Enum min, Enum max) noexcept {
    return (
        ( to_underlying(value) >= to_underlying(min) ) and
        ( to_underlying(value) <= to_underlying(max) )
    );
}

/* ================================================================================================================================ */

} // End namespace enum

#endif
