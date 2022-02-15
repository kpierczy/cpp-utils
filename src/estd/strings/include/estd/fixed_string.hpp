/** ==================================================================================================================================
 * @file     fixed_string.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Monday, 12th July 2021 9:25:13 am
 * @modified Tuesday, 15th February 2022 12:49:14 am
 * @project  Winder
 * @brief
 *    
 *    Header file of compile-time strings
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __ESTD_FIXED_STRING_H__
#define __ESTD_FIXED_STRING_H__

/* =========================================================== Includes =========================================================== */

#include <string_view>

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ===================================================== Compiletime utilities ==================================================== */

/**
 * @brief Compil-time string
 * 
 * @tparam Size 
 */
template <auto Size>
struct fixed_string {
public:

    // Size of the string
    static constexpr auto size = Size;

public:

    /**
     * @brief Constructs fixed_string from the array of chars
     * @param str 
     *    source array to be copied
     */
    constexpr explicit(false) fixed_string(char const* str);

    /**
     * @brief Converts fixed_string to the std::string_view
     */
    constexpr explicit(false) operator std::string_view() const;

public:

    // Data hold by the string
    char data[Size + 1]{};

};

/**
 * @brief Helper user-defined deduction guide
 */
template <auto Size>
fixed_string(char const (&)[Size]) -> fixed_string<Size - 1>;

/* ================================================================================================================================ */

} // End namespace estd

/* ==================================================== Implementation includes =================================================== */

#include "estd/fixed_string/impl/fixed_string.hpp"

/* ================================================================================================================================ */

#endif
