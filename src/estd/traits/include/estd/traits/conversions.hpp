/* ============================================================================================================================ *//**
 * @file       conversions.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 3rd February 2022 10:48:23 am
 * @modified   Wednesday, 19th October 2022 9:57:37 pm
 * @project    cpp-utils
 * @brief      Set of type traits related to types conversions
 *    
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_TRAITS_CONVERSIONS_H__
#define __ESTD_TRAITS_CONVERSIONS_H__

/* =========================================================== Includes =========================================================== */

#include <type_traits>

/* ========================================================== Namespaces ========================================================== */

namespace estd {

/* ======================================================= Types-conversions ====================================================== */

/**
 * @brief Macro checking whether @tparam From is explicitly converible to @tparam To
 */
template <class From, class To>
struct is_explicitly_convertible {
    static constexpr bool value = std::is_constructible<To, From>::value && !std::is_convertible<From, To>::value;
};

/// @brief Alias for @ref is_explicitly_convertible<From, To>::value
template <class From, class To>
constexpr bool is_explicitly_convertible_v = 
    is_explicitly_convertible<From, To>::value;

namespace details
{
    template<typename From, typename To, typename = void>
    struct is_narrowing_conversion_impl : std::true_type {};

    template<typename From, typename To>
    struct is_narrowing_conversion_impl<From, To, std::void_t<decltype(To{std::declval<From>()})>> : 
        std::false_type {};
} 

/**
 * @brief Trait describing whether conversion from @p From type to the 
 *    @p To type narrows representation
 * @tparam From 
 *    source type of the conversion
 * @tparam To 
 *    destination type of the conversion
 */
template<typename From, typename To>
struct is_narrowing_conversion : 
    details::is_narrowing_conversion_impl<From, To> {};

/* ================================================================================================================================ */

} // End namespace estd

#endif
