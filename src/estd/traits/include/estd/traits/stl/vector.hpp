/* ============================================================================================================================ *//**
 * @file       vector.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 3rd February 2022 10:48:23 am
 * @modified   Wednesday, 19th October 2022 9:57:37 pm
 * @project    cpp-utils
 * @brief      Set of type traits related to std::vector
 *    
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_TRAITS_STL_VECTOR_H__
#define __ESTD_TRAITS_STL_VECTOR_H__

/* =========================================================== Includes =========================================================== */

#include <vector>
#include <type_traits>

/* ========================================================== Namespaces ========================================================== */

namespace estd {

/* ============================================================ Helpers =========================================================== */

namespace detail 
{    
    template <typename T>
    struct is_std_vector : std::false_type {};

    template <class T> 
    struct is_std_vector<std::vector<T>> : std::true_type {};
}

/**
 * @brief Trait stating whether the typ @tparam T is a specialization of
 *    @ref std::vector
 * @tparam T 
 *    type to be examined
 */
template <typename T> 
struct is_std_vector : detail::is_std_vector<T> { };

/// @brief Alias for @ref is_std_vector<...>::value
template <class T> 
inline constexpr bool is_std_vector_v = 
    is_std_vector<T>::value;

/* ================================================================================================================================ */

} // End namespace estd

#endif
