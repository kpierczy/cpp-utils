/** ==================================================================================================================================
 * @file       print_format.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Tuesday, 15th February 2022 5:28:11 am
 * @modified   Tuesday, 15th February 2022 11:10:22 pm
 * @project    engineering-thesis
 * @brief
 *    
 *    Implementation of compile-time, compiler-dependent typename strings generation
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * ================================================================================================================================ */

#ifndef __ESTD_PRINTF_FORMAT_IMPL_PRINTF_FORMAT_H__
#define __ESTD_PRINTF_FORMAT_IMPL_PRINTF_FORMAT_H__

/* =========================================================== Includes =========================================================== */

#include <cstdint>
#include <type_traits>
#include "estd/printf_format.hpp"

/* ========================================================== Namespaces ========================================================== */

namespace estd {

/* ===================================================== Printf format string ===================================================== */

template<std::size_t Size>
constexpr printf_format_string<Size>::printf_format_string(const basic_fixed_string<char, Size> &str) noexcept
    : basic_fixed_string<char, Size>{ str }
{ }

template<std::size_t Size>
template<std::size_t SizeMod>
constexpr printf_format_string<Size + SizeMod> 
printf_format_string<Size>::mod(const basic_fixed_string<char, SizeMod> &modifier) const {
    using namespace ::estd::litarals;
    return 
        /* Initial '%'       */ "%"_fs +
        /* Inserted modifier */ modifier +
        /* Current specifier */ (*this).template substr<1, Size - 1>();
}


template<std::size_t Size>
template<std::size_t SizeMod>
constexpr printf_format_string<Size + SizeMod - 1> 
printf_format_string<Size>::mod(const char (&modifier)[SizeMod]) const {
    return mod(basic_fixed_string{ modifier });
}

/* ========================================================= Printf format ======================================================== */

template <typename T, printf_notation notation>
constexpr auto printf_format() {

    // Character
    if constexpr(std::is_same_v<T, char>) {
        return printf_format_string{ "%c" };
    // String
    } else if constexpr(std::is_same_v<T, const char *>) {
        return printf_format_string{ "%s" };

    /* ---------------- Fundamental numerical types ---------------- */

    // Short integers
    } else if constexpr(std::is_same_v<T, short int>) {
        return printf_format_string{ "%hd" };
    } else if constexpr(std::is_same_v<T, unsigned short int>) {
        if constexpr(notation == printf_notation::octal)
            return printf_format_string{ "%ho" };
        else if constexpr(notation == printf_notation::hexadecimal)
            return printf_format_string{ "%hx" };
        else if constexpr(notation == printf_notation::Hexadecimal)
            return printf_format_string{ "%hX" };
        else
            return printf_format_string{ "%hu" };
    // Integers
    } else if constexpr(std::is_same_v<T, int>) {
        return printf_format_string{ "%d" };
    } else if constexpr(std::is_same_v<T, unsigned int>) {
        if constexpr(notation == printf_notation::octal)
            return printf_format_string{ "%o" };
        else if constexpr(notation == printf_notation::hexadecimal)
            return printf_format_string{ "%x" };
        else if constexpr(notation == printf_notation::Hexadecimal)
            return printf_format_string{ "%X" };
        else
            return printf_format_string{ "%u" };
    // Long integers
    } else if constexpr(std::is_same_v<T, long int>) {
        return printf_format_string{ "%ld" };
    } else if constexpr(std::is_same_v<T, unsigned long int>) {
        if constexpr(notation == printf_notation::octal)
            return printf_format_string{ "%lo" };
        else if constexpr(notation == printf_notation::hexadecimal)
            return printf_format_string{ "%lx" };
        else if constexpr(notation == printf_notation::Hexadecimal)
            return printf_format_string{ "%lX" };
        else
            return printf_format_string{ "%lu" };
    // Long long integers
    } else if constexpr(std::is_same_v<T, long long int>) {
        return printf_format_string{ "%lld" };
    } else if constexpr(std::is_same_v<T, unsigned long long int>) {
        if constexpr(notation == printf_notation::octal)
            return printf_format_string{ "%llo" };
        else if constexpr(notation == printf_notation::hexadecimal)
            return printf_format_string{ "%llx" };
        else if constexpr(notation == printf_notation::Hexadecimal)
            return printf_format_string{ "%llX" };
        else
            return printf_format_string{ "%llu" };

    /* -------------- Specific-length numerical types -------------- */

    // 8-bit integers
    } else if constexpr(std::is_same_v<T, int8_t>) {
        return printf_format_string{ "%hhd" };
    } else if constexpr(std::is_same_v<T, uint8_t>) {
        if constexpr(notation == printf_notation::octal)
            return printf_format_string{ "%hho" };
        else if constexpr(notation == printf_notation::hexadecimal)
            return printf_format_string{ "%hhx" };
        else if constexpr(notation == printf_notation::Hexadecimal)
            return printf_format_string{ "%hhX" };
        else
            return printf_format_string{ "%hhu" };
    
    /* -------------- Floating-points numerical types -------------- */

    // Single-precision floating points
    } else if constexpr(std::is_same_v<T, float>) {
        if constexpr(notation == printf_notation::hexadecimal)
            return printf_format_string{ "%a" };
        else if constexpr(notation == printf_notation::Hexadecimal)
            return printf_format_string{ "%A" };
        else if constexpr(notation == printf_notation::scientific)
            return printf_format_string{ "%e" };
        else if constexpr(notation == printf_notation::Scientific)
            return printf_format_string{ "%E" };
        else if constexpr(notation == printf_notation::shortes)
            return printf_format_string{ "%g" };
        else if constexpr(notation == printf_notation::Shortes)
            return printf_format_string{ "%G" };
        else
            return printf_format_string{ "%f" };
    // Double-precision floating points
    } else if constexpr(std::is_same_v<T, double>) {
        if constexpr(notation == printf_notation::hexadecimal)
            return printf_format_string{ "%a" };
        else if constexpr(notation == printf_notation::Hexadecimal)
            return printf_format_string{ "%A" };
        else if constexpr(notation == printf_notation::scientific)
            return printf_format_string{ "%e" };
        else if constexpr(notation == printf_notation::Scientific)
            return printf_format_string{ "%E" };
        else if constexpr(notation == printf_notation::shortes)
            return printf_format_string{ "%g" };
        else if constexpr(notation == printf_notation::Shortes)
            return printf_format_string{ "%G" };
        else
            return printf_format_string{ "%f" };
    // Quadruple-precision floating points
    } else if constexpr(std::is_same_v<T, long double>) {
        if constexpr(notation == printf_notation::hexadecimal)
            return printf_format_string{ "%La" };
        else if constexpr(notation == printf_notation::Hexadecimal)
            return printf_format_string{ "%LA" };
        else if constexpr(notation == printf_notation::scientific)
            return printf_format_string{ "%Le" };
        else if constexpr(notation == printf_notation::Scientific)
            return printf_format_string{ "%LE" };
        else if constexpr(notation == printf_notation::shortes)
            return printf_format_string{ "%Lg" };
        else if constexpr(notation == printf_notation::Shortes)
            return printf_format_string{ "%LG" };
        else
            return printf_format_string{ "%Lf" };

    /* ------------------------------------------------------------- */

    } else if(std::is_pointer_v<T>) {
        return printf_format_string{ "%p" };
    }

}

/* ================================================================================================================================ */

} // End namespace estd

#endif
