/** ==================================================================================================================================
 * @file     pointers.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Monday, 12th July 2021 9:29:30 am
 * @modified Thursday, 3rd February 2022 11:35:35 am
 * @project  Winder
 * @brief
 *    
 *    Implementation of utilities defined in the estd/pointers.hpp
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

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
