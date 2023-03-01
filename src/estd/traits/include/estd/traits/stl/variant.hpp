/* ============================================================================================================================ *//**
 * @file       variant.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 3rd February 2022 10:48:23 am
 * @modified   Wednesday, 1st March 2023 4:08:55 am
 * @project    cpp-utils
 * @brief      Set of type traits related to std::variant
 *    
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

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
 * @brief Meta-function transforming all @tparam Args... with the @tparam TransformF 
 *    template and placing the result in the @b std::variant specialization
 * 
 * @tparam TransformF
 *    transforming template
 * @tparam Args...
 *    types to be transformer
 */
template<template<typename> typename TransformF, typename... Args>
using transform_into_variant = std::variant<TransformF<Args>...>;

namespace details {

    /**
     * @brief Helper meta-function guiding deduction of Args... from the std::variant for 
     *    the @ref details::transform_into_variant alias
     */
    template<template<typename> typename T, typename... Args>
    transform_into_variant<T, Args...> transform_into_variant_helper(std::variant<Args...> v);

    /**
     * @brief Helper alias template dispatching @ref transform_variant()
     */
    template<template<typename> typename T, typename Var>
    using transform_into_variant = decltype(transform_into_variant_helper<T>(std::declval<Var>()));

}

/**
 * @brief Helper meta-function transforming @b std::variant type by 'calling' @tparam TransformF 
 *    on each of its elements
 * 
 * @tparam TransformF
 *    template to transform @p Var into
 * @tparam Var
 *    variant to be transformed
 */
template<template<typename> typename T, typename Var>
using transform_variant = details::transform_into_variant<T, Var>;

/* ================================================================================================================================ */

} // End namespace estd

#endif
