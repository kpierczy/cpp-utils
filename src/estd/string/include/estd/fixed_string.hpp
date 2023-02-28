/* ============================================================================================================================ *//**
 * @file       fixed_string.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Monday, 12th July 2021 9:25:13 am
 * @modified   Tuesday, 28th February 2023 8:18:12 pm
 * @project    cpp-utils
 * @brief      Header file of compile-time strings literal
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * @source https://github.com/unterumarmung/fixed_string
 */// ============================================================================================================================= */

#ifndef __ESTD_FIXED_STRING_H__
#define __ESTD_FIXED_STRING_H__

/* =========================================================== Includes =========================================================== */

#include <array>
#include <functional>
#include <iterator>
#include <ostream>
#include <string_view>
#include <type_traits>
#include "estd/fixed_string/impl/fixed_string_details.hpp"

/* ======================================================= Compiler version ======================================================= */

// Compiler version
#ifdef _MSC_VER
#define FIXSTR_CPP_VERSION _MSVC_LANG
#else
#define FIXSTR_CPP_VERSION __cplusplus
#endif
// GCC version (note that when ICC or Clang is in use, FIXSTR_GCC_VERSION might not fully match the actual GCC version on the system)
#ifdef __GNUC__
#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif
// Clang version
#ifdef __clang__
#define CLANG_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#endif

/* ======================================================== Compiler traits ======================================================= */

// If GCC used, chekc if NTTP is available
#ifdef __GNUC__
#if GCC_VERSION >= 10'00'00 && CPP_VERSION > 2017'03L
#define CPP20_CNTTP_PRESENT 1
#elif __cpp_nontype_template_args >= 2019'11
#define CPP20_CNTTP_PRESENT 1
#elif __cpp_nontype_template_parameter_class >= 2018'06
#define CPP20_CNTTP_PRESENT 1
#else
#define CPP20_CNTTP_PRESENT 0
#endif
// Otgerwise check NTTP unused
#else
#define CPP20_CNTTP_PRESENT 0
#endif

// Language traits
#define CPP20_CHAR8T_PRESENT               __cpp_char8_t
#define CPP20_SPACESHIP_OPERATOR_PRESENT   __cpp_lib_three_way_comparison
#define CPP20_CONSTEXPR_ALGORITHMS_PRESENT __cpp_lib_constexpr_algorithms

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ====================================================== Basic fixed string ====================================================== */

/**
 * @brief Implementation of the compile-time, structural-type string type
 * @tparam CharType 
 *    type of the signel character
 * @tparam Size
 *     size of the string (without trailing '0')
 * @tparam TraitsType 
 *     traits of the string type
 */
template <typename CharType, std::size_t Size, typename TraitsType = std::char_traits<CharType>>
struct basic_fixed_string {

    // Content of the string
    std::array<CharType, Size + 1> _data{};

public: /* ----------------------------------------------------- Public types ----------------------------------------------------- */

    // Storage type (std::array)
    using storage_type = decltype(_data);
    // Standard set of STL traits
    using traits_type = TraitsType;
    using value_type = CharType;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = typename storage_type::iterator;
    using const_iterator = typename storage_type::const_iterator;
    using reverse_iterator = typename storage_type::reverse_iterator;
    using const_reverse_iterator = typename storage_type::const_reverse_iterator;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    // Specialization of the std::basic_string_view corresponding to the type
    using string_view_type = std::basic_string_view<value_type, traits_type>;

public: /* --------------------------------------------------- Public constants --------------------------------------------------- */

    // Number of string's positions
    static constexpr auto npos = string_view_type::npos;

private: /* ------------------------------------------------- Private algorithms -------------------------------------------------- */

    /// @brief Helper alias for the same-size fixed-string type
    template <size_t M>
    using same_with_other_size = basic_fixed_string<value_type, M, traits_type>;

    /// @brief Helper meta-function calculating size of the substring
    template <size_type pos, size_type count, size_type size>
    constexpr static size_type calculate_substr_size() {

        // If initial position is larger than size, return 0
        if constexpr (pos >= size)
            return 0;

        // Otherwise, calculate size
        return std::min(count, size - pos);
    }

