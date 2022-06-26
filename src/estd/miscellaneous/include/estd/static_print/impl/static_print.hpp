/* ============================================================================================================================ *//**
 * @file       static_print.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Monday, 12th July 2021 9:29:30 am
 * @modified   Sunday, 26th June 2022 11:56:58 am
 * @project    cpp-utils
 * @brief      Implementation of inline methods and methods templates of the compile-time helpers module
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

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
