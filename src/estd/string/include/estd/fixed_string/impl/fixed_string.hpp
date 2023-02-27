/* ============================================================================================================================ *//**
 * @file       fixed_string.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Monday, 12th July 2021 9:29:30 am
 * @modified   Sunday, 26th June 2022 11:56:58 am
 * @project    cpp-utils
 * @brief      Implementation of the compile-time strings literal
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_FIXED_STRING_IMPL_FIXED_STRING_H__
#define __ESTD_FIXED_STRING_IMPL_FIXED_STRING_H__

/* =========================================================== Includes =========================================================== */

#include "estd/fixed_string.hpp"

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ======================================================== Private methods ======================================================= */

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::string_view_type 
basic_fixed_string<CharType, Size, TraitsType>::sv() const { return *this; }

/* ====================================================== Public constructors ===================================================== */

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::basic_fixed_string(const value_type (&array)[Size + 1]) noexcept {
    details::copy(std::begin(array), std::end(array), _data.begin());
}

/* ======================================================= Public iterators ======================================================= */

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::iterator 
basic_fixed_string<CharType, Size, TraitsType>::begin() noexcept { return _data.begin(); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::const_iterator 
basic_fixed_string<CharType, Size, TraitsType>::begin() const noexcept { return _data.begin(); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::iterator 
basic_fixed_string<CharType, Size, TraitsType>::end() noexcept { return _data.end() - 1; }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::const_iterator 
basic_fixed_string<CharType, Size, TraitsType>::end() const noexcept { return _data.end() - 1; }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::const_iterator 
basic_fixed_string<CharType, Size, TraitsType>::cbegin() const noexcept { return _data.cbegin(); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::const_iterator 
basic_fixed_string<CharType, Size, TraitsType>::cend() const noexcept { return _data.cend() - 1; }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::reverse_iterator 
basic_fixed_string<CharType, Size, TraitsType>::rbegin() noexcept { return _data.rbegin() + 1; }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::const_reverse_iterator 
basic_fixed_string<CharType, Size, TraitsType>::rbegin() const noexcept { return _data.rbegin() + 1; }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::reverse_iterator 
basic_fixed_string<CharType, Size, TraitsType>::rend() noexcept { return _data.rend(); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::const_reverse_iterator 
basic_fixed_string<CharType, Size, TraitsType>::rend() const noexcept { return _data.rend(); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::const_reverse_iterator 
basic_fixed_string<CharType, Size, TraitsType>::crbegin() const noexcept { return _data.crbegin() + 1; }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::const_reverse_iterator 
basic_fixed_string<CharType, Size, TraitsType>::crend() const noexcept { return _data.crend(); }

/* ======================================================= Public operators ======================================================= */

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>& 
basic_fixed_string<CharType, Size, TraitsType>::operator=(const value_type (&array)[Size + 1]) noexcept {
    details::copy(std::begin(array), std::end(array), _data.begin());
    return *this;
}

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::reference 
basic_fixed_string<CharType, Size, TraitsType>::operator[](size_type n) { return _data[n]; }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::const_reference 
basic_fixed_string<CharType, Size, TraitsType>::operator[](size_type n) const { return _data[n]; }


template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::operator string_view_type() const noexcept {
    return {data(), Size};
}

/* ======================================================== Public methods ======================================================== */

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::size() const noexcept { return Size; }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::length() const noexcept { return Size; }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::max_size() const noexcept { return Size; }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr bool 
basic_fixed_string<CharType, Size, TraitsType>::empty() const noexcept { return Size == 0; }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::reference
basic_fixed_string<CharType, Size, TraitsType>::at(size_type n) { return _data.at(n); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::const_reference
basic_fixed_string<CharType, Size, TraitsType>::at(size_type n) const { return _data.at(n); }


template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::reference
basic_fixed_string<CharType, Size, TraitsType>::front() noexcept requires (Size != 0) { return _data.front(); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::const_reference
basic_fixed_string<CharType, Size, TraitsType>::front() const noexcept requires (Size != 0) { return _data.front(); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::reference
basic_fixed_string<CharType, Size, TraitsType>::back() noexcept requires (Size != 0) { return _data[size() - 1]; }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::const_reference
basic_fixed_string<CharType, Size, TraitsType>::back() const noexcept requires (Size != 0) { return _data[size() - 1]; }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::pointer
basic_fixed_string<CharType, Size, TraitsType>::data() noexcept { return _data.data(); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::const_pointer
basic_fixed_string<CharType, Size, TraitsType>::data() const noexcept { return _data.data(); }

/* ======================================================= Public algorithms ====================================================== */

/* -------------------------------------------------------- Find algorithms ------------------------------------------------------- */

template <typename CharType, std::size_t Size, typename TraitsType>
template <size_t M>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::find(const same_with_other_size<M>& str, size_type pos) const noexcept {
    if constexpr (M > Size)
        return npos;
    return sv().find(str.sv(), pos);
}

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::find(string_view_type sv, size_type pos) const noexcept { return sv().find(sv, pos); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::find(const value_type* s, size_type pos, size_type n) const { return sv().find(s, pos, n); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::find(const value_type* s, size_type pos) const { return sv().find(s, pos); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::find(value_type c, size_type pos) const noexcept { return sv().find(c, pos); }

/* ---------------------------------------------------- Revers Find algorithms ---------------------------------------------------- */

template <typename CharType, std::size_t Size, typename TraitsType>
template <size_t M>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::rfind(const same_with_other_size<M>& str, size_type pos) const noexcept {
    if constexpr (M > Size)
        return npos;
    return sv().rfind(str.sv(), pos);
}

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::rfind(string_view_type sv, size_type pos) const noexcept { return sv().rfind(sv, pos); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::rfind(const value_type* s, size_type pos, size_type n) const { return sv().rfind(s, pos, n); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::rfind(const value_type* s, size_type pos) const { return sv().rfind(s, pos); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::rfind(value_type c, size_type pos) const noexcept { return sv().rfind(c, pos); }

/* --------------------------------------------------- Find-first-of algorithms --------------------------------------------------- */

template <typename CharType, std::size_t Size, typename TraitsType>
template <size_t M>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::find_first_of(const same_with_other_size<M>& str, size_type pos) const noexcept {
    if constexpr (M > Size)
        return npos;
    return sv().find_first_of(str.sv(), pos);
}

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::find_first_of(string_view_type sv, size_type pos) const noexcept { return sv().find_first_of(sv, pos); }


template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::find_first_of(const value_type* s, size_type pos, size_type n) const { return sv().find_first_of(s, pos, n); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::find_first_of(const value_type* s, size_type pos) const { return sv().find_first_of(s, pos); }


template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::find_first_of(value_type c, size_type pos) const noexcept { return sv().find_first_of(c, pos); }

/* ---------------------------------------------------- Find-last-of algorithms --------------------------------------------------- */

template <typename CharType, std::size_t Size, typename TraitsType>
template <size_t M>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::find_last_of(const same_with_other_size<M>& str, size_type pos) const noexcept {
    if constexpr (M > Size)
        return npos;
    return sv().find_last_of(str.sv(), pos);
}

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::find_last_of(string_view_type sv, size_type pos) const noexcept { return sv().find_last_of(sv, pos); }


template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::find_last_of(const value_type* s, size_type pos, size_type n) const { return sv().find_last_of(s, pos, n); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::find_last_of(const value_type* s, size_type pos) const { return sv().find_last_of(s, pos); }


template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::find_last_of(value_type c, size_type pos) const noexcept { return sv().find_last_of(c, pos); }

/* ------------------------------------------------- Find-first-not-of algorithms ------------------------------------------------- */

template <typename CharType, std::size_t Size, typename TraitsType>
template <size_t M>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::find_first_not_of(const same_with_other_size<M>& str, size_type pos) const noexcept {
    if constexpr (M > Size)
        return npos;
    return sv().find_first_of(str.sv(), pos);
}

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::find_first_not_of(string_view_type sv, size_type pos) const noexcept { return sv().find_first_not_of(sv, pos); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::find_first_not_of(const value_type* s, size_type pos, size_type n) const { return sv().find_first_not_of(s, pos, n); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::find_first_not_of(const value_type* s, size_type pos) const { return sv().find_first_not_of(s, pos); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::find_first_not_of(value_type c, size_type pos) const noexcept { return sv().find_first_not_of(c, pos); }

/* -------------------------------------------------- Find-not-last-of algorithms ------------------------------------------------- */

template <typename CharType, std::size_t Size, typename TraitsType>
template <size_t M>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::find_last_not_of(const same_with_other_size<M>& str, size_type pos) const noexcept {
    if constexpr (M > Size)
        return npos;
    return sv().find_last_of(str.sv(), pos);
}

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::find_last_not_of(string_view_type sv, size_type pos) const noexcept { return sv().find_last_not_of(sv, pos); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::find_last_not_of(const value_type* s, size_type pos, size_type n) const { return sv().find_last_not_of(s, pos, n); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::find_last_not_of(const value_type* s, size_type pos) const { return sv().find_last_not_of(s, pos); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr basic_fixed_string<CharType, Size, TraitsType>::size_type
basic_fixed_string<CharType, Size, TraitsType>::find_last_not_of(value_type c, size_type pos) const noexcept { return sv().find_last_not_of(c, pos); }

/* ------------------------------------------------------ Compare algorithms ------------------------------------------------------ */

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr int 
basic_fixed_string<CharType, Size, TraitsType>::compare(string_view_type v) const noexcept { return sv().compare(v); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr int 
basic_fixed_string<CharType, Size, TraitsType>::compare(size_type pos1, size_type count1, string_view_type v) const { return sv().compare(pos1, count1, v); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr int 
basic_fixed_string<CharType, Size, TraitsType>::compare(size_type pos1, size_type count1, string_view_type v, size_type pos2, size_type count2) const { return sv().compare(pos1, count1, v, pos2, count2); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr int 
basic_fixed_string<CharType, Size, TraitsType>::compare(const value_type* s) const { return sv().compare(s); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr int 
basic_fixed_string<CharType, Size, TraitsType>::compare(size_type pos1, size_type count1, const value_type* s) const { return sv().compare(pos1, count1, s); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr int 
basic_fixed_string<CharType, Size, TraitsType>::compare(size_type pos1, size_type count1, const value_type* s, size_type count2) const { return sv().compare(pos1, count1, s, count2); }

/* ---------------------------------------------------- Starts-with algorithms ---------------------------------------------------- */

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr bool
basic_fixed_string<CharType, Size, TraitsType>::starts_with(string_view_type v) const noexcept { return sv().substr(0, v.size()) == v; }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr bool
basic_fixed_string<CharType, Size, TraitsType>::starts_with(char c) const noexcept { return !empty() && traits_type::eq(front(), c); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr bool
basic_fixed_string<CharType, Size, TraitsType>::starts_with(const value_type* s) const noexcept { return starts_with(string_view_type(s)); }

/* ----------------------------------------------------- Ends-with algorithms ----------------------------------------------------- */

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr bool
basic_fixed_string<CharType, Size, TraitsType>::ends_with(string_view_type sv) const noexcept { return size() >= sv.size() && compare(size() - sv.size(), npos, sv) == 0; }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr bool
basic_fixed_string<CharType, Size, TraitsType>::ends_with(value_type c) const noexcept { return !empty() && traits_type::eq(back(), c); }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr bool
basic_fixed_string<CharType, Size, TraitsType>::ends_with(const value_type* s) const { return ends_with(string_view_type(s)); }

/* ----------------------------------------------------- Contains algorithms ------------------------------------------------------ */

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr bool
basic_fixed_string<CharType, Size, TraitsType>::contains(string_view_type sv) const noexcept { return find(sv) != npos; }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr bool
basic_fixed_string<CharType, Size, TraitsType>::contains(value_type c) const noexcept { return find(c) != npos; }

template <typename CharType, std::size_t Size, typename TraitsType>
constexpr bool
basic_fixed_string<CharType, Size, TraitsType>::contains(const value_type* s) const { return find(s) != npos; }

/* ------------------------------------------------------- Swap algorithms -------------------------------------------------------- */

template <typename CharType, std::size_t Size, typename TraitsType>
void basic_fixed_string<CharType, Size, TraitsType>::swap(basic_fixed_string& other) noexcept(std::is_nothrow_swappable_v<storage_type>) { _data.swap(other._data); }

/* ============================================================== UDL ============================================================= */

namespace litarals {

    template <basic_fixed_string str>
    constexpr auto operator""_fs() noexcept {
        return str;
    }

} // End namespace litarals

/* ================================================================================================================================ */

} // End namespace estd

#endif