    /// @brief Helper alias for the type of string's substring
    template <size_type pos, size_type count>
    using substr_result_type = same_with_other_size<calculate_substr_size<pos, count, Size>()>;

private: /* --------------------------------------------------- Private methods --------------------------------------------------- */

    /// @brief Convertes string to the std::basic_string_view
    constexpr string_view_type sv() const;

public: /* ------------------------------------------------- Public constructors -------------------------------------------------- */

    /**
     * @brief Default constructor (empty string)
     */
    constexpr basic_fixed_string() noexcept = default;

    /**
     * @brief Constructs string from the array of characters
     * @param array
     *    source array of characters
     */
    constexpr explicit(false) basic_fixed_string(const value_type (&array)[Size + 1]) noexcept;

    /**
     * @brief Default copy constructpr
     */
    constexpr basic_fixed_string(const basic_fixed_string &other) noexcept = default;

public: /* --------------------------------------------------- Public iterators ----------------------------------------------------- */

    /// @brief Returns iterator to the first element of the string
    [[nodiscard]] constexpr iterator begin() noexcept;
    /// @brief Returns iterator to the first element of the const string
    [[nodiscard]] constexpr const_iterator begin() const noexcept;
    /// @brief Returns iterator to the last element of the string
    [[nodiscard]] constexpr iterator end() noexcept;
    /// @brief Returns iterator to the last element of the const string
    [[nodiscard]] constexpr const_iterator end() const noexcept;

    /// @brief Returns const iterator to the first element of the string
    [[nodiscard]] constexpr const_iterator cbegin() const noexcept;
    /// @brief Returns const iterator to the last element of the string
    [[nodiscard]] constexpr const_iterator cend() const noexcept;

