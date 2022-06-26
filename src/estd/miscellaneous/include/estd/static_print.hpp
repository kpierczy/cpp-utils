/* ============================================================================================================================ *//**
 * @file       static_print.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Monday, 12th July 2021 9:25:13 am
 * @modified   Sunday, 26th June 2022 11:56:58 am
 * @project    cpp-utils
 * @brief      Header file of compile-time, hacky values printer
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_STATIC_PRINT_H__
#define __ESTD_STATIC_PRINT_H__

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
