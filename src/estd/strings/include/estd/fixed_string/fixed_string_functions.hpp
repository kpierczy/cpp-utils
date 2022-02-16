/** ==================================================================================================================================
 * @file     fixed_string.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Tuesday, 15th February 2022 8:23:43 pm
 * @modified Tuesday, 15th February 2022 8:58:36 pm
 * @project  Winder
 * @brief
 *    
 *    Implementation of free functions related to the compile-time strings literal
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __ESTD_FIXED_STRING_FUNCTIONS_H__
#define __ESTD_FIXED_STRING_FUNCTIONS_H__

/* =========================================================== Includes =========================================================== */

#include "estd/fixed_string.hpp"

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ===================================================== Comparison operators ===================================================== */

template <typename CharType, typename TraitsType, size_t Size1, size_t Size2>
[[nodiscard]] constexpr bool operator==(
    const basic_fixed_string<CharType, Size1, TraitsType>& lhs,
    const basic_fixed_string<CharType, Size2, TraitsType>& rhs
);

template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr bool operator==(
    const basic_fixed_string<CharType, Size, TraitsType>& lhs,
    std::basic_string_view<CharType, TraitsType> rhs
);

template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr bool operator==(
    std::basic_string_view<CharType, TraitsType> lhs,
    const basic_fixed_string<CharType, Size, TraitsType>& rhs
);

#if CPP20_SPACESHIP_OPERATOR_PRESENT

template <typename CharType, typename TraitsType, size_t Size1, size_t Size2>
[[nodiscard]] constexpr auto operator<=>(
    const basic_fixed_string<CharType, Size1, TraitsType>& lhs,
    const basic_fixed_string<CharType, Size2, TraitsType>& rhs
);

template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr auto operator<=>(
    const basic_fixed_string<CharType, Size, TraitsType>& lhs,
    std::basic_string_view<CharType, TraitsType> rhs
);

template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr auto operator<=>(
    std::basic_string_view<CharType, TraitsType> lhs,
    const basic_fixed_string<CharType, Size, TraitsType>& rhs
);

#else

template <typename CharType, typename TraitsType, size_t Size1, size_t Size2>
[[nodiscard]] constexpr bool operator!=(
    const basic_fixed_string<CharType, Size1, TraitsType>& lhs,
    const basic_fixed_string<CharType, Size2, TraitsType>& rhs
);

template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr bool operator!=(
    const basic_fixed_string<CharType, Size, TraitsType>& lhs,
    std::basic_string_view<CharType, TraitsType> rhs
);

template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr bool operator!=(
    std::basic_string_view<CharType, TraitsType> lhs,
    const basic_fixed_string<CharType, Size, TraitsType>& rhs
);

template <typename CharType, typename TraitsType, size_t Size1, size_t Size2>
[[nodiscard]] constexpr bool operator<(
    const basic_fixed_string<CharType, Size1, TraitsType>& lhs,
    const basic_fixed_string<CharType, Size2, TraitsType>& rhs
);

template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr bool operator<(
    const basic_fixed_string<CharType, Size, TraitsType>& lhs,
    std::basic_string_view<CharType, TraitsType> rhs
);

template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr bool operator<(
    std::basic_string_view<CharType, TraitsType> lhs,
    const basic_fixed_string<CharType, Size, TraitsType>& rhs
);

template <typename CharType, typename TraitsType, size_t Size1, size_t Size2>
[[nodiscard]] constexpr bool operator<=(
    const basic_fixed_string<CharType, Size1, TraitsType>& lhs,
    const basic_fixed_string<CharType, Size2, TraitsType>& rhs
);

template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr bool operator<=(
    const basic_fixed_string<CharType, Size, TraitsType>& lhs,
    std::basic_string_view<CharType, TraitsType> rhs
);

template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr bool operator<=(
    std::basic_string_view<CharType, TraitsType> lhs,
    const basic_fixed_string<CharType, Size, TraitsType>& rhs
);

template <typename CharType, typename TraitsType, size_t Size1, size_t Size2>
[[nodiscard]] constexpr bool operator>(
    const basic_fixed_string<CharType, Size1, TraitsType>& lhs,
    const basic_fixed_string<CharType, Size2, TraitsType>& rhs
);

template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr bool operator>(
    const basic_fixed_string<CharType, Size, TraitsType>& lhs,
    std::basic_string_view<CharType, TraitsType> rhs
);

template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr bool operator>(
    std::basic_string_view<CharType, TraitsType> lhs,
    const basic_fixed_string<CharType, Size, TraitsType>& rhs
);

template <typename CharType, typename TraitsType, size_t Size1, size_t Size2>
[[nodiscard]] constexpr bool operator>=(
    const basic_fixed_string<CharType, Size1, TraitsType>& lhs,
    const basic_fixed_string<CharType, Size2, TraitsType>& rhs
);

template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr bool operator>=(
    const basic_fixed_string<CharType, Size, TraitsType>& lhs,
    std::basic_string_view<CharType, TraitsType> rhs
);

