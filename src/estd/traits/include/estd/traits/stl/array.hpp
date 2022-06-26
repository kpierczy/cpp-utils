/** ==================================================================================================================================
 * @file       arrays.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 3rd February 2022 10:48:23 am
 * @modified   Thursday, 3rd February 2022 6:57:58 pm
 * @project    cpp-utils
 * @brief      Set of type traits related to std::array
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * ================================================================================================================================ */

#ifndef __ESTD_TRAITS_STL_ARRAYS_H__
#define __ESTD_TRAITS_STL_ARRAYS_H__

/* =========================================================== Includes =========================================================== */

#include <array>
#include <type_traits>

/* ========================================================== Namespaces ========================================================== */

namespace estd {

/* ============================================================ Helpers =========================================================== */

namespace detail 
{    
    template <typename T>
    struct is_std_array : std::false_type {};

    template <class T, auto S> 
    struct is_std_array<std::array<T, S>> : std::true_type {};
}

/**
 * @brief Trait stating whether the typ @tparam T is a specialization of
 *    @ref std::array
 * @tparam T 
 *    type to be examined
 */
template <typename T> 
struct is_std_array : detail::is_std_array<T> { };

/// @brief Alias for @ref is_std_array<...>::value
template <class T> 
inline constexpr bool is_std_array_v = 
    is_std_array<T>::value;

/* ================================================================================================================================ */

} // End namespace estd

#endif
