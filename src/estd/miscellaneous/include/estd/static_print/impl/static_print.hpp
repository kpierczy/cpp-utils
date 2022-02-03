/** ==================================================================================================================================
 * @file     static_print.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Monday, 12th July 2021 9:29:30 am
 * @modified Thursday, 3rd February 2022 11:26:36 am
 * @project  Winder
 * @brief
 *    
 *    Implementation of inline methods and methods templates of the compile-time helpers module
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __ESTD_STATIC_PRINT_IMPL_STATIC_PRINT_H__
#define __ESTD_STATIC_PRINT_IMPL_STATIC_PRINT_H__

/* =========================================================== Includes =========================================================== */

#include "estd/static_print.hpp"

/* ========================================================== Namespaces ========================================================== */

template <auto val>
constexpr void static_print() {
    #if !defined(__GNUC__) || defined(__clang__)
        int static_print_is_implemented_only_for_gcc = 0;
    #else
    #pragma GCC diagnostic warning "-Wunused"
    #pragma GCC diagnostic push
        int unused = 0;
    #pragma GCC diagnostic pop
    #endif
};

/* ================================================================================================================================ */

#endif
