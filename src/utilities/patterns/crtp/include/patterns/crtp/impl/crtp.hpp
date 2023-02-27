/* ============================================================================================================================ *//**
 * @file       crtp.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Sunday, 2nd January 2022 3:49:09 pm
 * @modified   Tuesday, 28th February 2023 12:33:32 am
 * @project    cpp-utils
 * @brief      Implementation of inline methods of the crtp template class
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __PATTERNS_CRTP_IMPL_CRTP_H__
#define __PATTERNS_CRTP_IMPL_CRTP_H__

/* =========================================================== Includes =========================================================== */

#include "patterns/crtp.hpp"

/* =========================================================== Namespace ========================================================== */

namespace patterns {

/* ========================================================== Namespaces ========================================================== */

template<typename T>
T &patterns::crtp<T>::impl() {
    return *static_cast<T*> (this);
}


template<typename T>
const T &patterns::crtp<T>::impl() const { 
    return *static_cast<const T*>(this); 
}

/* ================================================================================================================================ */

} // End namespace patterns

#endif
