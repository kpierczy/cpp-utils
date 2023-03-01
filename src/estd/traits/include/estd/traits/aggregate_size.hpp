/* ============================================================================================================================ *//**
 * @file       aggregate_size.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Wednesday, 1st March 2023 3:46:40 am
 * @modified   Wednesday, 1st March 2023 4:11:52 am
 * @project    cpp-utils
 * @brief      Implementation of the compile-time count of the members of aggregate types
 * 
 * @copyright Krzysztof Pierczyk © 2023
 */// ============================================================================================================================= */

#ifndef __ESTD_TRAITS_AGGREGATE_SIZE_H__
#define __ESTD_TRAITS_AGGREGATE_SIZE_H__

/* =========================================================== Includes =========================================================== */

#include <utility>
#include <tuple>
#include <type_traits>
#include "estd/traits/stl/tuple.hpp"

/* ========================================================== Namespaces ========================================================== */

namespace estd {

namespace details {

    /**
     * @brief Compile-time SFINAE check for whether the @tparam T is constructible with list
     *    of arguments of the given type
     */
    template <class T, class... Args>
    decltype(void(T{ {std::declval<Args>()}... }), std::true_type{}) test_is_braces_constructible(int);

    template <class, class...>
    std::false_type test_is_braces_constructible(...);

    template <class T, class... TArgs>
    using is_braces_constructible = decltype(test_is_braces_constructible<T, TArgs...>(0));

    /**
     * @brief Type stub that can be casted onto an arbitrary type
     */
    struct any_type {
        template <class T>
        constexpr operator T();
    };

    /**
     * @brief Key part of the implementation of the @ref aggregate_size . Transforms aggregate
     *    into std::tuple whose size can be obtained with std::tuple_size
     */
    template <class T>
    auto to_tuple(T &&object) noexcept
    {
        if constexpr(::estd::is_tuple_v<T>) {
            return object;
        } else if constexpr (is_braces_constructible<T, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type>{}) {
            auto &&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16] = object;
            return std::make_tuple(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16);
        } else if constexpr (is_braces_constructible<T, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type>{}) {
            auto &&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15] = object;
            return std::make_tuple(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15);
        } else if constexpr (is_braces_constructible<T, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type>{}) {
            auto &&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14] = object;
            return std::make_tuple(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14);
        } else if constexpr (is_braces_constructible<T, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type>{}) {
            auto &&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13] = object;
            return std::make_tuple(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13);
        } else if constexpr (is_braces_constructible<T, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type>{}) {
            auto &&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12] = object;
            return std::make_tuple(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
        } else if constexpr (is_braces_constructible<T, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type>{}) {
            auto &&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11] = object;
            return std::make_tuple(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
        } else if constexpr (is_braces_constructible<T, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type>{}) {
            auto &&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10] = object;
            return std::make_tuple(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
        } else if constexpr (is_braces_constructible<T, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type>{}) {
            auto &&[p1, p2, p3, p4, p5, p6, p7, p8, p9] = object;
            return std::make_tuple(p1, p2, p3, p4, p5, p6, p7, p8, p9);
        } else if constexpr (is_braces_constructible<T, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type>{}) {
            auto &&[p1, p2, p3, p4, p5, p6, p7, p8] = object;
            return std::make_tuple(p1, p2, p3, p4, p5, p6, p7, p8);
        } else if constexpr (is_braces_constructible<T, any_type, any_type, any_type, any_type, any_type, any_type, any_type>{}) {
            auto &&[p1, p2, p3, p4, p5, p6, p7] = object;
            return std::make_tuple(p1, p2, p3, p4, p5, p6, p7);
        } else if constexpr (is_braces_constructible<T, any_type, any_type, any_type, any_type, any_type, any_type>{}) {
            auto &&[p1, p2, p3, p4, p5, p6] = object;
            return std::make_tuple(p1, p2, p3, p4, p5, p6);
        } else if constexpr (is_braces_constructible<T, any_type, any_type, any_type, any_type, any_type>{}) {
            auto &&[p1, p2, p3, p4, p5] = object;
            return std::make_tuple(p1, p2, p3, p4, p5);
        } else if constexpr (is_braces_constructible<T, any_type, any_type, any_type, any_type>{}) {
            auto &&[p1, p2, p3, p4] = object;
            return std::make_tuple(p1, p2, p3, p4);
        } else if constexpr (is_braces_constructible<T, any_type, any_type, any_type>{}) {
            auto &&[p1, p2, p3] = object;
            return std::make_tuple(p1, p2, p3);
        } else if constexpr (is_braces_constructible<T, any_type, any_type>{}) {
            auto &&[p1, p2] = object;
            return std::make_tuple(p1, p2);
        } else if constexpr (is_braces_constructible<T, any_type>{}) {
            auto &&[p1] = object;
            return std::make_tuple(p1);
        } else {
            return std::make_tuple();
        }
    }

} // End namespace details

/**
 * @brief Implementation of the compile-time count of the members of aggregate types
 * @details
 *    Trait defines @a aggregate_size variable template that counts number of the members of aggregate
 *    types. Aggregate type is understood as the one that can be used as a subject to the structured
 *    binding.
 * @note 
 *    Implementation is C++17 compatible, although can be realized much prettier using C++20 'requires'
 * 
 * @tparam T 
 *    aggregate type to be sized
 */
template<typename T>
static constexpr std::size_t aggregate_size 
    = std::tuple_size<decltype(details::to_tuple(std::declval<T>()))>::value;

/* ================================================================================================================================ */

} // End namespace estd

/* ================================================================================================================================ */

#endif
