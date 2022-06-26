/** ==================================================================================================================================
 * @file       traits.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 3rd February 2022 10:48:23 am
 * @modified   Thursday, 3rd February 2022 6:57:58 pm
 * @project    cpp-utils
 * @brief      Set of commonly used type traits
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * ================================================================================================================================ */

#ifndef __ESTD_TRAITS_H__
#define __ESTD_TRAITS_H__

/* =========================================================== Includes =========================================================== */

#include <tuple>
#include <type_traits>

/* ========================================================== Namespaces ========================================================== */

namespace estd {

/* ============================================================ Helpers =========================================================== */

/**
 * @brief Trait used to trigger compilation error when compiler reaches 'else' clause
 *    of the 'if constexpr' expression
 * @tparam T 
 *    an arbitrary type that the tempalte using this trait is dependent on
 * 
 * @example
 * 
 *    template<typename Type>
 *    Type fun() {
 * 
 *        if constexpr(...)
 *            ...
 *        else if constexpr(...)
 *            ...
 *        else
 *            static_assert(always_false<Type>::value)
 *    }
 * 
 */
template<typename T> struct always_false : std::false_type {};

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

/* ====================================================== Types-manipulation ====================================================== */

namespace details
{
    template <typename...>
    struct is_any_of { static constexpr bool value = false; };
    
    template <typename F, typename S, typename... T>
    struct is_any_of<F, S, T...> { 
        static constexpr bool value = std::is_same<F, S>::value || is_any_of<F, T...>::value; 
    };
}

/**
 * @brief Helper trait checking whether the type is any of types given given in the sequence
 */
template <typename... T>
struct is_any_of :
    details::is_any_of<T...> {};

/// @brief Alias for @ref is_any_of<...>::value
template <typename... T>
inline constexpr bool is_any_of_v = 
    is_any_of<T...>::value;

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

/* =========================================================== Callables ========================================================== */

namespace details
{
    template <typename T>
    struct return_type;

    // Specialization for function pointers
    template <typename R, typename ... A>
    struct return_type<R (*)(A...)> { typedef R type; };

    // Specialization for function pointers with variadic arguments
    template <typename R, typename ... A>
    struct return_type<R (*)(A..., ...)> { typedef R type; };

    // Specialization for methods pointers
    template <typename R, typename T, typename ... A>
    struct return_type<R (T::*)(A...)> { typedef R type; };

    // Specialization for methods pointers with variadic arguments
    template <typename R, typename T, typename ... A>
    struct return_type<R (T::*)(A..., ...)> { typedef R type; };

}

/**
 * @brief Trait extracting return type of the function/method
 */
template <typename ... T>
struct return_type :
    details::return_type<T...> {};

/// @brief Alias for @ref return_type<T...>::type
template <typename ... T>
using return_type_t = 
    return_type<T...>::type;

namespace details
{

    // For default types, define basic structure
    template <typename T>
    struct callable_traits {

        // False for default types
        static constexpr bool is_callable = false;

    };

    // Specialization for pointers to function
    template <typename R, typename... Args>
    requires std::is_function_v<R(*)(Args...)>
    struct callable_traits<R(*)(Args...)>
    {

        // True for callable types
        static constexpr bool is_callable = true;

        // Function's arity (number of arguments)
        enum { arity = sizeof...(Args) };

        // Return type
        typedef R result_type;

        /**
         * @brief The i-th argument is equivalent to the i-th tuple element of a tuple
         *    composed of those arguments
         */
        template <size_t i>
        struct arg {
            typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
        };
    };

    // Specialization for pointers to member function
    template <typename Class, typename R, typename... Args>
    requires std::is_member_function_pointer_v<R(Class::*)(Args...) const>
    struct callable_traits<R(Class::*)(Args...) const>
    {

        // True for callable types
        static constexpr bool is_callable = true;

        // Function's arity (number of arguments)
        enum { arity = sizeof...(Args) };

        // Return type
        typedef R result_type;

        /**
         * @brief The i-th argument is equivalent to the i-th tuple element of a tuple
         *    composed of those arguments
         */
        template <size_t i>
        struct arg {
            typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
        };
    };

    // For callable types, directly use the result of the signature of its 'operator()'
    template <typename T>
    requires std::is_class_v<T>
    struct callable_traits<T> : public callable_traits<decltype(&T::operator())> { };

}

/**
 * @brief Trait provide a compile-time interface to inspect charasteristics
 *    of the arbitrary functor object (return value, parameters, etc...)
 * @tparam T
 *    type to be inspected
 */
template <typename T>
struct callable_traits : details::callable_traits<T> {};

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
    

/* ======================================================= Types-conversions ====================================================== */

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

/* ========================================================== STL-related ========================================================= */

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
