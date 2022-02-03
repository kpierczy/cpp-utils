/** ==================================================================================================================================
 * @file     aligned_storage.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Wednesday, 5th January 2022 11:09:00 pm
 * @modified Thursday, 3rd February 2022 11:27:44 am
 * @project  Winder
 * @brief
 *    
 *    Implementation of helper utilities related to aligned storage container
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * @see https://stackoverflow.com/questions/42521605/placement-new-address-alignment
 * ================================================================================================================================ */

#ifndef __ESTD_ALIGNED_STORAGE_H__
#define __ESTD_ALIGNED_STORAGE_H__

/* =========================================================== Includes =========================================================== */

#include <new>
#include <type_traits>

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ========================================================== Definitions ========================================================= */

/**
 * @brief Alias for the uninitialized storage containers proper to store
 *    objects of type @tparam T
 * @tparam T 
 *    type of the stored object
 */
template<typename T>
using aligned_storage = std::aligned_storage_t<sizeof(T), alignof(T)>;

/**
 * @brief Helper cast operation turning storage object into reference to 
 *    the stored type
 * @tparam T 
 *    type of the stored object
 * @param storage 
 *    storage object
 * @return T& 
 */
template<typename T>
inline constexpr T& aligned_storage_to_object(aligned_storage<T> &storage);

/* ==================================================== Implementation includes =================================================== */

#include "estd/miscellaneous/aligned_storage/impl/aligned_storage.hpp"

/* ================================================================================================================================ */

} // End namespace estd

#endif
