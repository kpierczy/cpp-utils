/* ============================================================================================================================ *//**
 * @file       general.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 3rd February 2022 10:48:23 am
 * @modified   Wednesday, 19th October 2022 9:57:37 pm
 * @project    cpp-utils
 * @brief      Set of commonly used type traits
 *    
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_TRAITS_GENERAL_H__
#define __ESTD_TRAITS_GENERAL_H__

/* =========================================================== Includes =========================================================== */

#include <tuple>
#include <type_traits>

/* ========================================================== Namespaces ========================================================== */

namespace estd {

/* ============================================================ Helpers =========================================================== */

/**
 * @brief Auxiliary empty class for base-class conditional resolution
 */
struct empty { };

/**
 * @brief Auxiliary alias for choosing between target and empty type based on the 
 *    given conditon
 */
template<bool condition, typename T>
using type_or_empty = std::conditional_t<condition, T, empty>;

/**
 * @brief Auxiliary alias for choosing between target and empty type based on the 
 *    given conditon
 */
template<bool condition, typename T>
using empty_or_type = std::conditional_t<condition, empty, T>;

/**
 * @brief Auxiliary type used to conditonally include member objects into class'es layout
 */
template<typename T, bool condition>
using maybe_member = std::conditional_t<condition, T, empty>;

/**
 * @brief Helper trait wrapping type @p T into a type-dependant context
 * 
 * @tparam T 
 *    wrapped type
 * 
 * @note This trait can be used to prevent specialization of the type T in an unwanted
 *    context (e.g. in argument of std::conditional_t)
 */
template<typename T>
struct wrap_type {
    using type = T;
};

template<typename T>
using wrap_type_t = typename wrap_type<T>::type;

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

template<typename T>
constexpr bool always_false_v = always_false<T>::value;

/**
 * @brief Helper integral-constant trait providing true value in a type-dependent context
 * 
 * @tparam T 
 *    dependent type
 */
template<typename T>
struct always_true : public std::true_type { };

template<typename T>
constexpr bool always_true_v = always_false<T>::value;

namespace details {

    template<class T>
    struct remove_vref {
        using type = std::remove_volatile_t<std::remove_reference_t<T>>;
    };

} // End namespace details

/**
 * @brief Helper trait removing volatile and reference attribtues from the type @p T
 * 
 * @tparam T 
 *   type to be modified
 */
template<class T>
struct remove_vref : public details::remove_vref<T> { };

/// Helper alias for remove_vref<T>::type
template<class T>
using remove_vref_t = typename remove_vref<T>::type;

namespace details {

    template<class T>
    struct remove_cvref {
        using type = std::remove_cv_t<std::remove_reference_t<T>>;
    };

} // End namespace details

/**
 * @brief Helper trait removing cv and reference attribtues from the type @p T
 * 
 * @tparam T 
 *   type to be modified
 * 
 * @note It's defined as standard trait since C++20
 */
template<class T>
struct remove_cvref : public details::remove_cvref<T> { };

/// Helper alias for remove_cvref<T>::type
template<class T>
using remove_cvref_t = typename remove_cvref<T>::type;

namespace details {

    template<class T, class D>
    struct cvref_derived_no_ref {
        static constexpr bool value = 
            std::is_same_v<
                remove_cvref_t<D>, T
            > && not std::is_same_v<
                D, T&
            >;
    };

} // End namespace details

/**
 * @brief Helper trait checking whether @p D is cv-ref-derived from @p T but is not
 *    @p T&
 * 
 * @tparam T 
 *   base type
 * @tparam D 
 *   derived type
 */
template<class T, class D>
struct cvref_derived_no_ref : public details::cvref_derived_no_ref<T, D> { };

/// Helper alias for remove_vref<T>::type
template<class T, class D>
constexpr bool cvref_derived_no_ref_v = cvref_derived_no_ref<T, D>::value;

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

/* ================================================================================================================================ */

} // End namespace estd

#endif
