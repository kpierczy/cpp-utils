/* ============================================================================================================================ *//**
 * @file       pointers.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Monday, 12th July 2021 9:29:30 am
 * @modified   Sunday, 26th June 2022 11:56:58 am
 * @project    cpp-utils
 * @brief      Implementation of utilities defined in the estd/pointers.hpp
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_POINTERS_IMPL_POINTERS_H__
#define __ESTD_POINTERS_IMPL_POINTERS_H__

/* =========================================================== Includes =========================================================== */

#include "estd/pointers.hpp"

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ========================================================== Namespaces ========================================================== */

template<class T, typename U>
std::ptrdiff_t member_offset(U T::* member) {
    return reinterpret_cast<std::ptrdiff_t>(
        (char*)(&((T*)nullptr->*member)) - (char*)(nullptr)
    );
}

/* ================================================================================================================================ */

} // End namespace estd

#endif
