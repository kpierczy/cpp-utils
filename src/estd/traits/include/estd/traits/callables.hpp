/* ============================================================================================================================ *//**
 * @file       callables.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 3rd February 2022 10:48:23 am
 * @modified   Wednesday, 19th October 2022 9:56:39 pm
 * @project    cpp-utils
 * @brief      Set of type traits related to callables
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_TRAITS_CALLABLE_H__
#define __ESTD_TRAITS_CALLABLE_H__

/* =========================================================== Includes =========================================================== */

#include <tuple>
#include <type_traits>

/* ========================================================== Namespaces ========================================================== */

namespace estd {

/* =========================================================== Callables ========================================================== */

namespace details {

    /// Helper structure defining dependent-name dispatching to @b void
    struct void_t { using type = void; };

    template<typename T> 
    struct callable_traits; 

    /**
     * @brief Base type for function traits
     * 
     * @tparam R 
     *    result type
     * @tparam Args 
     *    argument types
     */
    template<typename R, typename ...Args> 
    struct callable_traits_base {

        /// Number of arguments
        static constexpr size_t nargs = sizeof...(Args);

        /// Resulting type
        using result_type = R;

        /// Arguments' types
        template <size_t i>
        struct arg {
            using type = typename std::tuple_element<i, std::tuple<Args...>>::type;
        };

        /// Helper meta-function returning type of the n'th argument or void if index invalid
        template <size_t i>
        struct arg_or_void {
            using type = typename std::conditional<
                i < sizeof...(Args),
                std::tuple_element<i, std::tuple<Args...>>,
                void_t
            >::type::type;
        };

    }; 

    /// Specialization of the trait for simple functions
    template<typename R, typename ...Args> 
    struct callable_traits<R (*)(Args...)> :
        public callable_traits_base<R, Args...>
    { };

    /// Specialization of the trait for simple functions with variadic template list
    template<typename R, typename ...Args> 
    struct callable_traits<R (*)(Args..., ...)> :
        public callable_traits_base<R, Args...>
    { };

    /// Specialization of the trait for methods
    template <typename R, typename T, typename ... Args>
    struct callable_traits<R (T::*)(Args...)> :
        public callable_traits_base<R, Args...>
    { };

    /// Specialization of the trait for methods (const)
    template <typename R, typename T, typename ... Args>
    struct callable_traits<R (T::*)(Args...) const> :
        public callable_traits_base<R, Args...>
    { };

    /// Specialization of the trait for methods with variadic template list
    template <typename R, typename T, typename ... Args>
    struct callable_traits<R (T::*)(Args..., ...)> :
        public callable_traits_base<R, Args...>
    { };

    /// Specialization of the trait for methods with variadic template list (const)
    template <typename R, typename T, typename ... Args>
    struct callable_traits<R (T::*)(Args..., ...) const> :
        public callable_traits_base<R, Args...>
    { };

    /// Specialization of the trait for functors
    template<typename Functor> 
    struct callable_traits :
        public callable_traits<decltype(&std::remove_reference<Functor>::type::operator())>
    { };

    /// Specialization of the trait for std::function
    template<typename R, typename ...Args> 
    struct callable_traits<std::function<R(Args...)>> :
        public callable_traits_base<R, Args...>
    { };

} // End namespace details

/**
 * @brief Helper traits used to obtain types related to the callable objects
 */
template<typename T> 
struct callable_traits : public details::callable_traits<T> { };

/// Alias for number of arguments of callable
template<typename T> 
constexpr size_t nargs = callable_traits<T>::nargs;

/// Alias for argument type of callable
template<typename T> 
using result_t = typename callable_traits<T>::result_type;

/// Alias for argument type of callable
template<typename T, std::size_t i> 
using arg_t = typename callable_traits<T>::template arg<i>::type;

/// Alias for 'argument type or void' helper function of callable
template<typename T, std::size_t i> 
using arg_or_void_t = typename callable_traits<T>::template arg_or_void<i>::type;

/* ================================================================================================================================ */

} // End namespace estd

/* ========================================================== Subincludes ========================================================= */

#include "estd/traits/callables/methods.hpp"

/* ================================================================================================================================ */

#endif
