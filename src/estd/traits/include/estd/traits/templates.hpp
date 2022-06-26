/** ==================================================================================================================================
 * @file       templates.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 3rd February 2022 10:48:23 am
 * @modified   Thursday, 3rd February 2022 6:57:58 pm
 * @project    cpp-utils
 * @brief      Set of type traits related to templates
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * ================================================================================================================================ */

#ifndef __ESTD_TRAITS_TEMPLATES_H__
#define __ESTD_TRAITS_TEMPLATES_H__

/* =========================================================== Includes =========================================================== */

#include <type_traits>

/* ========================================================== Namespaces ========================================================== */

namespace estd {

/* =========================================================== Templates ========================================================== */

namespace details 
{
    template <typename T, template <typename...> typename Template>
    struct is_specialization_of : std::false_type {};
    
    template <template <typename...> typename Template, typename... Args>
    struct is_specialization_of<Template<Args...>, Template> : std::true_type {};
}

/**
 * @brief Trait checking whether the type is a specialization a class template
 * @tparam T 
 *    class to be verified
 * @tparam Template 
 *    template to be compared against
 */
template <typename T, template <typename...> typename Template>
struct is_specialization_of : 
    details::is_specialization_of<std::remove_cvref_t<T>, Template> {};

/// @brief Alias for @ref is_specialization_of<...>::value
template <typename T, template <typename...> typename Template>
inline constexpr bool is_specialization_of_v = 
    is_specialization_of<T, Template>::value;

/* ================================================================================================================================ */

} // End namespace estd

#endif
