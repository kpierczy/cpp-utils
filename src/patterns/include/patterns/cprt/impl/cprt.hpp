/** ==================================================================================================================================
 * @file     cprt.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Sunday, 2nd January 2022 3:49:09 pm
 * @modified Thursday, 3rd February 2022 6:58:47 pm
 * @project  Winder
 * @brief
 *    
 *    Implementation of inline methods of the CPRT template class
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __PATTERNS_CPRT_IMPL_CPRT_H__
#define __PATTERNS_CPRT_IMPL_CPRT_H__

/* =========================================================== Includes =========================================================== */

#include "patterns/cprt.hpp"

/* =========================================================== Namespace ========================================================== */

namespace patterns {

/* ========================================================== Namespaces ========================================================== */

template<typename T>
T &patterns::CPRT<T>::impl() {
    return *static_cast<T*> (this);
}


template<typename T>
const T &patterns::CPRT<T>::impl() const { 
    return *static_cast<const T*>(this); 
}

/* ================================================================================================================================ */

} // End namespace patterns

#endif
