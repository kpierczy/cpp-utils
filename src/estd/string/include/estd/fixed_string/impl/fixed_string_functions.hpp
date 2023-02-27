/* ============================================================================================================================ *//**
 * @file       fixed_string.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Tuesday, 15th February 2022 8:23:43 pm
 * @modified   Sunday, 26th June 2022 11:56:58 am
 * @project    cpp-utils
 * @brief      Implementation of free functions related to the compile-time strings literal
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_FIXED_STRING_FUNCTIONS_IMPL_H__
#define __ESTD_FIXED_STRING_FUNCTIONS_IMPL_H__

/* =========================================================== Includes =========================================================== */

#include "estd/fixed_string.hpp"

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ============================================================ Helpers =========================================================== */

namespace details {

    /**
     * @brief Converts character to the fixed string
     * 
     * @tparam CharType 
     *    type of the character
     * @param ch 
     *    character to be converted
     * @returns 
     *     character converted to string
     */
    template <typename CharType>
    constexpr basic_fixed_string<CharType, 1> from_char(CharType ch) {
        basic_fixed_string<CharType, 1> fs;
        fs[0] = ch;
        return fs;
    }

}

/* ===================================================== Comparison operators ===================================================== */

template <typename CharType, typename TraitsType, size_t Size1, size_t Size2>
[[nodiscard]] constexpr bool operator==(
    const basic_fixed_string<CharType, Size1, TraitsType>& lhs,
    const basic_fixed_string<CharType, Size2, TraitsType>& rhs
) {
    if constexpr (Size1 != Size2)
        return false;
    using lhs_type = std::decay_t<decltype(lhs)>;
    using sv_type = typename lhs_type::string_view_type;
    return static_cast<sv_type>(lhs) == rhs;
}


template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr bool operator==(
    const basic_fixed_string<CharType, Size, TraitsType>& lhs,
    std::basic_string_view<CharType, TraitsType> rhs
) {
    using lhs_type = std::decay_t<decltype(lhs)>;
    using sv_type = typename lhs_type::string_view_type;
    return static_cast<sv_type>(lhs) == rhs;
}


template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr bool operator==(
    std::basic_string_view<CharType, TraitsType> lhs,
    const basic_fixed_string<CharType, Size, TraitsType>& rhs
) {
    using rhs_type = std::decay_t<decltype(rhs)>;
    using sv_type = typename rhs_type::string_view_type;
    return lhs == static_cast<sv_type>(rhs);
}

#if CPP20_SPACESHIP_OPERATOR_PRESENT

template <typename CharType, typename TraitsType, size_t Size1, size_t Size2>
[[nodiscard]] constexpr auto operator<=>(
    const basic_fixed_string<CharType, Size1, TraitsType>& lhs,
    const basic_fixed_string<CharType, Size2, TraitsType>& rhs
) {
    using lhs_type = std::decay_t<decltype(lhs)>;
    using sv_type = typename lhs_type::string_view_type;
    return static_cast<sv_type>(lhs) <=> rhs;
}


template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr auto operator<=>(
    const basic_fixed_string<CharType, Size, TraitsType>& lhs,
    std::basic_string_view<CharType, TraitsType> rhs
) {
    using lhs_type = std::decay_t<decltype(lhs)>;
    using sv_type = typename lhs_type::string_view_type;
    return static_cast<sv_type>(lhs) <=> rhs;
}


template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr auto operator<=>(
    std::basic_string_view<CharType, TraitsType> lhs,
    const basic_fixed_string<CharType, Size, TraitsType>& rhs
) {
    using rhs_type = std::decay_t<decltype(rhs)>;
    using sv_type = typename rhs_type::string_view_type;
    return lhs <=> static_cast<sv_type>(rhs);
}

#else

template <typename CharType, typename TraitsType, size_t Size1, size_t Size2>
[[nodiscard]] constexpr bool operator!=(
    const basic_fixed_string<CharType, Size1, TraitsType>& lhs,
    const basic_fixed_string<CharType, Size2, TraitsType>& rhs
) {
    if constexpr (Size1 != Size2)
        return true;
    using lhs_type = std::decay_t<decltype(lhs)>;
    using sv_type = typename lhs_type::string_view_type;
    return static_cast<sv_type>(lhs) != rhs;
}


template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr bool operator!=(
    const basic_fixed_string<CharType, Size, TraitsType>& lhs,
    std::basic_string_view<CharType, TraitsType> rhs
) {
    using lhs_type = std::decay_t<decltype(lhs)>;
    using sv_type = typename lhs_type::string_view_type;
    return static_cast<sv_type>(lhs) != rhs;
}