    /// @brief Returns reversed iterator to the first element of the string
    [[nodiscard]] constexpr reverse_iterator rbegin() noexcept;
    /// @brief Returns reversed iterator to the first element of the const string
    [[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept;
    /// @brief Returns reversed iterator to the last element of the string
    [[nodiscard]] constexpr reverse_iterator rend() noexcept;
    /// @brief Returns reversed iterator to the last element of the const string
    [[nodiscard]] constexpr const_reverse_iterator rend() const noexcept;

    /// @brief Returns reversed const iterator to the first element of the string
    [[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept;
    /// @brief Returns reversed const iterator to the last element of the string
    [[nodiscard]] constexpr const_reverse_iterator crend() const noexcept;

public: /* --------------------------------------------------- Public operators --------------------------------------------------- */

    /**
     * @brief Assignment operator
     * @param array
     *    array of characters to be copied
     * @returns 
     *     reference to *this
     */
    constexpr basic_fixed_string& operator=(const value_type (&array)[Size + 1]) noexcept;

    /**
     * @brief Default assignment operator
     */
    constexpr basic_fixed_string& operator=(const basic_fixed_string& other) noexcept = default;
    
    /**
     * @brief Acesses n'th element of the string
     * @param n 
     *    index of the element fo be accessed
     * @returns 
     *    reference to the element
     */
    [[nodiscard]] constexpr reference operator[](size_type n);
    
    /**
     * @brief Acesses n'th element of the const string
     * @param n 
     *    index of the element fo be accessed
     * @returns 
     *    reference to the const element
     */
    [[nodiscard]] constexpr const_reference operator[](size_type n) const;

    /**
     * @brief Converts string to the std::basic_string_view
     */
    [[nodiscard]] constexpr operator string_view_type() const noexcept;
    
public: /* --------------------------------------------------- Public methods ----------------------------------------------------- */

    /**
     * @returns 
     *    size of the string (without trailing '0')
     */
    [[nodiscard]] constexpr size_type size() const noexcept;

    /**
     * @returns 
     *    size of the string (without trailing '0')
     */
    [[nodiscard]] constexpr size_type length() const noexcept;

    /**
     * @returns 
     *    size of the string (without trailing '0')
     */
    [[nodiscard]] constexpr size_type max_size() const noexcept;

    /**
     * @returns 
     *    @c true if size of the string (without trailing '0') is @c 0
     */
    [[nodiscard]] constexpr bool empty() const noexcept;

    /**
     * @brief Accesses n'th element of the string
     * @param n
     *    index of the element to be accessed
     * @returns 
     *    reference to the accesed element
     */
    [[nodiscard]] constexpr reference at(size_type n);

    /**
     * @brief Accesses n'th element of the const string
     * @param n
     *    index of the element to be accessed
     * @returns 
     *    const reference to the accesed element
     */
    [[nodiscard]] constexpr const_reference at(size_type n) const;

    /**
     * @brief Accesses first element of the string
     * @returns 
     *    const reference to the first element
     */
    [[nodiscard]] constexpr reference front() noexcept requires (Size != 0);

    /**
     * @brief Accesses first element of the const string
     * @returns 
     *    const reference to the first element
     */
    [[nodiscard]] constexpr const_reference front() const noexcept requires (Size != 0);

    /**
     * @brief Accesses last element of the string
     * @returns 
     *    const reference to the last element
     */
    [[nodiscard]] constexpr reference back() noexcept requires (Size != 0);

    /**
     * @brief Accesses last element of the const string
     * @returns 
     *    const reference to the last element
     */
    [[nodiscard]] constexpr const_reference back() const noexcept requires (Size != 0);

    /**
     * @brief Accesses first element of the string
     * @returns 
     *    pointer to the first element
     */
    [[nodiscard]] constexpr pointer data() noexcept;

    /**
     * @brief Accesses first element of the const string
     * @returns 
     *    const pointer to the first element
     */
    [[nodiscard]] constexpr const_pointer data() const noexcept;

    /**
     * @brief Converts string to C-style string
     * @returns 
     *    const pointer to the first element
     */
    [[nodiscard]] constexpr const_pointer c_str() const noexcept;

public: /* -------------------------------------------------- Public algorithms --------------------------------------------------- */

    /**
     * @brief Transforms substring of the string into the fixed-string
     * 
     * @param pos 
     *    position of the first element of the substring
     * @param count 
     *    length of the substring
     * 
     * @todo Move definiiton to the impl/ file
     */
    template <size_type pos = 0, size_type count = npos>
        requires (pos <= Size)
    [[nodiscard]] constexpr auto substr() const noexcept 
        -> substr_result_type<pos, count>
    {
        substr_result_type<pos, count> result;
        details::copy(begin() + pos, begin() + pos + result.size(), result.begin());
        return result;
    }

    /**
     * @brief Finds @p str substring in the string
     * @param str 
     *    substring to be found
     * @param pos
     *    position to start search from
     */
    template <size_t M>
    [[nodiscard]] constexpr size_type find(const same_with_other_size<M>& str, size_type pos = 0) const noexcept;

    /**
     * @brief Finds @p sv substring in the string
     * @param sv 
     *    substring to be found
     * @param pos
     *    position to start search from
     */
    [[nodiscard]] constexpr size_type find(string_view_type sv, size_type pos = 0) const noexcept;

    /**
     * @brief Finds @p s substring in the string
     * @param s 
     *    substring to be found
     * @param pos
     *    position to start search from
     * @param n
     *    maximal number of positions to be searched
     */
    [[nodiscard]] constexpr size_type find(const value_type* s, size_type pos, size_type n) const;

    /**
     * @brief Finds @p s substring in the string
     * @param s 
     *    substring to be found
     * @param pos
     *    position to start search from
     */
    [[nodiscard]] constexpr size_type find(const value_type* s, size_type pos = 0) const;

    /**
     * @brief Finds @p c character in the string
     * @param c 
     *    character to be found
     * @param pos
     *    position to start search from
     */
    [[nodiscard]] constexpr size_type find(value_type c, size_type pos = 0) const noexcept;

    /**
     * @brief Finds @p str substring in the string traversing string in the reversed order
     * @param str 
     *    substring to be found
     * @param pos
     *    position to start search from
     */
    template <size_t M>
    [[nodiscard]] constexpr size_type rfind(const same_with_other_size<M>& str, size_type pos = npos) const noexcept;

    /**
     * @brief Finds @p sv substring in the string traversing string in the reversed order
     * @param sv 
     *    substring to be found
     * @param pos
     *    position to start search from
     */

    [[nodiscard]] constexpr size_type rfind(string_view_type sv, size_type pos = npos) const noexcept;
    
    /**
     * @brief Finds @p s substring in the string traversing string in the reversed order
     * @param s 
     *    substring to be found
     * @param pos
     *    position to start search from
     * @param n
     *    maximal number of positions to be searched
     */

    [[nodiscard]] constexpr size_type rfind(const value_type* s, size_type pos, size_type n) const;
    
    /**
     * @brief Finds @p s substring in the string traversing string in the reversed order
     * @param s 
     *    substring to be found
     * @param pos
     *    position to start search from
     */

    [[nodiscard]] constexpr size_type rfind(const value_type* s, size_type pos = npos) const;
    
    /**
     * @brief Finds @p c character in the string traversing string in the reversed order
     * @param c 
     *    character to be found
     * @param pos
     *    position to start search from
     */

    [[nodiscard]] constexpr size_type rfind(value_type c, size_type pos = npos) const noexcept;

    /**
     * @brief Searches the string for the first character that matches any of the characters specified in its arguments
     * @param str 
     *    list of characters to search for
     * @param pos
     *    position to start search from
     */
    template <size_t M>
    [[nodiscard]] constexpr size_type find_first_of(const same_with_other_size<M>& str, size_type pos = 0) const noexcept;

    /**
     * @brief Searches the string for the first character that matches any of the characters specified in its arguments
     * @tparam s 
     *    list of characters to search for
     * @tparam pos
     *    position to start search from
     */
    [[nodiscard]] constexpr size_type find_first_of(string_view_type sv, size_type pos = 0) const noexcept;
    
    /**
     * @brief Searches the string for the first character that matches any of the characters specified in its arguments
     * @param s 
     *    list of characters to search for
     * @param pos
     *    position to start search from
     * @param n
     *    maximal number of elements to be searched
     */
    [[nodiscard]] constexpr size_type find_first_of(const value_type* s, size_type pos, size_type n) const;
    
    /**
     * @brief Searches the string for the first character that matches any of the characters specified in its arguments
     * @param s 
     *    list of characters to search for
     * @param pos
     *    position to start search from
     */
    [[nodiscard]] constexpr size_type find_first_of(const value_type* s, size_type pos = 0) const;
    
    /**
     * @brief Searches the string for the first character that matches any of the characters specified in its arguments
     * @param str 
     *    character to search for
     * @param pos
     *    position to start search from
     */
    [[nodiscard]] constexpr size_type find_first_of(value_type c, size_type pos = 0) const noexcept;

    /**
     * @brief Searches the string for the last character that matches any of the characters specified in its arguments
     * @param str 
     *    list of characters to search for
     * @param pos
     *    position to start search from
     */
    template <size_t M>
    [[nodiscard]] constexpr size_type find_last_of(const same_with_other_size<M>& str, size_type pos = npos) const noexcept;

    /**
     * @brief Searches the string for the last character that matches any of the characters specified in its arguments
     * @param s 
     *    list of characters to search for
     * @param pos
     *    position to start search from
     */
    [[nodiscard]] constexpr size_type find_last_of(string_view_type sv, size_type pos = npos) const noexcept;

    /**
     * @brief Searches the string for the last character that matches any of the characters specified in its arguments
     * @param s 
     *    list of characters to search for
     * @param pos
     *    position to start search from
     * @param n
     *    maximal number of elements to be searched
     */
    [[nodiscard]] constexpr size_type find_last_of(const value_type* s, size_type pos, size_type n) const;

    /**
     * @brief Searches the string for the last character that matches any of the characters specified in its arguments
     * @param s 
     *    list of characters to search for
     * @param pos
     *    position to start search from
     */
    [[nodiscard]] constexpr size_type find_last_of(const value_type* s, size_type pos = npos) const;

    /**
     * @brief Searches the string for the last character that matches any of the characters specified in its arguments
     * @param str 
     *    character to search for
     * @param pos
     *    position to start search from
     */
    [[nodiscard]] constexpr size_type find_last_of(value_type c, size_type pos = npos) const noexcept;

    /**
     * @brief Searches the string for the first character that does NOT match any of the characters specified in its arguments
     * @param str 
     *    list of characters to search for
     * @param pos
     *    position to start search from
     */
    template <size_t M>
    [[nodiscard]] constexpr size_type find_first_not_of(const same_with_other_size<M>& str, size_type pos = 0) const noexcept;

    /**
     * @brief Searches the string for the first character that does NOT match any of the characters specified in its arguments
     * @param s 
     *    list of characters to search for
     * @param pos
     *    position to start search from
     */
    [[nodiscard]] constexpr size_type find_first_not_of(string_view_type sv, size_type pos = 0) const noexcept;

    /**
     * @brief Searches the string for the first character that does NOT match any of the characters specified in its arguments
     * @param s 
     *    list of characters to search for
     * @param pos
     *    position to start search from
     * @param n
     *    maximal number of elements to be searched
     */
    [[nodiscard]] constexpr size_type find_first_not_of(const value_type* s, size_type pos, size_type n) const;

    /**
     * @brief Searches the string for the first character that does NOT match any of the characters specified in its arguments
     * @param s 
     *    list of characters to search for
     * @param pos
     *    position to start search from
     */
    [[nodiscard]] constexpr size_type find_first_not_of(const value_type* s, size_type pos = 0) const;

    /**
     * @brief Searches the string for the first character that does NOT match any of the characters specified in its arguments
     * @param str 
     *    character to search for
     * @param pos
     *    position to start search from
     */
    [[nodiscard]] constexpr size_type find_first_not_of(value_type c, size_type pos = 0) const noexcept;

    /**
     * @brief Searches the string for the last character that does NOT match any of the characters specified in its arguments
     * @param str 
     *    list of characters to search for
     * @param pos
     *    position to start search from
     */
    template <size_t M>
    [[nodiscard]] constexpr size_type find_last_not_of(const same_with_other_size<M>& str, size_type pos = npos) const noexcept;

    /**
     * @brief Searches the string for the last character that does NOT match any of the characters specified in its arguments
     * @param s 
     *    list of characters to search for
     * @param pos
     *    position to start search from
     */
    [[nodiscard]] constexpr size_type find_last_not_of(string_view_type sv, size_type pos = npos) const noexcept;

    /**
     * @brief Searches the string for the last character that does NOT match any of the characters specified in its arguments
     * @param s 
     *    list of characters to search for
     * @param pos
     *    position to start search from
     * @param n
     *    maximal number of elements to be searched
     */
    [[nodiscard]] constexpr size_type find_last_not_of(const value_type* s, size_type pos, size_type n) const;

    /**
     * @brief Searches the string for the last character that does NOT match any of the characters specified in its arguments
     * @param s 
     *    list of characters to search for
     * @param pos
     *    position to start search from
     */
    [[nodiscard]] constexpr size_type find_last_not_of(const value_type* s, size_type pos = npos) const;

    /**
     * @brief Searches the string for the last character that does NOT match any of the characters specified in its arguments
     * @param str 
     *    character to search for
     * @param pos
     *    position to start search from
     */
    [[nodiscard]] constexpr size_type find_last_not_of(value_type c, size_type pos = npos) const noexcept;

    /**
     * @brief Compares @ref *this with the @p v string
     * @param v
     *    string to be compared with
     * @returns 
     *    @retval @c 0 if compared strings are equal
     *    @retval @c <0 if either the value of the first character that does not match is lower in the compared
     *       string, or all compared characters match but the compared string is shorter
     *    @retval @c >0 if either the value of the first character that does not match is greater in the compared
     *       string, or all compared characters match but the compared string is longer
     */
    [[nodiscard]] constexpr int compare(string_view_type v) const noexcept;

    /**
     * @brief Compares @ref *this with the @p v string
     * @param pos1
     *    position of the first character in the *this string
     * @param count1
     *    length of compared string
     * @param v
     *    string to be compared with
     * @returns 
     *    @retval @c 0 if compared strings are equal
     *    @retval @c <0 if either the value of the first character that does not match is lower in the compared
     *       string, or all compared characters match but the compared string is shorter
     *    @retval @c >0 if either the value of the first character that does not match is greater in the compared
     *       string, or all compared characters match but the compared string is longer
     */
    [[nodiscard]] constexpr int compare(size_type pos1, size_type count1, string_view_type v) const;

    /**
     * @brief Compares @ref *this with the @p v string
     * @param pos1
     *    position of the first character in the *this string
     * @param count1
     *    length of compared string
     * @param v
     *    string to be compared with
     * @param pos1
     *    position of the first character in the @p v string
     * @param count1
     *    length of compared @p v string
     * @returns 
     *    @retval @c 0 if compared strings are equal
     *    @retval @c <0 if either the value of the first character that does not match is lower in the compared
     *       string, or all compared characters match but the compared string is shorter
     *    @retval @c >0 if either the value of the first character that does not match is greater in the compared
     *       string, or all compared characters match but the compared string is longer
     */
    [[nodiscard]] constexpr int compare(size_type pos1, size_type count1, string_view_type v, size_type pos2, size_type count2) const;
    
    /**
     * @brief Compares @ref *this with the @p v string
     * @param v
     *    string to be compared with
     * @returns 
     *    @retval @c 0 if compared strings are equal
     *    @retval @c <0 if either the value of the first character that does not match is lower in the compared
     *       string, or all compared characters match but the compared string is shorter
     *    @retval @c >0 if either the value of the first character that does not match is greater in the compared
     *       string, or all compared characters match but the compared string is longer
     */
    [[nodiscard]] constexpr int compare(const value_type* s) const;

    /**
     * @brief Compares @ref *this with the @p v string
     * @param pos1
     *    position of the first character in the *this string
     * @param count1
     *    length of compared string
     * @param v
     *    string to be compared with
     * @returns 
     *    @retval @c 0 if compared strings are equal
     *    @retval @c <0 if either the value of the first character that does not match is lower in the compared
     *       string, or all compared characters match but the compared string is shorter
     *    @retval @c >0 if either the value of the first character that does not match is greater in the compared
     *       string, or all compared characters match but the compared string is longer
     */
    [[nodiscard]] constexpr int compare(size_type pos1, size_type count1, const value_type* s) const;

    /**
     * @brief Compares @ref *this with the @p v string
     * @param pos1
     *    position of the first character in the *this string
     * @param count1
     *    length of compared string
     * @param v
     *    string to be compared with
     * @param pos1
     *    position of the first character in the @p v string
     * @param count1
     *    length of compared @p v string
     * @returns 
     *    @retval @c 0 if compared strings are equal
     *    @retval @c <0 if either the value of the first character that does not match is lower in the compared
     *       string, or all compared characters match but the compared string is shorter
     *    @retval @c >0 if either the value of the first character that does not match is greater in the compared
     *       string, or all compared characters match but the compared string is longer
     */
    [[nodiscard]] constexpr int compare(size_type pos1, size_type count1, const value_type* s, size_type count2) const;

    /**
     * @param v 
     *    substring to be found
     * @returns 
     *    @retval @c true if string starts with @p v
     *    @retval @c false otherwise
     */
    [[nodiscard]] constexpr bool starts_with(string_view_type v) const noexcept;

    /**
     * @param c 
     *    character to be found
     * @returns 
     *    @retval @c true if string starts with @p c
     *    @retval @c false otherwise
     */
    [[nodiscard]] constexpr bool starts_with(char c) const noexcept;

    /**
     * @param v 
     *    substring to be found
     * @returns 
     *    @retval @c true if string starts with @p v
     *    @retval @c false otherwise
     */
    [[nodiscard]] constexpr bool starts_with(const value_type* s) const noexcept;

    /**
     * @param v 
     *    substring to be found
     * @returns 
     *    @retval @c true if string ends with @p v
     *    @retval @c false otherwise
     */    
    [[nodiscard]] constexpr bool ends_with(string_view_type sv) const noexcept;

    /**
     * @param c 
     *    character to be found
     * @returns 
     *    @retval @c true if string ends with @p c
     *    @retval @c false otherwise
     */    
    [[nodiscard]] constexpr bool ends_with(value_type c) const noexcept;

    /**
     * @param v 
     *    substring to be found
     * @returns 
     *    @retval @c true if string ends with @p v
     *    @retval @c false otherwise
     */    
    [[nodiscard]] constexpr bool ends_with(const value_type* s) const;

    /**
     * @param v 
     *    substring to be found
     * @returns 
     *    @retval @c true if string contains @p v
     *    @retval @c false otherwise
     */ 
    [[nodiscard]] constexpr bool contains(string_view_type sv) const noexcept;

    /**
     * @param c 
     *    character to be found
     * @returns 
     *    @retval @c true if string contains @p c
     *    @retval @c false otherwise
     */ 
    [[nodiscard]] constexpr bool contains(value_type c) const noexcept;

    /**
     * @param v 
     *    substring to be found
     * @returns 
     *    @retval @c true if string contains @p v
     *    @retval @c false otherwise
     */    
    [[nodiscard]] constexpr bool contains(const value_type* s) const;

    /**
     * @brief Swaps content of strings
     * @param other 
     *    strings to be swapped with
     */
    void swap(basic_fixed_string& other) noexcept(std::is_nothrow_swappable_v<storage_type>);

};

/**
 * @brief CDAT for the basic_fixed_string
 */
template <typename CharType, size_t Size>
basic_fixed_string(const CharType (&)[Size]) -> basic_fixed_string<CharType, Size - 1>;

/* ============================================================== UDL ============================================================= */

namespace litarals {

    /**
     * @brief UDL creating fixed string from string literal
     * @tparam str
     *    source string
     * @returns 
     *    fixed string containing @param str
     */
    template <basic_fixed_string str>
    constexpr auto operator""_fs() noexcept;

} // End namespace litarals

/* ========================================================= Fixed string ========================================================= */

#ifdef __GNUC__ 
#if (GCC_VERSION < 12'00'00)
#warning                                                                                            \
    "Early GCC versions (probably < 12) that support NTTP were not able to deduce size_t parameter" \
    "of basic_fixed_string when fixed_string and other typedef were just type aliases"
#endif
#endif

/**
 * @brief Alias of the basic_fixed string for @ref char
 */
template <size_t Size>
using fixed_string = basic_fixed_string<char, Size>;

/* ======================================================== Fixed U8 string ======================================================= */

#if CPP20_CHAR8T_PRESENT
    
/**
 * @brief Alias of the basic_fixed string for @ref char8_t
 */
template <size_t Size>
using fixed_u8string = basic_fixed_string<char8_t, Size>;

#endif

/* ======================================================= Fixed U16 string ======================================================= */

/**
 * @brief Alias of the basic_fixed string for @ref char16_t
 */
template <size_t Size>
using fixed_u16string = basic_fixed_string<char16_t, Size>;

/* ======================================================= Fixed U32 string ======================================================= */

/**
 * @brief Alias of the basic_fixed string for @ref char32_t
 */
template <size_t Size>
using fixed_u32string = basic_fixed_string<char32_t, Size>;

/* ========================================================= Fixed wstring ======================================================== */

/**
 * @brief Alias of the basic_fixed string for @ref wchar_t
 */
template <size_t Size>
using fixed_wstring = basic_fixed_string<wchar_t, Size>;

/* ================================================================================================================================ */

} // End namespace estd

/* ==================================================== Implementation includes =================================================== */

#include "estd/fixed_string/impl/fixed_string.hpp"
#include "estd/fixed_string/fixed_string_functions.hpp"

/* ================================================================================================================================ */

#endif
