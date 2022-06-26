/* ============================================================================================================================ *//**
 * @file       synchronised_reference.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Tuesday, 7th June 2022 6:49:43 pm
 * @modified   Sunday, 26th June 2022 3:41:37 pm
 * @project    cpp-utils
 * @brief      
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_SYNCHRONISATION_SYNCHRONISED_REFERENCE_SYNCHRONISED_REFERENCE_H__
#define __ESTD_SYNCHRONISATION_SYNCHRONISED_REFERENCE_SYNCHRONISED_REFERENCE_H__

/* =========================================================== Includes =========================================================== */

// Standard includes
#include <assert.h>
// Private includes
#include "estd/synchronised_reference.hpp"

/* ========================================================== Namespaces ========================================================== */

namespace estd {

/* ================================================ Public ctors, dtors & operators =============================================== */

template<typename T>
constexpr synchronised_reference<T>::synchronised_reference(T &obj) :
    obj{ &obj }
{
    this->obj->lock();
}


template<typename T>
synchronised_reference<T>::~synchronised_reference() {
    if(not moved)
        obj->unlock();
}


template<typename T>
constexpr synchronised_reference<T>::synchronised_reference(synchronised_reference &&rref) :
    obj{ rref.obj }
{
    rref.moved = true;
    rref.obj   = nullptr;
}


template<typename T>
constexpr synchronised_reference<T> &synchronised_reference<T>::operator=(synchronised_reference &&rref) {
    obj        = rref.obj;
    rref.moved = true;
    rref.obj   = nullptr;
}

/* ======================================================== Public methods ======================================================== */

template<typename T>
constexpr T &synchronised_reference<T>::get() {
    assert(obj != nullptr);
    return *obj;
}


template<typename T>
constexpr const T &synchronised_reference<T>::get() const {
    return const_cast<synchronised_reference*>(this)->get();
}

/* ================================================================================================================================ */

} // End namespace estd

/* ================================================================================================================================ */

#endif
