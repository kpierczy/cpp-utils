/** ==================================================================================================================================
 * @file     fixed_string.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Monday, 12th July 2021 9:29:30 am
 * @modified Tuesday, 15th February 2022 12:43:12 am
 * @project  Winder
 * @brief
 *    
 *    Implementation of inline methods and methods templates of the compile-time string
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __ESTD_FIXED_STRING_IMPL_FIXED_STRING_H__
#define __ESTD_FIXED_STRING_IMPL_FIXED_STRING_H__

/* =========================================================== Includes =========================================================== */

#include "estd/fixed_string.hpp"

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ========================================================== Namespaces ========================================================== */

template <auto Size>
constexpr fixed_string<Size>::fixed_string(char const* str) {
    std::copy_n(str, Size + 1, data);
}

template <auto Size>
constexpr fixed_string<Size>::operator std::string_view() const {
    return {data, Size};
}

/* ================================================================================================================================ */

} // End namespace estd

#endif