template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr bool operator!=(
    std::basic_string_view<CharType, TraitsType> lhs,
    const basic_fixed_string<CharType, Size, TraitsType>& rhs
) {
    using rhs_type = std::decay_t<decltype(rhs)>;
    using sv_type = typename rhs_type::string_view_type;
    return lhs != static_cast<sv_type>(rhs);
}


template <typename CharType, typename TraitsType, size_t Size1, size_t Size2>
[[nodiscard]] constexpr bool operator<(
    const basic_fixed_string<CharType, Size1, TraitsType>& lhs,
    const basic_fixed_string<CharType, Size2, TraitsType>& rhs
) {
    using lhs_type = std::decay_t<decltype(lhs)>;
    using sv_type = typename lhs_type::string_view_type;
    return static_cast<sv_type>(lhs) < rhs;
}


template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr bool operator<(
    const basic_fixed_string<CharType, Size, TraitsType>& lhs,
    std::basic_string_view<CharType, TraitsType> rhs
) {
    using lhs_type = std::decay_t<decltype(lhs)>;
    using sv_type = typename lhs_type::string_view_type;
    return static_cast<sv_type>(lhs) < rhs;
}


template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr bool operator<(
    std::basic_string_view<CharType, TraitsType> lhs,
    const basic_fixed_string<CharType, Size, TraitsType>& rhs
) {
    using rhs_type = std::decay_t<decltype(rhs)>;
    using sv_type = typename rhs_type::string_view_type;
    return lhs < static_cast<sv_type>(rhs);
}


template <typename CharType, typename TraitsType, size_t Size1, size_t Size2>
[[nodiscard]] constexpr bool operator<=(
    const basic_fixed_string<CharType, Size1, TraitsType>& lhs,
    const basic_fixed_string<CharType, Size2, TraitsType>& rhs
) {
    using lhs_type = std::decay_t<decltype(lhs)>;
    using sv_type = typename lhs_type::string_view_type;
    return static_cast<sv_type>(lhs) <= rhs;
}


template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr bool operator<=(
    const basic_fixed_string<CharType, Size, TraitsType>& lhs,
    std::basic_string_view<CharType, TraitsType> rhs
) {
    using lhs_type = std::decay_t<decltype(lhs)>;
    using sv_type = typename lhs_type::string_view_type;
    return static_cast<sv_type>(lhs) <= rhs;
}


template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr bool operator<=(
    std::basic_string_view<CharType, TraitsType> lhs,
    const basic_fixed_string<CharType, Size, TraitsType>& rhs
) {
    using rhs_type = std::decay_t<decltype(rhs)>;
    using sv_type = typename rhs_type::string_view_type;
    return lhs <= static_cast<sv_type>(rhs);
}


template <typename CharType, typename TraitsType, size_t Size1, size_t Size2>
[[nodiscard]] constexpr bool operator>(
    const basic_fixed_string<CharType, Size1, TraitsType>& lhs,
    const basic_fixed_string<CharType, Size2, TraitsType>& rhs
) {
    using lhs_type = std::decay_t<decltype(lhs)>;
    using sv_type = typename lhs_type::string_view_type;
    return static_cast<sv_type>(lhs) > rhs;
}


template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr bool operator>(
    const basic_fixed_string<CharType, Size, TraitsType>& lhs,
    std::basic_string_view<CharType, TraitsType> rhs
) {
    using lhs_type = std::decay_t<decltype(lhs)>;
    using sv_type = typename lhs_type::string_view_type;
    return static_cast<sv_type>(lhs) > rhs;
}


template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr bool operator>(
    std::basic_string_view<CharType, TraitsType> lhs,
    const basic_fixed_string<CharType, Size, TraitsType>& rhs
) {
    using rhs_type = std::decay_t<decltype(rhs)>;
    using sv_type = typename rhs_type::string_view_type;
    return lhs > static_cast<sv_type>(rhs);
}


template <typename CharType, typename TraitsType, size_t Size1, size_t Size2>
[[nodiscard]] constexpr bool operator>=(
    const basic_fixed_string<CharType, Size1, TraitsType>& lhs,
    const basic_fixed_string<CharType, Size2, TraitsType>& rhs
) {
    using lhs_type = std::decay_t<decltype(lhs)>;
    using sv_type = typename lhs_type::string_view_type;
    return static_cast<sv_type>(lhs) >= rhs;
}


template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr bool operator>=(
    const basic_fixed_string<CharType, Size, TraitsType>& lhs,
    std::basic_string_view<CharType, TraitsType> rhs
) {
    using lhs_type = std::decay_t<decltype(lhs)>;
    using sv_type = typename lhs_type::string_view_type;
    return static_cast<sv_type>(lhs) >= rhs;
}


