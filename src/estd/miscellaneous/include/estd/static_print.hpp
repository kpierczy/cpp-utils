/** ==================================================================================================================================
 * @file     static_print.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Monday, 12th July 2021 9:25:13 am
 * @modified Thursday, 3rd February 2022 11:26:44 am
 * @project  Winder
 * @brief
 *    
 *    Header file of compile-time, hacky values printer
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __UTILS_MISCELLANEOUS_CONSTEXPR_H__
#define __UTILS_MISCELLANEOUS_CONSTEXPR_H__

/* =========================================================== Includes =========================================================== */

#include <array>
#include <string_view>

/* ===================================================== Compiletime utilities ==================================================== */

/**
 * @brief Helper compile-time function that will print the template-enabled @p var 
 *    constant using GCC's -Wunused warning
 * @tparam val 
 *    value to be printed
 */
template <auto val>
constexpr void static_print();

/* ==================================================== Implementation includes =================================================== */

#include "estd/static_print/impl/static_print.hpp"

/* ================================================================================================================================ */

#endif
