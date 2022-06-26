/* ============================================================================================================================ *//**
 * @file       if_constexpr.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 30th December 2021 5:32:36 pm
 * @modified   Sunday, 26th June 2022 11:56:58 am
 * @project    cpp-utils
 * @brief      Declaration of the enabling compil-failure when the series of if constexpr-else statements finds no match
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_PREPROCESSOR_IF_CONSTEXPR_H__
#define __ESTD_PREPROCESSOR_IF_CONSTEXPR_H__

/* ======================================================= Macrodefinitison ======================================================= */

/**
 * @brief Helper macro to be used in methods and functions templates that utilize
 *   'if-constexpr' compilation-time conditions matching. Inserting @ref IF_CONSTEXPR_NO_MATCH(...) 
 *   in the 'else' statement of such a matching scheme will result in static_assert failute
 *   with the given message.
 * @param message
 *    message to be printed with assert
 *  
 * @example 
 *  
 *    template<typename T>
 *    int foo(const T &t) {
 *        
 *        if constexpr(std::is_same_v<T, some_type_1>)
 *            ...
 *        else if constexpr(std::is_same_v<T, some_type_2>)
 *            ...
 *        else
 *            IF_CONSTEXPR_NO_MATCH("[foo] No matching type T")
 *    }
 */
#define IF_CONSTEXPR_NO_MATCH(message) []<bool flag = false>() { static_assert(flag, message); }();

/* ================================================================================================================================ */

#endif
