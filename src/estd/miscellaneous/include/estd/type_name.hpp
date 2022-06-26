/* ============================================================================================================================ *//**
 * @file       type_name.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Monday, 9th May 2022 5:42:48 pm
 * @modified   Sunday, 26th June 2022 3:41:37 pm
 * @project    cpp-utils
 * @brief      Definitions of (kindof) portable compile-time function obtaining human-readable name of the type with C++17
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_MISCELLANEOUS_TYPE_NAME_H__
#define __ESTD_MISCELLANEOUS_TYPE_NAME_H__

/* =========================================================== Includes =========================================================== */

// Standard includes
#include <experimental/source_location>

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ======================================================== Implementation ======================================================== */

namespace details {

    /**
     * @brief Obtains name of the function specialized for the target @p T type (name of the type is 
     *    present in the name of function)
     * 
     * @tparam T 
     *    target type
     * @returns 
     *    name of the function specialized for @p T
     */
    template <typename T>
    constexpr auto func_name() {
        const auto& loc = std::experimental::source_location::current();
        return loc.function_name();
    }

    /**
     * @brief Parses result of @ref func_name() to obtain name of the target type
     * 
     * @tparam T 
     *    target type
     * @returns 
     *    name of the @p T
     */
    template <typename T>
    constexpr std::string_view type_name() {
        constexpr std::string_view fname = func_name<T>();
        return std::string_view{ &fname[10], fname.size() - 11};
    }

}

/* =========================================================== type_name ========================================================== */

/**
 * @brief Obtains name of the type of the given @p arg computed at compile time
 * 
 * @tparam T 
 *    type of @p arg
 * @param arg 
 *    value whose type should be stringified
 * @returns 
 *    human-readable name of the type of @p arg
 */
template <typename T>
constexpr auto type_name(T&& arg) {
    return details::type_name<decltype(arg)>();
}

/**
 * @brief Obtains name of the @p T computed at compile time
 * 
 * @tparam T 
 *    type to be stringified
 * @returns 
 *    human-readable name of the @p T
 */
template <typename T>
constexpr auto type_name() {
    return details::type_name<T>();
}

/* ================================================================================================================================ */

} // End namespace estd

#endif