template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr bool operator>=(
    std::basic_string_view<CharType, TraitsType> lhs,
    const basic_fixed_string<CharType, Size, TraitsType>& rhs
);

#endif

/* ====================================================== Addition operators ====================================================== */

template <typename CharType, size_t Size, size_t N, typename TraitsType>
constexpr basic_fixed_string<CharType, Size + N, TraitsType> operator+(
    const basic_fixed_string<CharType, Size, TraitsType>& lhs,
    const basic_fixed_string<CharType, N, TraitsType>& rhs
);

template <typename CharType, size_t Size, size_t N, typename TraitsType>
constexpr basic_fixed_string<CharType, Size - 1 + N, TraitsType> operator+(
    const CharType (&lhs)[Size],
    const basic_fixed_string<CharType, N, TraitsType>& rhs
);

template <typename CharType, size_t Size, size_t N, typename TraitsType>
constexpr basic_fixed_string<CharType, Size + N - 1, TraitsType> operator+(
    const basic_fixed_string<CharType, Size, TraitsType>& lhs,
    const CharType (&rhs)[N]
);

template <typename CharType, size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size + 1, TraitsType> operator+(
    CharType lhs,
    const basic_fixed_string<CharType, Size, TraitsType>& rhs
);

template <typename CharType, size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size + 1, TraitsType> operator+(
    const basic_fixed_string<CharType, Size, TraitsType>& lhs,
    CharType rhs
);

/* ==================================================== Pipes-related operators =================================================== */

template <typename CharType, size_t Size, typename TraitsType>
std::basic_ostream<CharType, TraitsType>& operator<<(
    std::basic_ostream<CharType, TraitsType>& out,
    const basic_fixed_string<CharType, Size, TraitsType>& str
);

/* ========================================================== Algorithms ========================================================== */

template <typename CharType, typename TraitsType, size_t Size>
void swap(
    basic_fixed_string<CharType, Size, TraitsType>& lhs,
    basic_fixed_string<CharType, Size, TraitsType>& rhs
) noexcept(noexcept(lhs.swap(rhs)));

/* ================================================================================================================================ */

} // End namespace estd

/* ======================================================== Hash functions ======================================================== */

namespace std {

    /**
     * @brief Helper class for hash support for fixed_strings
     * @tparam Size 
     *    size of the fixed_string
     */
    template <size_t Size>
    struct hash<estd::fixed_string<Size>> {

        /// Type of hashed string
        using argument_type = estd::fixed_string<Size>;

        /**
         * @brief Hashing oeprator
         * @param str 
         *    string to be hashed
         * @returns 
         *     size of the hash
         */
        size_t operator()(const argument_type& str) const;
    };

#if FIXSTR_CPP20_CHAR8T_PRESENT

    /**
     * @brief Helper class for hash support for fixed_u8string
     * @tparam Size 
     *    size of the fixed_u8string
     */
    template <size_t Size>
    struct hash<estd::fixed_u8string<Size>> {

        /// Type of hashed string
        using argument_type = estd::fixed_u8string<Size>;

        /**
         * @brief Hashing oeprator
         * @param str 
         *    string to be hashed
         * @returns 
         *     size of the hash
         */
        size_t operator()(const argument_type& str) const;
        
    };

#endif // FIXSTR_CPP20_CHAR8T_PRESENT

    /**
     * @brief Helper class for hash support for fixed_u16string
     * @tparam Size 
     *    size of the fixed_u16string
     */
    template <size_t Size>
    struct hash<estd::fixed_u16string<Size>> {

        /// Type of hashed string
        using argument_type = estd::fixed_u16string<Size>;
        
        /**
         * @brief Hashing oeprator
         * @param str 
         *    string to be hashed
         * @returns 
         *     size of the hash
         */
        size_t operator()(const argument_type& str) const;

    };

    /**
     * @brief Helper class for hash support for fixed_u32string
     * @tparam Size 
     *    size of the fixed_u32string
     */
    template <size_t Size>
    struct hash<estd::fixed_u32string<Size>> {

        /// Type of hashed string
        using argument_type = estd::fixed_u32string<Size>;

        /**
         * @brief Hashing oeprator
         * @param str 
         *    string to be hashed
         * @returns 
         *     size of the hash
         */
        size_t operator()(const argument_type& str) const;
        
    };

    /**
     * @brief Helper class for hash support for fixed_wstring
     * @tparam Size 
     *    size of the fixed_wstring
     */
    template <size_t Size>
    struct hash<estd::fixed_wstring<Size>> {

        /// Type of hashed string
        using argument_type = estd::fixed_wstring<Size>;

        /**
         * @brief Hashing oeprator
         * @param str 
         *    string to be hashed
         * @returns 
         *     size of the hash
         */
        size_t operator()(const argument_type& str) const;
        
    };

} // End namespace std

/* ==================================================== Implementation includes =================================================== */

#include "estd/fixed_string/impl/fixed_string_functions.hpp"

/* ================================================================================================================================ */

#endif
