/* ============================================================================================================================ *//**
 * @file       aligned_storage.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Sunday, 2nd January 2022 3:49:09 pm
 * @modified   Sunday, 26th June 2022 11:56:58 am
 * @project    cpp-utils
 * @brief      Implementation of inline methods of the aligned-storage module
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_ALIGNED_STORAGE_IMPL_ALIGNED_STORAGE_H__
#define __ESTD_ALIGNED_STORAGE_IMPL_ALIGNED_STORAGE_H__

/* =========================================================== Includes =========================================================== */

#include "estd/aligned_storage.hpp"

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ========================================================== Namespaces ========================================================== */

template<typename T>
constexpr T& aligned_storage_to_object(aligned_storage<T> &storage) {
    return *std::launder(reinterpret_cast<T*>(&storage));
}

/* ================================================================================================================================ */

} // End namespace estd

/* ================================================================================================================================ */

#endif
