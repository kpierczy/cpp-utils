/** ==================================================================================================================================
 * @file       typename.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Tuesday, 15th February 2022 5:28:11 am
 * @modified   Tuesday, 15th February 2022 11:25:41 pm
 * @project    engineering-thesis
 * @brief      Implementation of compile-time, compiler-dependent typename strings generation
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * ================================================================================================================================ */

#ifndef __ESTD_TYPENAME_IMPL_TYPENAME_H__
#define __ESTD_TYPENAME_IMPL_TYPENAME_H__

/* =========================================================== Includes =========================================================== */

#include "estd/typename.hpp"

/* ========================================================== Namespaces ========================================================== */

namespace estd {

/* ========================================================== Definitions ========================================================= */

template <class T>
[[nodiscard]] constexpr auto type_name() -> std::string_view {
#if defined(_MSC_VER) and not defined(__clang__)
  return {&__FUNCSIG__[120], sizeof(__FUNCSIG__) - 128};
#elif defined(__clang_analyzer__)
  return {&__PRETTY_FUNCTION__[57], sizeof(__PRETTY_FUNCTION__) - 59};
#elif defined(__clang__) and (__clang_major__ >= 12) and not defined(__APPLE__)
  return {&__PRETTY_FUNCTION__[34], sizeof(__PRETTY_FUNCTION__) - 36};
#elif defined(__clang__)
  return {&__PRETTY_FUNCTION__[70], sizeof(__PRETTY_FUNCTION__) - 72};
#elif defined(__GNUC__)
  return {&__PRETTY_FUNCTION__[55], sizeof(__PRETTY_FUNCTION__) - 106};
#endif
}

/* ================================================================================================================================ */

} // End namespace estd

#endif
