/** ==================================================================================================================================
 * @file     typename.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Tuesday, 15th February 2022 5:27:08 am
 * @modified Tuesday, 15th February 2022 11:10:17 pm
 * @project  Winder
 * @brief
 *    
 *    Header file prividning compile-time print-specific specifiers for numeric conversions for templated types
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __ESTD_PRINTF_FORMAT_H__
#define __ESTD_PRINTF_FORMAT_H__

/* =========================================================== Includes =========================================================== */

#include <array>
#include "estd/fixed_string.hpp"

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ===================================================== Compiletime utilities ==================================================== */

/**
 * @brief Numeric notatrions supported by the printf
 */
enum class printf_notation {
    decimal,
    octal,
    hexadecimal,
    Hexadecimal,
    scientific,
    Scientific,
    shortes,
    Shortes
};

/**
 * @brief Helper wrapper around std::string_view providing additional methods formatting
 *    printf-format specifiers
 */
template<std::size_t Size>
class printf_format_string : public basic_fixed_string<char, Size> {
public:

    // Use basic constructor
    using basic_fixed_string<char, Size>::basic_fixed_string;

    /**
     * @brief Constructs printf_format_string from basic_fixed_string
     * 
     */
    constexpr printf_format_string(const basic_fixed_string<char, Size> &str) noexcept;

public:

    /**
     * @brief Helper method template returning printf format with @p modifier 
     *    inserted after '%' character
     * @tparam modifier 
     *    modifier to be inserted
     */
    template<std::size_t SizeMod>
    [[nodiscard]] constexpr printf_format_string<Size + SizeMod>
    mod(const basic_fixed_string<char, SizeMod> &modifier) const;

    /**
     * @brief Helper method template returning printf format with @p modifier 
     *    inserted after '%' character
     * @tparam modifier 
     *    modifier to be inserted
     */
    template<std::size_t SizeMod>
    [[nodiscard]] constexpr printf_format_string<Size + SizeMod - 1>
    mod(const char (&modifier)[SizeMod]) const;
};

/**
 * @brief CDAT for the basic_fixed_string when constructing from (char&)[]
 */
template <size_t Size>
printf_format_string(const char (&)[Size]) -> printf_format_string<Size - 1>;

/**
 * @brief CDAT for the basic_fixed_string when constructing from basic_fixed_string
 */
template <size_t Size>
printf_format_string(basic_fixed_string<char, Size>) -> printf_format_string<Size>;

/**
 * @brief Returns printf specifier for  the given @tparam T type
 * @tparam T 
 *    type to be converted
 * @tparam notation ( optional, default: @c printf_notation::decimal ) 
 *    notation used if numerical type given
 * @returns 
 *    name of the given @tparam T type
 */
template <class T, printf_notation notation = printf_notation::decimal>
[[nodiscard]] constexpr auto printf_format();

/* ================================================================================================================================ */

} // End namespace estd

/* ==================================================== Implementation includes =================================================== */

#include "estd/printf_format/impl/printf_format.hpp"

/* ================================================================================================================================ */

#endif
