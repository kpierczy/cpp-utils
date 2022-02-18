/** ==================================================================================================================================
 * @file     concepts.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Friday, 18th February 2022 2:00:39 pm
 * @modified Friday, 18th February 2022 2:14:20 pm
 * @project  cpp-utils
 * @brief
 *    
 *    Set of the helper concepts used in the implementation of `parseargs` module
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * ================================================================================================================================ */

#ifndef __UTILITIES_PARSEARGS_CONCEPTS_H__
#define __UTILITIES_PARSEARGS_CONCEPTS_H__

/* =========================================================== Includes =========================================================== */

#include <type_traits>
#include <string>
#include <iostream>

/* ========================================================= Declarations ========================================================= */

/**
 * @brief Helper concept describing standard containers
 */
template<typename T>
concept Container = requires(T &t) {

    // Explicit value type's identifier
    typename T::value_type;

    // Common containers' interface
    t.begin();
    t.end();
    t.size();

    // Exclude std::string
    not std::is_same_v<T, std::string>;

};

/**
 * @brief Helper concept describing streamable objects
 */
template<typename T>
concept Streamable = requires(T &t, std::ostream &stream) {

    // Require streaming oject
    stream << t;

};

/**
 * @brief Helper concept describing types that can be represented graphically
 */
template<typename T>
concept Representable = requires Container<T> || Streamable<T>;

/* ================================================================================================================================ */


#endif
