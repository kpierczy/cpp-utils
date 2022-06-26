/** ==================================================================================================================================
 * @file       variant.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 3rd February 2022 10:48:23 am
 * @modified   Thursday, 3rd February 2022 6:57:58 pm
 * @project    cpp-utils
 * @brief      Set of type traits related to std::variant
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * ================================================================================================================================ */

#ifndef __ESTD_TRAITS_STL_VARIANT_H__
#define __ESTD_TRAITS_STL_VARIANT_H__

/* =========================================================== Includes =========================================================== */

#include <variant>
#include <type_traits>

/* ========================================================== Namespaces ========================================================== */

namespace estd {

/* ============================================================ Helpers =========================================================== */

/// @brief Helper type for the in-place (lambda-based) std::visitor
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
/// @brief Explicit deduction guide for @ref overloaded class template (not needed as of C++20)
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

/* ======================================================= Dynamic dispatch ======================================================= */

/**
 * @brief Helper function producing std::variant initialized with an alternative associated with index
 *    given at runtime
 * 
 * @tparam Var
 *    type of the variant
 * @tparam Args 
 *    types of arguments to be passed to the std::variant
 * @param index 
 *    index of the target alternative
 * @param args 
 *    arguments to be passed to the std::variant
 * @returns 
 *    constructed variant
 * 
 * @note @p index is limited by the underlying @ref boost::mp11::mp_with_index implementation
 */
template<class Var, class... Args>
inline constexpr Var make_variant( std::size_t index, Args&&... args );

/* ==================================================== Variant transformations =================================================== */

/**
 * @brief Helper type alias template providing std::variant specialization holding specializations
 *    of the template @p T for all types listed in @p Args...
 * 
 * @tparam T
 *    template to be specialized
 * @tparam Args 
 *    types for specializaing the @p T template
 */
template<template<typename> typename T, typename... Args>
using specialization_variant = std::variant<T<Args>...>;

namespace details {

    /**
     * @brief Helper meta-function guiding deduction of Args... from the std::variant declval for 
     *    the @ref specialization_variant alias
     */
    template<template<typename> typename T, typename... Args>
    specialization_variant<T, Args...> specialization_variant_helper(std::variant<Args...> v);

    /**
     * @brief Helper alias template dispaching @ref specialization_variant_helper()
     */
    template<template<typename> typename T, typename Var>
    using specialization_variant = decltype(specialization_variant_helper<T>(std::declval<Var>()));

}

/**
 * @brief Helper type alias template providing a std::variant specialization defined by
 *    dispatching subsequent types held by the given @p Var std::variant as a template
 *    parameters for specializations of the given @p T template
 * 
 * @tparam T
 *    template to dispatch @p Var into
 * @tparam Var
 *    variant to be dispatched
 */
template<template<typename> typename T, typename Var>
using variant_dispatch = details::specialization_variant_helper<T, Var>;

/* ================================================================================================================================ */

} // End namespace estd

#endif
