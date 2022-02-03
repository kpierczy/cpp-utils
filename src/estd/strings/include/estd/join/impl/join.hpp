/** ==================================================================================================================================
 * @file     join.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Monday, 12th July 2021 9:29:30 am
 * @modified Thursday, 3rd February 2022 11:28:53 am
 * @project  Winder
 * @brief
 *    
 *    Implementation of inline methods and methods templates of the compile-time helpers module
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __ESTD_JOIN_IMPL_JOIN_H__
#define __ESTD_JOIN_IMPL_JOIN_H__

/* =========================================================== Includes =========================================================== */

#include "estd/join.hpp"

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ========================================================== Namespaces ========================================================== */

template <std::string_view const&... Strs>
constexpr auto join<Strs...>::impl() noexcept {

    // Calculate length of the resulting string
    constexpr std::size_t len = (Strs.size() + ... + 0);

    // Prepare array containing the string
    std::array<char, len + 1> arr{};
    // Prepare string's constructor
    auto append = [i = 0, &arr](auto const& s) mutable {
        for (auto c : s)
            arr[i++] = c;
    };

    // Construct the string
    (append(Strs), ...);
    // Close the string with trailing '0'
    arr[len] = 0;
    
    return arr;
}

/* ================================================================================================================================ */

} // End namespace estd

#endif
