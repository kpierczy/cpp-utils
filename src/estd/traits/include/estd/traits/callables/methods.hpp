/* ============================================================================================================================ *//**
 * @file       methods.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 3rd February 2022 10:48:23 am
 * @modified   Wednesday, 19th October 2022 9:56:13 pm
 * @project    cpp-utils
 * @brief      Set of type traits related to methods
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_TRAITS_CALLABLE_METHODS_H__
#define __ESTD_TRAITS_CALLABLE_METHODS_H__

/* =========================================================== Includes =========================================================== */

#include <type_traits>

/* ========================================================== Namespaces ========================================================== */

namespace estd {
    
/* ============================================================ Methods =========================================================== */

namespace details
{
    template<typename T>
    struct is_method : std::false_type { };

    // Specialization for non-const methods
    template<typename T, typename Return, typename... Args>
    struct is_method<Return (T::*)(Args...)> : std::true_type {
        using class_type = T;
    };

    // Specialization for const methods
    template<typename T, typename Return, typename... Args>
    struct is_method<Return (T::*)(Args...) const> : std::true_type {
        using class_type = T;
    };
}

/**
 * @brief Trait checking whether given the type is class'es method
 * @tparam T
 *    type to be checked
 * @a class_type
 *    type of the class (defined only if the @tparam T is a method type)
 */
template<typename T>
struct is_method : 
    details::is_method<T> { };

/**
 * @brief Trait testing whether class defines a particular method
 * @tparam T 
 *    tested class
 * @tparam Method 
 *    tested method
 */
template<typename T, typename Method>
struct has_method {
    static constexpr bool value = is_method<Method>::value && std::same_as<T, typename is_method<Method>::class_type>;
};
    
/// @brief Alias for @ref has_method<T, Method>::value
template<typename T, typename Method>
constexpr bool has_method_v = has_method<T, Method>::value;

namespace details {

    // Auxiliary deduction guide returning object of type of the class that the argument method pointer is from
    template<typename R, typename C, typename... Args>
    C function_pointer_class_guide(R (C::*)(Args...));

    // Implementation of the trait
    template<typename Method>
        requires (std::is_member_function_pointer_v<Method>)
    struct method_class {
        using type = decltype(function_pointer_class_guide(std::declval<Method>()));
    };

}

/**
 * @brief Trait deducing type of the class that the given @p Method is defined in
 * 
 * @tparam Method 
 *    tested method
 */
template<typename Method>
struct method_class :
    public details::method_class<Method>
{ };
    
/// @brief Alias for @ref method_class<Method>::type
template<typename Method>
using method_class_t = typename method_class<Method>::type;

/* ================================================================================================================================ */

} // End namespace estd

#endif
