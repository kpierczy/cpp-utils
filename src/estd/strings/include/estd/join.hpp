/** ==================================================================================================================================
 * @file     join.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Monday, 12th July 2021 9:25:13 am
 * @modified Thursday, 3rd February 2022 11:28:13 am
 * @project  Winder
 * @brief
 *    
 *    Header file of compile-time strings joiner
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __ESTD_JOIN_H__
#define __ESTD_JOIN_H__

/* =========================================================== Includes =========================================================== */

#include <array>
#include <string_view>

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ===================================================== Compiletime utilities ==================================================== */

/**
 * @brief Helper structure enabling compile-time concatenation of strings
 * @tparam Strs 
 *    strings to be concatenated
 */
template <std::string_view const&... Strs>
struct join {
private:

    /**
     * @brief Joins all strings into a single std::array of chars
     * @param strs 
     *    strings to be joined
     * @returns 
     *    concatenated string
     */
    static constexpr auto impl() noexcept;

    // Give the joined string static storage
    static constexpr auto arr = impl();
    
public:

    // View as a std::string_view
    static constexpr std::string_view value {arr.data(), arr.size() - 1};

};

// Helper to get the value out
template <std::string_view const&... Strs>
static constexpr auto join_v = join<Strs...>::value;

/* ================================================================================================================================ */

} // End namespace estd

/* ==================================================== Implementation includes =================================================== */

#include "estd/join/impl/join.hpp"

/* ================================================================================================================================ */

#endif