template <typename CharType, typename TraitsType, size_t Size>
[[nodiscard]] constexpr bool operator>=(
    std::basic_string_view<CharType, TraitsType> lhs,
    const basic_fixed_string<CharType, Size, TraitsType>& rhs
) {
    using rhs_type = std::decay_t<decltype(rhs)>;
    using sv_type = typename rhs_type::string_view_type;
    return lhs >= static_cast<sv_type>(rhs);
}

#endif

/* ====================================================== Addition operators ====================================================== */

template <typename CharType, size_t Size, size_t N, typename TraitsType>
constexpr basic_fixed_string<CharType, Size + N, TraitsType> operator+(
    const basic_fixed_string<CharType, Size, TraitsType>& lhs,
    const basic_fixed_string<CharType, N, TraitsType>& rhs
) {
    basic_fixed_string<CharType, Size + N, TraitsType> result;
    details::copy(lhs.begin(), lhs.end(), result.begin());
    details::copy(rhs.begin(), rhs.end(), result.begin() + Size);
    return result;
}

template <typename CharType, size_t Size, size_t N, typename TraitsType>
constexpr basic_fixed_string<CharType, Size - 1 + N, TraitsType> operator+(
    const CharType (&lhs)[Size],
    const basic_fixed_string<CharType, N, TraitsType>& rhs
) {
    basic_fixed_string lhs2 = lhs;
    return lhs2 + rhs;
}

template <typename CharType, size_t Size, size_t N, typename TraitsType>
constexpr basic_fixed_string<CharType, Size + N - 1, TraitsType> operator+(
    const basic_fixed_string<CharType, Size, TraitsType>& lhs,
    const CharType (&rhs)[N]
) {
    basic_fixed_string rhs2 = rhs;
    return lhs + rhs2;
}

template <typename CharType, size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size + 1, TraitsType> operator+(
    CharType lhs,
    const basic_fixed_string<CharType, Size, TraitsType>& rhs
) {
    return details::from_char(lhs) + rhs;
}

template <typename CharType, size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size + 1, TraitsType> operator+(
    const basic_fixed_string<CharType, Size, TraitsType>& lhs,
    CharType rhs
) {
    return lhs + details::from_char(rhs);
}

/* ==================================================== Pipes-related operators =================================================== */

template <typename CharType, size_t Size, typename TraitsType>
std::basic_ostream<CharType, TraitsType>& operator<<(
    std::basic_ostream<CharType, TraitsType>& out,
    const basic_fixed_string<CharType, Size, TraitsType>& str
) {
    out << str.data();
    return out;
}

/* ========================================================== Algorithms ========================================================== */

template <typename CharType, typename TraitsType, size_t Size>
void swap(
    basic_fixed_string<CharType, Size, TraitsType>& lhs,
    basic_fixed_string<CharType, Size, TraitsType>& rhs
) noexcept(noexcept(lhs.swap(rhs))) {
    lhs.swap(rhs);
}

/* ================================================================================================================================ */

} // End namespace estd

/* ======================================================== Hash functions ======================================================== */

namespace std {

    template <size_t Size>
    size_t hash<estd::fixed_string<Size>>::operator()(const argument_type& str) const {
        using sv_t = typename argument_type::string_view_type;
        return std::hash<sv_t>()(static_cast<sv_t>(str));
    }

#if FIXSTR_CPP20_CHAR8T_PRESENT

    template <size_t Size>
    size_t hash<estd::fixed_u8string<Size>>::operator()(const argument_type& str) const {
        using sv_t = typename argument_type::string_view_type;
        return std::hash<sv_t>()(static_cast<sv_t>(str));
    }

#endif // FIXSTR_CPP20_CHAR8T_PRESENT

    template <size_t Size>
    size_t hash<estd::fixed_u16string<Size>>::operator()(const argument_type& str) const {
        using sv_t = typename argument_type::string_view_type;
        return std::hash<sv_t>()(static_cast<sv_t>(str));
    }

    template <size_t Size>
    size_t hash<estd::fixed_u32string<Size>>::operator()(const argument_type& str) const {
        using sv_t = typename argument_type::string_view_type;
        return std::hash<sv_t>()(static_cast<sv_t>(str));
    }

    template <size_t Size>
    size_t hash<estd::fixed_wstring<Size>>::operator()(const argument_type& str) const {
        using sv_t = typename argument_type::string_view_type;
        return std::hash<sv_t>()(static_cast<sv_t>(str));
    }

} // End namespace std

/* ================================================================================================================================ */

#endif
