/* ============================================================================================================================ *//**
 * @file       arrays.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Wednesday, 1st March 2023 4:09:16 am
 * @modified   Wednesday, 1st March 2023 4:11:28 am
 * @project    cpp-utils
 * @brief      Set of type traits related to std::tuple
 *    
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_TRAITS_STL_TUPLE_H__
#define __ESTD_TRAITS_STL_TUPLE_H__

/* =========================================================== Includes =========================================================== */

#include <tuple>
#include <type_traits>

/* ========================================================== Namespaces ========================================================== */

namespace estd {

/* ============================================================ Helpers =========================================================== */

namespace detail 
{    
    template <typename T>
    struct is_tuple :
        std::false_type
    { };

    template <typename... T> 
    struct is_tuple<std::tuple<T...>> :
        std::true_type
    { };
}

/**
 * @brief Trait stating whether the typ @tparam T is a specialization of
 *    @ref std::array
 * @tparam T 
 *    type to be examined
 */
template <typename T> 
struct is_tuple : 
    detail::is_tuple<T>
{ };

/// @brief Alias for @ref is_tuple<...>::value
template <class T> 
inline constexpr bool is_tuple_v = is_tuple<T>::value;

/* ================================================================================================================================ */

} // End namespace estd

#endif
