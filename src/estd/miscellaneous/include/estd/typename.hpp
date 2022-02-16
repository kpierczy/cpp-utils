/** ==================================================================================================================================
 * @file     typename.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Tuesday, 15th February 2022 5:27:08 am
 * @modified Tuesday, 15th February 2022 5:28:15 am
 * @project  Winder
 * @brief
 *    
 *    Header file of compile-time, compiler-dependent typename strings generation
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __ESTD_TYPENAME_H__
#define __ESTD_TYPENAME_H__

/* =========================================================== Includes =========================================================== */

#include <array>
#include <string_view>

/* ===================================================== Compiletime utilities ==================================================== */

/**
 * @brief Returns name of the given @tparam T type
 * @tparam T 
 *    type to be converted
 * @returns 
 *    name of the given @tparam T type
 */
template <class T>
[[nodiscard]] constexpr auto type_name() -> std::string_view;

/* ==================================================== Implementation includes =================================================== */

#include "estd/typename/impl/typename.hpp"

/* ================================================================================================================================ */

#endif
